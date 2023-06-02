#pragma once

#include <Siv3D.hpp>

enum NodeKind {
  ND_Bin,
  ND_Assign,
  ND_Num,
  ND_Var,
  ND_NextPixel,
  ND_NowPixel,
  ND_While,
  ND_For,
  ND_If,
  ND_Cpd,
};

class Node {
 public:
  NodeKind kind;

  // bin
  String calc;

  // bin, assign
  Node* lhs;
  Node* rhs;

  // num
  int32 num;

  // var
  String var;

  // pixel
  Node* x_var;
  Node* y_var;

  // while, if, for
  Node* cond_node;

  // while
  Node* run_node;

  // for
  Node* init_node;
  Node* loop_node;

  // if
  Node* then_node;
  Node* else_node;

  // cpd
  Array<Node*> nodes;

  static Node* new_bin(String calc, Node* lhs, Node* rhs);
  static Node* new_assign(Node* lhs, Node* rhs);
  static Node* new_num(int32 num);
  static Node* new_var(String var);
  static Node* new_next_pixel(Node* x_var, Node* y_var);
  static Node* new_now_pixel(Node* x_var, Node* y_var);
  static Node* new_while(Node* cond_node, Node* run_node);
  static Node* new_for(Node* init_node, Node* cond_node, Node* loop_node,
                       Node* run_node);
  static Node* new_if(Node* cond_node, Node* then_node, Node* else_node);
  static Node* new_cpd(Array<Node*> nodes);
};

class Func {
 public:
  String name;
  Node* node;
};
