#include "tokenizer.h"

Tokenizer::Tokenizer(String file) {
  TextReader reader{file};
  if (not reader) {
    throw Error{U"Failed to open " + file};
  }
  String line;
  while (reader.readLine(line)) {
    this->code.append(line + '\n');
  }
}

Array<Token> Tokenizer::tokenize() {
  Array<Token> tokens;

  for (int i = 0; i < (int)code.length(); i++) {
    if (isspace(code[i])) {
      continue;
    }

    const Array<String> puncs = {
        U"<=", U">=", U"==", U"!=", U"&&", U"||", U"[[", U"]]", U"++", U"--",
        U"[",  U"]",  U"(",  U")",  U"{",  U"}",  U"*",  U"/",  U"+",  U"-",
        U"%",  U"=",  U";",  U"<",  U">",  U"&",  U"|",  U","};
    for (String punc : puncs) {
      int length = (int)punc.length();
      if (punc == code.substr(i, length)) {
        tokens.push_back(Token{TokenKind::TK_Punc, 0, punc});
        i += length - 1;
        goto fin;
      }
    }

    if (isdigit(code[i])) {
      String str{code[i]};
      while (isdigit(code[i + 1])) {
        str.push_back(code[i + 1]);
        i++;
      }
      tokens.push_back(Token{TokenKind::TK_Num, Parse<int32>(str), str});
      goto fin;
    }

    if (isalpha(code[i]) || code[i] == '_') {
      String str{code[i]};
      while (isalpha(code[i + 1]) || isdigit(code[i + 1]) ||
             code[i + 1] == '_') {
        str.push_back(code[i + 1]);
        i++;
      }

      if (str == U"while") {
        tokens.push_back(Token{TokenKind::TK_While, 0, str});
      } else if (str == U"for") {
        tokens.push_back(Token{TokenKind::TK_For, 0, str});
      } else if (str == U"if") {
        tokens.push_back(Token{TokenKind::TK_If, 0, str});
      } else if (str == U"else") {
        tokens.push_back(Token{TokenKind::TK_Else, 0, str});
      } else {
        tokens.push_back(Token{TokenKind::TK_Ident, 0, str});
      }
      goto fin;
    }

    throw Error{U"Failed to tokenize '" + String{code[i]} + U"\'"};
  fin:;
  }
  tokens.push_back(Token{TokenKind::TK_Eof, 0, U""});
  return tokens;
}
