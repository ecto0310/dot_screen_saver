#include <Siv3D.hpp>

#include "parser.h"
#include "runner.h"
#include "tokenizer.h"

void Main() {
  Scene::SetResizeMode(ResizeMode::Actual);
  Window::SetFullscreen(true);

  Tokenizer tokenizer(U"program");
  Array<Token> tokens = tokenizer.tokenize();

  Parser parser = Parser(tokens);
  HashTable<String, Node*> funcs = parser.parse();

  System::Update();
  Size size = Window::GetState().virtualSize;

  Runner runner = Runner(funcs, size.x, size.y);

  runner.run(U"init");
  runner.run(U"draw");

  while (System::Update()) {
    Cursor::RequestStyle(CursorStyle::Hidden);

    runner.run(U"draw");
    runner.draw();
  }
}
