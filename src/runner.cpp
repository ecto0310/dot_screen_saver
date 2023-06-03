#include "runner.h"

Runner::Runner(HashTable<String, Node*> funcs, int32 wx, int32 wy)
    : funcs(funcs), wx(wx), wy(wy) {}

void Runner::run(String name) {
  if (this->funcs.count(name) == 0) {
    throw Error{U"Failed to run"};
  }
  this->run_node(this->funcs[name]);
}

int32 Runner::run_node(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  switch (node->kind) {
    case NodeKind::ND_Bin:
      return this->run_bin(node->calc, node->lhs, node->rhs);
    case NodeKind::ND_Assign:
      return this->run_assign(node->lhs, node->rhs);
    case NodeKind::ND_Num:
      return node->num;
    case NodeKind::ND_Var:
      return this->run_var(node->var);
    case NodeKind::ND_NextPixel:
      return this->run_next_pixel(node->x_var, node->y_var);
    case NodeKind::ND_NowPixel:
      return this->run_now_pixel(node->x_var, node->y_var);
    case NodeKind::ND_While:
      return this->run_while(node->cond_node, node->run_node);
    case NodeKind::ND_For:
      return this->run_for(node->init_node, node->cond_node, node->loop_node,
                           node->run_node);
    case NodeKind::ND_If:
      return this->run_if(node->cond_node, node->then_node, node->else_node);
    case NodeKind::ND_Cpd:
      return this->run_cpd(node->nodes);
  }
  throw Error{U"Failed to run"};
}

int32 Runner::run_bin(String calc, Node* lhs, Node* rhs) {
  int32 res_lhs = this->run_node(lhs);
  int32 res_rhs = this->run_node(rhs);
  if (calc == U"+") {
    return res_lhs + res_rhs;
  }
  if (calc == U"-") {
    return res_lhs - res_rhs;
  }
  if (calc == U"*") {
    return res_lhs * res_rhs;
  }
  if (calc == U"/") {
    return res_lhs / res_rhs;
  }
  if (calc == U"%") {
    return res_lhs % res_rhs;
  }
  if (calc == U"&") {
    return res_lhs & res_rhs;
  }
  if (calc == U"|") {
    return res_lhs | res_rhs;
  }
  if (calc == U"^") {
    return res_lhs ^ res_rhs;
  }
  if (calc == U"||") {
    return res_lhs || res_rhs;
  }
  if (calc == U"&&") {
    return res_lhs && res_rhs;
  }
  if (calc == U"==") {
    return res_lhs == res_rhs;
  }
  if (calc == U"!=") {
    return res_lhs != res_rhs;
  }
  if (calc == U"<") {
    return res_lhs < res_rhs;
  }
  if (calc == U"<=") {
    return res_lhs <= res_rhs;
  }
  throw Error{U"Failed to run"};
}

int32 Runner::run_assign(Node* lhs, Node* rhs) {
  if (lhs->kind == NodeKind::ND_Var &&
      (lhs->var == U"wx" || lhs->var == U"wx" ||
       this->funcs.count(lhs->var) == 1)) {
    throw Error{U"Failed to run"};
  }
  int32 res_rhs = this->run_node(rhs);
  if (lhs->kind == NodeKind::ND_Var) {
    this->var[lhs->var] = res_rhs;
  } else if (lhs->kind == NodeKind::ND_NextPixel) {
    int32 res_x_var = this->run_node(lhs->x_var);
    int32 res_y_var = this->run_node(lhs->y_var);
    this->next_pixel[{res_x_var, res_y_var}] = res_rhs;
  }
  return res_rhs;
}

int32 Runner::run_var(String name) {
  if (name == U"wx") {
    return this->wx / this->pattern_size;
  }
  if (name == U"wy") {
    return this->wy / this->pattern_size;
  }
  if (name == U"rand") {
    return rand();
  }
  if (this->funcs.count(name) == 1) {
    this->run(name);
    return 0;
  }
  return this->var[name];
}

int32 Runner::run_while(Node* cond_node, Node* run_node) {
  while (this->run_node(cond_node)) {
    this->run_node(run_node);
  }
  return 0;
}

int32 Runner::run_for(Node* init_node, Node* cond_node, Node* loop_node,
                      Node* run_node) {
  for (this->run_node(init_node); this->run_node(cond_node);
       this->run_node(loop_node)) {
    this->run_node(run_node);
  }
  return 0;
}

int32 Runner::run_if(Node* cond_node, Node* then_node, Node* else_node) {
  if (this->run_node(cond_node)) {
    this->run_node(then_node);
  } else {
    this->run_node(else_node);
  }
  return 0;
}

int32 Runner::run_cpd(std::vector<Node*> nodes) {
  for (Node* node : nodes) {
    this->run_node(node);
  }
  return 0;
}

int32 Runner::run_next_pixel(Node* x_var, Node* y_var) {
  int32 res_x_var = this->run_node(x_var);
  int32 res_y_var = this->run_node(y_var);
  return this->next_pixel[{res_x_var, res_y_var}];
}

int32 Runner::run_now_pixel(Node* x_var, Node* y_var) {
  int32 res_x_var = this->run_node(x_var);
  int32 res_y_var = this->run_node(y_var);
  return this->now_pixel[{res_x_var, res_y_var}];
}

void Runner::draw() {
  for (auto [pos, color] : this->next_pixel) {
    Rect{pos.first * this->pattern_size, pos.second * this->pattern_size,
         this->pattern_size, this->pattern_size}
        .draw(Color{(uint8)(color / (int32)65536 % (int32)256),
                    (uint8)(color / (int32)256 % (int32)256),
                    (uint8)(color % (int32)256)});
  }
  this->now_pixel = this->next_pixel;
  this->next_pixel.clear();
}
