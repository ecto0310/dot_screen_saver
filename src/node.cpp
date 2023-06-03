#include "node.h"

Node* Node::new_bin(String calc, Node* lhs, Node* rhs) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_Bin;
#ifdef _WIN32
  node->calc = String(calc);
#else
  node->calc = calc;
#endif
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node* Node::new_assign(Node* lhs, Node* rhs) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_Assign;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node* Node::new_num(int32 num) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_Num;
  node->num = num;
  return node;
}

Node* Node::new_var(String var) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_Var;
#ifdef _WIN32
  node->var = String(var);
#else
  node->var = var;
#endif
  return node;
}

Node* Node::new_next_pixel(Node* x_var, Node* y_var) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_NextPixel;
  node->x_var = x_var;
  node->y_var = y_var;
  return node;
}

Node* Node::new_now_pixel(Node* x_var, Node* y_var) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_NowPixel;
  node->x_var = x_var;
  node->y_var = y_var;
  return node;
}

Node* Node::new_while(Node* cond_node, Node* run_node) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_While;
  node->cond_node = cond_node;
  node->run_node = run_node;
  return node;
}

Node* Node::new_for(Node* init_node, Node* cond_node, Node* loop_node,
                    Node* run_node) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_For;
  node->init_node = init_node;
  node->cond_node = cond_node;
  node->loop_node = loop_node;
  node->run_node = run_node;
  return node;
}

Node* Node::new_if(Node* cond_node, Node* then_node, Node* else_node) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_If;
  node->cond_node = cond_node;
  node->then_node = then_node;
  node->else_node = else_node;
  return node;
}

Node* Node::new_cpd(Array<Node*> nodes) {
  Node* node = (Node*)calloc(1, sizeof(Node));
  node->kind = NodeKind::ND_Cpd;
  node->nodes = nodes;
  return node;
}
