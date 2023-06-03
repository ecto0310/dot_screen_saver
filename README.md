# Dot Screen Saver

Interpreter to draw dots for screen saver.

## Requirement

- [Siv3D SDK](https://siv3d.github.io/) v0.6.10
- [CMake](https://cmake.org/) v3.20
- (Windows) [Microsoft Visual C++](https://visualstudio.microsoft.com/) 2022

## Usage

### Linux

```bash
# release
$ cmake -B build -DCMAKE_BUILD_TYPE=Release .
# debug
$ cmake -B build .

$ cmake --build build
$ ./dot_screen_saver
```

### Windows

```bash
$ cmake -B build .

# release
$ cmake --build build --config Release
$ cp program ./Release/program
$ ./Release/dot_screen_saver.exe

# debug
$ cmake --build build
$ cp program ./Debug/program
$ ./Debug/dot_screen_saver.exe
```


## Program

[BNF](bnf.txt)

- [[x,y]] is a variable indicating the color of the next frame
- [x,y] is a constant indicating the color of the current frame
- The color specification indicates RGB using the lower 24 bits
