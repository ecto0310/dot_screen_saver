#include <Siv3D.hpp>

#include "parser.h"
#include "tokenizer.h"

void Main() {
  Scene::SetResizeMode(ResizeMode::Actual);
  Window::SetFullscreen(true);

  Tokenizer tokenizer(U"program");
  Array<Token> tokens = tokenizer.tokenize();

  Parser parser = Parser(tokens);
  HashTable<String, Node*> funcs = parser.parse();

  while (System::Update()) {
    Cursor::RequestStyle(CursorStyle::Hidden);
  }
}
