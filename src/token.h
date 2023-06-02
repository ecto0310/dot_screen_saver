#pragma once

#include <Siv3D.hpp>

enum TokenKind {
  TK_Punc,
  TK_Num,
  TK_Ident,
  TK_While,
  TK_For,
  TK_If,
  TK_Else,
  TK_Eof,
};

class Token {
 public:
  TokenKind kind;
  int32 num;
  String str;
};
