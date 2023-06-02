#pragma once

#include "node.h"
#include "token.h"

class Parser {
  Array<Token> tokens;
  int32 token_size;
  int32 ind = 0;

  Func func();

  Node* stmt();
  Node* stmt_while();
  Node* stmt_for();
  Node* stmt_if();
  Node* stmt_expr();
  Node* expr();
  Node* expr_assign();
  Node* expr_log_or();
  Node* expr_log_and();
  Node* expr_or();
  Node* expr_xor();
  Node* expr_and();
  Node* expr_equal();
  Node* expr_relation();
  Node* expr_add();
  Node* expr_mul();
  Node* expr_unary();
  Node* expr_prim();

 public:
  Parser(Array<Token> tokens);
  HashTable<String, Node*> parse();
};
