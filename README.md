# Lexical Analyzer and Parser – Concepts of Programming Languages Project 2

This project implements a **lexical analyzer** and a **recursive descent parser** in C for a simplified programming language.  
It was developed as part of the *Concepts of Programming Languages* course at Texas Tech University.

## Features
- Tokenizes arithmetic expressions, operators, keywords (`if`, `else`, `begin`, `end`, `read`, `print`), and identifiers.
- Implements a recursive descent parser for assignments, arithmetic expressions, and conditional statements.
- Reports syntax errors with descriptive messages and line numbers.
- Includes a Makefile for compilation.

## Files
- `front.c` / `front.h` – Lexical analyzer
- `parser.c` / `parser.h` – Parser implementation
- `Makefile` – Build script

## Compilation
```bash
make
