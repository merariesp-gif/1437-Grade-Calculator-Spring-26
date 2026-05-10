# USER GUIDE - Grade Calculator (OOP Edition)

## Introduction

The Grade Calculator is a C++ console application that helps users manage and calculate course grades. Users can add homework assignments, quizzes, and exams, customize grading weights, remove items, and calculate final grades using either a points-based or weighted grading system.

This application was developed as a final project for COSC 1437 and demonstrates object-oriented programming concepts including inheritance, polymorphism, vectors, smart pointers, and menu-driven program design.

---

# Getting Started

## Build the Program

Compile using g++:

```bash
g++ -std=c++17 *.cpp -o GradeCalculator
```

## Run the Program

### macOS / Linux
```bash
./GradeCalculator
```

### Windows
```bash
GradeCalculator.exe
```

---

# Main Menu

When the program starts, the following menu appears:

```text
1 Set Scheme
2 Add Homework
3 Add Quiz
4 Add Exam
5 View Items
6 Remove Item
7 Calculate Points-Based Grade
8 Calculate Weighted Grade
0 Exit
```

---

# Menu Walkthrough

## 1. Set Scheme

Allows the user to customize:

- Homework weight
- Quiz weight
- Exam weight
- Letter grade cutoffs

### Input Requirements
- Weights must be numeric values
- Total weights must equal 100%
- Grade cutoffs should be entered as percentages

### Example
```text
Homework %: 20
Quiz %: 30
Exam %: 50
```

---

## 2. Add Homework

Adds a homework assignment to the gradebook.

### Information Required
- Assignment name
- Points possible
- Points earned

### Input Rules
- Points possible must be greater than 0
- Points earned cannot exceed points possible

---

## 3. Add Quiz

Adds a quiz item to the gradebook.

### Information Required
- Quiz name
- Points possible
- Points earned

---

## 4. Add Exam

Adds an exam item to the gradebook.

### Information Required
- Exam name
- Points possible
- Points earned

---

## 5. View Items

Displays all graded items in a formatted table.

### Displayed Information
- Item number
- Name
- Category
- Points earned
- Points possible
- Percentage

### Example
```text
#   Name           Type       Earned   Possible   Percent
1   Homework 1     Homework   90       100        90%
2   Quiz 1         Quiz       45       50         90%
```

---

## 6. Remove Item

Removes a graded item from the list.

### Steps
1. Enter the item number
2. Confirm removal

### Example
```text
Enter item number: 2
Are you sure? (y/n): y
```

---

## 7. Calculate Points-Based Grade

Calculates the final grade using:

```text
Total points earned ÷ total points possible
```

### Output
- Final percentage
- Letter grade

---

## 8. Calculate Weighted Grade

Calculates the final grade using category averages and grading weights.

### Formula
```text
Homework Average × Homework Weight
+ Quiz Average × Quiz Weight
+ Exam Average × Exam Weight
```

### Output
- Weighted final percentage
- Letter grade

---

# Sample Session

```text
====================================
GRADE CALCULATOR
====================================

1 Set Scheme
2 Add Homework
3 Add Quiz
4 Add Exam
5 View Items
6 Remove Item
7 Calculate Points-Based Grade
8 Calculate Weighted Grade
0 Exit

Choice: 2

Name: Homework 1
Possible: 100
Earned: 95

Added!

Choice: 3

Name: Quiz 1
Possible: 50
Earned: 45

Added!

Choice: 5

#   Name           Type       Earned   Possible   Percent
1   Homework 1     Homework   95       100        95%
2   Quiz 1         Quiz       45       50         90%

Choice: 7

Final: 93.3%
Letter: A
```

---

# Sprint Features

## Sprint 19 - Input Validation
The program prevents invalid numeric input and menu choices from crashing the application.

## Sprint 20 - Additional Functionality
Users can remove items and customize grading schemes.

## Sprint 21 - UI Improvements
ANSI color formatting is used to display grade results visually.

## Sprint 22 - Final Polish
The application includes formatted tables, dashboard summaries, and improved menu organization.

---

# Understanding Your Results

## Points-Based Grade
Calculates the overall grade by dividing total earned points by total possible points.

This method works best when all assignments should count equally by point value.

## Weighted Grade
Calculates category averages separately and applies category weights.

This method works best for courses where homework, quizzes, and exams contribute different percentages to the final grade.

---

# Known Limitations

- Data is not permanently saved after the program closes unless file saving is implemented.
- ANSI color formatting may not display correctly on some Windows terminals.
- Very long assignment names may affect table formatting.

---

# Troubleshooting

## Problem: Program says "Invalid input"
Cause:
A non-numeric value was entered where a number was expected.

Fix:
Enter a valid integer or decimal number.

---

## Problem: Weights do not total 100%
Cause:
Homework, quiz, and exam weights must add to exactly 100%.

Fix:
Re-enter weights so the total equals 100.

---

## Problem: No items appear in calculations
Cause:
No assignments have been added yet.

Fix:
Use Add Homework, Add Quiz, or Add Exam before calculating grades.
