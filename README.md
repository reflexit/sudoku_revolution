# Sudoku Revolution

Automatic Sudoku solver written in C++

The main idea is recursion and backtrace. Since the Sudoku problem is known to be NP-complete, this algorithm runs in super-polynomial time. However, due to the small problem size (9*9), it can solve most problems very quickly (~0.02s on my PC for the provided example).

## Prerequisites

- g++

## How to run

Command to build executable:

```
g++ -o sudoku_revolution src/sudoku_revolution.cpp
```

Command to run:

```
./sudoku_revolution
```

You will need to choose how to input the Sudoku problem:
- If you choose `keyboard`, input the Sudoku values in the same format as the provided example.
- If you choose `file`, indicate the file path.

The provided example is located at `resource/sudoku.txt`.
