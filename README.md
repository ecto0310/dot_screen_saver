# Dot Screen Saver

Interpreter to draw dots for screen saver.

## Requirement

- [Siv3D SDK](https://siv3d.github.io/) v0.6.10
- [CMake](https://cmake.org/) v3.12

## Usage

```bash
cmake -S . -B build
cmake --build build
./dot_screen_saver
```

## Program

[BNF](bnf.txt)

- [[x,y]] is a variable indicating the color of the next frame
- [x,y] is a constant indicating the color of the current frame
- The color specification indicates RGB using the lower 24 bits
