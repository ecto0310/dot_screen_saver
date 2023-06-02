#include <Siv3D.hpp>

void Main() {
  Scene::SetResizeMode(ResizeMode::Actual);
  Window::SetFullscreen(true);

  while (System::Update()) {
    Cursor::RequestStyle(CursorStyle::Hidden);
  }
}
