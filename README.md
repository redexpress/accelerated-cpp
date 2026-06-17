# Accelerated C++ — Solutions and Exercises

[简体中文](README.zh.md) | [English](README.md)

My work through Andrew Koenig & Barbara E. Moo, *Accelerated C++* (2000).
Book reference code in `source/`; my solutions and variations in `exercise/`. C++23.

## Layout

- `source` — code from the book
- `exercise` — my exercises

## Tested with

- MSVC 19.30+ on Windows
- GCC 13+ on Linux
- Apple Clang 15+ on macOS (with feature-test fallbacks for some C++23 features)

CMake >= 3.28.

## Build

```shell
./build.sh
```

## Code style

- `source/` — original book style: `using std::xxx;`, Allman braces on their own line.
- `exercise/` — modern C++23: fully qualified `std::` (no `using` declarations), Allman braces on the same line as the statement.
