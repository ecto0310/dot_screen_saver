#pragma once

#include <Siv3D.hpp>

#include "node.h"

class Runner {
  int32 wx, wy;
  HashTable<String, Node*> funcs;
  HashTable<String, int32> var;
  HashTable<std::pair<int32, int32>, int32> next_pixel;
  HashTable<std::pair<int32, int32>, int32> now_pixel;
  const int32 pattern_size = 40;

 public:
  Runner(HashTable<String, Node*> funcs, int32 wx, int32 wy);

  void run(String name);
  int32 run_node(Node* node);
  int32 run_bin(String calc, Node* lhs, Node* rhs);
  int32 run_assign(Node* lhs, Node* rhs);
  int32 run_var(String name);
  int32 run_while(Node* cont_node, Node* run_node);
  int32 run_for(Node* init_node, Node* cond_node, Node* loop_node,
                Node* run_node);
  int32 run_if(Node* cond_node, Node* then_node, Node* else_node);
  int32 run_cpd(std::vector<Node*> nodes);
  int32 run_next_pixel(Node* x_var, Node* y_var);
  int32 run_now_pixel(Node* x_var, Node* y_var);
  void draw();
};
