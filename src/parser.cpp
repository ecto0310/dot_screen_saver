#include "parser.h"

Parser::Parser(Array<Token> tokens) {
  this->tokens = tokens;
  this->token_size = (int32)tokens.size();
}

HashTable<String, Node*> Parser::parse() {
  HashTable<String, Node*> funcs;
  while (this->tokens[this->ind].kind != TK_Eof) {
    Func func = this->func();
    funcs[func.name] = func.node;
  }
  return funcs;
}

Func Parser::func() {
  Func func;
  if (this->tokens[this->ind].kind != TokenKind::TK_Ident) {
    throw Error{U"Failed to parse function name"};
  }
  func.name = this->tokens[this->ind].str;
  this->ind++;
  func.node = this->stmt();
  return func;
}

Node* Parser::stmt() {
  if (this->tokens[this->ind].str == U"{") {
    this->ind++;
    Array<Node*> nodes;
    while (this->tokens[this->ind].str != U"}") {
      nodes.push_back(this->stmt());
    }
    if (this->tokens[this->ind].str != U"}") {
      throw Error{U"Failed to parse cpd end }"};
    }
    this->ind++;
    return Node::new_cpd(nodes);
  }
  switch (this->tokens[this->ind].kind) {
    case TokenKind::TK_While:
      return this->stmt_while();
    case TokenKind::TK_For:
      return this->stmt_for();
    case TokenKind::TK_If:
      return this->stmt_if();
  }
  return this->stmt_expr();
}

Node* Parser::stmt_while() {
  if (this->tokens[this->ind].kind != TokenKind::TK_While) {
    throw Error{U"Failed to parse for"};
  }
  this->ind++;
  if (this->tokens[this->ind].str != U"(") {
    throw Error{U"Failed to parse while begin ("};
  }
  this->ind++;
  Node* cont_node = this->expr();

  if (this->tokens[this->ind].str != U")") {
    throw Error{U"Failed to parse while end )"};
  }
  this->ind++;
  Node* run_node = this->stmt();
  return Node::new_while(cont_node, run_node);
}

Node* Parser::stmt_for() {
  if (this->tokens[this->ind].kind != TokenKind::TK_For) {
    throw Error{U"Failed to parse for"};
  }
  this->ind++;
  if (this->tokens[this->ind].str != U"(") {
    throw Error{U"Failed to parse for begin ("};
  }
  this->ind++;
  Node* init_node = this->expr();
  if (this->tokens[this->ind].str != U";") {
    throw Error{U"Failed to parse for between ;"};
  }
  this->ind++;
  Node* cond_node = this->expr();
  if (this->tokens[this->ind].str != U";") {
    throw Error{U"Failed to parse for between ;"};
  }
  this->ind++;
  Node* loop_node = this->expr();
  if (this->tokens[this->ind].str != U")") {
    throw Error{U"Failed to parse while end )"};
  }
  this->ind++;
  Node* run_node = this->stmt();
  return Node::new_for(init_node, cond_node, loop_node, run_node);
}

Node* Parser::stmt_if() {
  if (this->tokens[this->ind].kind != TokenKind::TK_If) {
    throw Error{U"Failed to parse for"};
  }
  this->ind++;
  if (this->tokens[this->ind].str != U"(") {
    throw Error{U"Failed to parse while begin ("};
  }
  this->ind++;
  Node* cond_node = this->expr();
  if (this->tokens[this->ind].str != U")") {
    throw Error{U"Failed to parse while end )"};
  }
  this->ind++;
  Node* then_node = this->stmt();
  if (this->tokens[this->ind].kind != TokenKind::TK_Else) {
    return Node::new_if(cond_node, then_node, nullptr);
  }
  this->ind++;
  Node* else_node = this->stmt();
  return Node::new_if(cond_node, then_node, else_node);
}

Node* Parser::stmt_expr() {
  Node* node = this->expr();
  if (this->tokens[this->ind].str != U";") {
    throw Error{U"Failed to expr stmt end ;" + this->tokens[this->ind].str};
  }
  this->ind++;
  return node;
}

Node* Parser::expr() { return this->expr_assign(); }

Node* Parser::expr_assign() {
  Node* lhs = this->expr_log_or();
  if (this->tokens[this->ind].str == U"=") {
    this->ind++;
    return Node::new_assign(lhs, this->expr_assign());
  }
  return lhs;
}

Node* Parser::expr_log_or() {
  Node* lhs = this->expr_log_and();
  if (this->tokens[this->ind].str == U"||") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_log_or());
  }
  return lhs;
}

Node* Parser::expr_log_and() {
  Node* lhs = this->expr_or();
  if (this->tokens[this->ind].str == U"&&") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_log_and());
  }
  return lhs;
}

Node* Parser::expr_or() {
  Node* lhs = this->expr_xor();
  if (this->tokens[this->ind].str == U"|") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_or());
  }
  return lhs;
}

Node* Parser::expr_xor() {
  Node* lhs = this->expr_and();
  if (this->tokens[this->ind].str == U"^") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_xor());
  }
  return lhs;
}

Node* Parser::expr_and() {
  Node* lhs = this->expr_equal();
  if (this->tokens[this->ind].str == U"&") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_and());
  }
  return lhs;
}

Node* Parser::expr_equal() {
  Node* lhs = this->expr_relation();
  if (this->tokens[this->ind].str == U"==" ||
      this->tokens[this->ind].str == U"!=") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_equal());
  }
  return lhs;
}

Node* Parser::expr_relation() {
  Node* lhs = this->expr_add();
  if (this->tokens[this->ind].str == U"<" ||
      this->tokens[this->ind].str == U"<=") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_relation());
  }
  if (this->tokens[this->ind].str == U">") {
    this->ind++;
    return Node::new_bin(U"<", this->expr_relation(), lhs);
  }
  if (this->tokens[this->ind].str == U">=") {
    this->ind++;
    return Node::new_bin(U"<=", this->expr_relation(), lhs);
  }
  return lhs;
}

Node* Parser::expr_add() {
  Node* lhs = this->expr_mul();
  if (this->tokens[this->ind].str == U"+" ||
      this->tokens[this->ind].str == U"-") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_add());
  }
  return lhs;
}

Node* Parser::expr_mul() {
  Node* lhs = this->expr_unary();
  if (this->tokens[this->ind].str == U"*" ||
      this->tokens[this->ind].str == U"/" ||
      this->tokens[this->ind].str == U"%") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, lhs, this->expr_mul());
  }
  return lhs;
}

Node* Parser::expr_unary() {
  if (this->tokens[this->ind].str == U"-" ||
      this->tokens[this->ind].str == U"+") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    return Node::new_bin(calc, Node::new_num(0), this->expr_prim());
  }
  if (this->tokens[this->ind].str == U"++") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    Node* var = this->expr_prim();
    return Node::new_assign(var, Node::new_bin(U"+", var, Node::new_num(1)));
  }
  if (this->tokens[this->ind].str == U"--") {
    String calc = this->tokens[this->ind].str;
    this->ind++;
    Node* var = this->expr_prim();
    return Node::new_assign(var, Node::new_bin(U"-", var, Node::new_num(1)));
  }
  return this->expr_prim();
}

Node* Parser::expr_prim() {
  if (this->tokens[this->ind].str == U"[[") {
    this->ind++;
    Node* x_var = this->expr();
    if (this->tokens[this->ind].str != U",") {
      throw Error{U"Failed to prim ," + this->tokens[this->ind].str};
    }
    this->ind++;
    Node* y_var = this->expr();
    if (this->tokens[this->ind].str != U"]]") {
      throw Error{U"Failed to prim ]]"};
    }
    this->ind++;
    return Node::new_next_pixel(x_var, y_var);
  }
  if (this->tokens[this->ind].str == U"[") {
    this->ind++;
    Node* x_var = this->expr();
    if (this->tokens[this->ind].str != U",") {
      throw Error{U"Failed to prim ,"};
    }
    this->ind++;
    Node* y_var = this->expr();
    if (this->tokens[this->ind].str != U"]") {
      throw Error{U"Failed to prim ]"};
    }
    this->ind++;
    return Node::new_now_pixel(x_var, y_var);
  }
  if (this->tokens[this->ind].str == U"(") {
    this->ind++;
    Node* node = this->expr();
    if (this->tokens[this->ind].str != U")") {
      throw Error{U"Failed to prim )"};
    }
    this->ind++;
    return node;
  }
  if (this->tokens[this->ind].kind == TokenKind::TK_Num) {
    int32 num = this->tokens[this->ind].num;
    this->ind++;
    return Node::new_num(num);
  }
  String name = this->tokens[this->ind].str;
  this->ind++;
  return Node::new_var(name);
}
