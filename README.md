# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items such as homework, quizzes, and exams. The program calculates both points-based and weighted grades using a customizable grading scheme and demonstrates object-oriented programming concepts including inheritance, polymorphism, and smart pointers.

## Author
Merari E. Torres - COSC 1437, Spring 2026

## Description
This application allows users to manage grades through a menu-driven interface. Users can add assignments, quizzes, and exams, customize grading weights, remove items, and calculate final grades using both points-based and weighted systems.

The project demonstrates object-oriented programming concepts learned throughout COSC 1437, including inheritance, polymorphism, vectors, smart pointers, modular programming, and formatted output.

## Features
- Menu-driven interface
- Add Homework, Quiz, and Exam items
- View all graded items in a formatted table
- Remove graded items
- Custom grading scheme
- Adjustable letter grade cutoffs
- Points-based grade calculation
- Weighted grade calculation
- Input validation
- ANSI color output
- Dashboard summary
- Smart pointers with `std::unique_ptr`
- Inheritance and polymorphism

## Files

| File | Purpose |
|------|----------|
| main.cpp | Driver program and menu system |
| GradedItem.h | Base class for all graded items |
| Homework.h | Derived Homework class |
| Quiz.h | Derived Quiz class |
| Exam.h | Derived Exam class |
| USER_GUIDE.md | End-user instructions |

## How to Build

Using g++:

```bash
g++ -std=c++17 *.cpp -o GradeCalculator
```

## How to Run

### macOS / Linux
```bash
./GradeCalculator
```

### Windows
```bash
GradeCalculator.exe
```

## Requirements
- C++17 compatible compiler
- g++, clang++, or MSVC

## Course Concepts Demonstrated

- Chapter 11 - Vectors, loops, modular programming
- Chapter 12 - STL algorithms
- Chapter 13 - File I/O concepts
- Chapter 14 - User-defined classes
- Chapter 15 - Constructors and encapsulation
- Chapter 16 - Menu-driven programs and formatting
- Chapter 17 - Inheritance and polymorphism
- Chapter 18 - Smart pointers and structs
- Sprint 19 - Input validation
- Sprint 20 - Additional functionality
- Sprint 21 - UI improvements and formatting
- Sprint 22 - Final polish and robustness
