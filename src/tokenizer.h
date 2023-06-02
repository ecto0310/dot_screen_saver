#pragma once

#include <Siv3D.hpp>

#include "token.h"

class Tokenizer {
  String code;

 public:
  Tokenizer(String file);
  Array<Token> tokenize();
};
