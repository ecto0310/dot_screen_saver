#include <Siv3D.hpp>

#include "tokenizer.h"

void Main() {
  Scene::SetResizeMode(ResizeMode::Actual);
  Window::SetFullscreen(true);

  Tokenizer tokenizer(U"program");
  Array<Token> tokens = tokenizer.tokenize();

  while (System::Update()) {
    Cursor::RequestStyle(CursorStyle::Hidden);
  }
}
