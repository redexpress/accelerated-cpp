# Accelerated C++ — 解答与练习

[English](README.md) | [简体中文](README.zh.md)

学习 Andrew Koenig 与 Barbara E. Moo 合著《Accelerated C++》（2000）的代码。
`source/` 存放书上的参考代码，`exercise/` 存放我的解答与变体。C++23。

## 目录

- `source` — 书上原版代码
- `exercise` — 我的练习

## 测试环境

- MSVC 19.30+（Windows）
- GCC 13+（Linux）
- Apple Clang 15+（macOS，部分 C++23 特性使用 feature-test 回退）

CMake >= 3.28。

## 构建

```shell
./build.sh
```

## 代码风格

- `source/` — 沿用原书风格：`using std::xxx;`，Allman 大括号独占一行。
- `exercise/` — 现代 C++23：完全限定 `std::`（不使用 `using` 声明），Allman 大括号与语句同行。
