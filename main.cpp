#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include <limits>
#include <cmath>
#include <fstream>
#include <algorithm>

#include "GradedItem.h"
#include "Homework.h"
#include "Exam.h"
#include "Quiz.h"

using namespace std;

/*
 * Grade Calculator (OOP Edition) — Final Project
 * Author: Merari Espinosa Torres
 * Course: COSC 1437, Spring 2026
 *
 * Concepts Demonstrated (Chapters 11-18 + Sprints 19-22)
 * ------------------------------------------------------
 * Ch 11 - std::vector, control flow, modular code
 * Ch 12 - STL algorithms: std::sort
 * Ch 13 - File I/O: saveGrades() / loadGrades()
 * Ch 14 - User-defined class: GradedItem
 * Ch 15 - Constructors, encapsulation, getPercentage()
 * Ch 16 - Menu-driven UI, switch statements, iomanip
 * Ch 17 - Inheritance + polymorphism
 * Ch 18 - Smart pointers with unique_ptr
 *
 * Sprint 19 - Input validation
 * Sprint 20 - Save/load grades from file
 * Sprint 21 - ANSI color output + dashboard
 * Sprint 22 - Sorting graded items
 */

// --------------------------------------------------
// STRUCT
// --------------------------------------------------
struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;

    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

// ---------------- INPUT HELPERS ----------------
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float getValidFloat(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void pause() {
    cout << "\nPress ENTER to continue...";
    cin.get();
}

// --------------------------------------------------
// UI HELPERS
// --------------------------------------------------
void clearScreen() {
    cout << string(50, '\n');
}

void header(const string& title) {
    cout << "\n==================================================\n";
    cout << title << '\n';
    cout << "==================================================\n";
}

void separator() {
    cout << "--------------------------------------------------\n";
}

string color(float percent) {
    if (percent >= 90)
        return "\033[32m"; // green
    else if (percent >= 70)
        return "\033[33m"; // yellow

    return "\033[31m"; // red
}

char getLetterGrade(float percent, const GradingScheme& scheme) {
    if (percent >= scheme.cutoffA) return 'A';
    if (percent >= scheme.cutoffB) return 'B';
    if (percent >= scheme.cutoffC) return 'C';
    if (percent >= scheme.cutoffD) return 'D';

    return 'F';
}

// --------------------------------------------------
// DASHBOARD
// --------------------------------------------------
void displayDashboard(const vector<unique_ptr<GradedItem>>& items) {
    int hw = 0;
    int qz = 0;
    int ex = 0;

    for (const auto& item : items) {
        if (item->getCategory() == "Homework")
            hw++;
        else if (item->getCategory() == "Quiz")
            qz++;
        else if (item->getCategory() == "Exam")
            ex++;
    }

    cout << "\nDASHBOARD\n";
    separator();

    cout << "Total Items: " << items.size() << '\n';
    cout << "Homework: " << hw
         << " | Quizzes: " << qz
         << " | Exams: " << ex << "\n\n";
}

// --------------------------------------------------
// MENU
// --------------------------------------------------
void displayMenu() {
    cout << "1. Set Grading Scheme\n";
    cout << "2. Add Homework\n";
    cout << "3. Add Quiz\n";
    cout << "4. Add Exam\n";
    cout << "5. View All Items\n";
    cout << "6. Remove Item\n";
    cout << "7. Calculate Points-Based Grade\n";
    cout << "8. Calculate Weighted Grade\n";
    cout << "9. Sort Items by Percentage\n";
    cout << "10. Save Grades\n";
    cout << "11. Load Grades\n";
    cout << "0. Exit\n";

    separator();
}

// --------------------------------------------------
// SET SCHEME
// --------------------------------------------------
void setScheme(GradingScheme& scheme) {
    header("SET GRADING SCHEME");

    float hw, qz, ex;

    while (true) {
        hw = getValidFloat("Homework Weight (%): ");
        qz = getValidFloat("Quiz Weight (%): ");
        ex = getValidFloat("Exam Weight (%): ");

        float total = hw + qz + ex;

        if (fabs(total - 100.0f) < 0.01f)
            break;

        cout << "Weights must total 100%.\n\n";
    }

    scheme.homeworkWeight = hw / 100.0f;
    scheme.quizWeight = qz / 100.0f;
    scheme.examWeight = ex / 100.0f;

    cout << "\nLetter Grade Cutoffs\n";

    scheme.cutoffA = getValidFloat("Minimum % for A: ");
    scheme.cutoffB = getValidFloat("Minimum % for B: ");
    scheme.cutoffC = getValidFloat("Minimum % for C: ");
    scheme.cutoffD = getValidFloat("Minimum % for D: ");

    cout << "\nGrading scheme updated.\n";

    pause();
}

// --------------------------------------------------
// ADD ITEM
// --------------------------------------------------
void addItem(vector<unique_ptr<GradedItem>>& items, int type) {
    header("ADD GRADED ITEM");

    string name;

    cout << "Assignment Name: ";
    getline(cin, name);

    float possible;
    float earned;

    while (true) {
        possible = getValidFloat("Points Possible: ");
        earned = getValidFloat("Points Earned: ");

        if (possible <= 0) {
            cout << "Possible points must be greater than 0.\n";
        }
        else if (earned < 0 || earned > possible) {
            cout << "Earned points must be between 0 and possible.\n";
        }
        else {
            break;
        }
    }

    if (type == 1)
        items.push_back(make_unique<Homework>(name, earned, possible));
    else if (type == 2)
        items.push_back(make_unique<Quiz>(name, earned, possible));
    else
        items.push_back(make_unique<Exam>(name, earned, possible));

    cout << "\nItem added successfully.\n";

    pause();
}

// --------------------------------------------------
// VIEW ITEMS
// --------------------------------------------------
void viewItems(const vector<unique_ptr<GradedItem>>& items) {
    header("ALL GRADED ITEMS");

    if (items.empty()) {
        cout << "No items entered.\n";
        pause();
        return;
    }

    cout << left
         << setw(5)  << "#"
         << setw(20) << "Name"
         << setw(15) << "Category"
         << right
         << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(12) << "Percent\n";

    separator();

    cout << fixed << setprecision(1);

    for (size_t i = 0; i < items.size(); i++) {
        cout << left
             << setw(5)  << (i + 1)
             << setw(20) << items[i]->getName()
             << setw(15) << items[i]->getCategory()
             << right
             << setw(10) << items[i]->getPointsEarned()
             << setw(10) << items[i]->getPointsPossible()
             << setw(11) << items[i]->getPercentage() << "%\n";
    }

    pause();
}

// --------------------------------------------------
// REMOVE ITEM
// --------------------------------------------------
void removeItem(vector<unique_ptr<GradedItem>>& items) {
    header("REMOVE ITEM");

    if (items.empty()) {
        cout << "No items to remove.\n";
        pause();
        return;
    }

    for (size_t i = 0; i < items.size(); i++) {
        cout << i + 1 << ". "
             << items[i]->getCategory()
             << " - "
             << items[i]->getName() << '\n';
    }

    int index = getValidInt("\nEnter item number to remove: ");

    if (index < 1 || index > static_cast<int>(items.size())) {
        cout << "Invalid item number.\n";
        pause();
        return;
    }

    cout << "Removed: " << items[index - 1]->getName() << '\n';

    items.erase(items.begin() + (index - 1));

    pause();
}

// --------------------------------------------------
// POINTS-BASED GRADE
// --------------------------------------------------
void calculatePointsBased(
    const vector<unique_ptr<GradedItem>>& items,
    const GradingScheme& scheme
) {
    header("POINTS-BASED GRADE");

    if (items.empty()) {
        cout << "No items entered.\n";
        pause();
        return;
    }

    float earned = 0;
    float possible = 0;

    for (const auto& item : items) {
        earned += item->getPointsEarned();
        possible += item->getPointsPossible();
    }

    float percent = (earned / possible) * 100.0f;

    cout << fixed << setprecision(1);

    cout << "Total Points: "
         << earned << " / " << possible << '\n';

    cout << color(percent)
         << "Final Percentage: " << percent << "%"
         << "\033[0m\n";

    cout << "Letter Grade: "
         << getLetterGrade(percent, scheme)
         << '\n';

    pause();
}

// --------------------------------------------------
// WEIGHTED GRADE
// --------------------------------------------------
void calculateWeighted(
    const vector<unique_ptr<GradedItem>>& items,
    const GradingScheme& scheme
) {
    header("WEIGHTED GRADE");

    if (items.empty()) {
        cout << "No items entered.\n";
        pause();
        return;
    }

    float hwTotal = 0;
    float hwCount = 0;

    float qzTotal = 0;
    float qzCount = 0;

    float exTotal = 0;
    float exCount = 0;

    for (const auto& item : items) {

        if (item->getCategory() == "Homework") {
            hwTotal += item->getPercentage();
            hwCount++;
        }

        else if (item->getCategory() == "Quiz") {
            qzTotal += item->getPercentage();
            qzCount++;
        }

        else if (item->getCategory() == "Exam") {
            exTotal += item->getPercentage();
            exCount++;
        }
    }

    float hwAvg = (hwCount > 0) ? hwTotal / hwCount : 0;
    float qzAvg = (qzCount > 0) ? qzTotal / qzCount : 0;
    float exAvg = (exCount > 0) ? exTotal / exCount : 0;

    float finalGrade =
        (hwAvg * scheme.homeworkWeight) +
        (qzAvg * scheme.quizWeight) +
        (exAvg * scheme.examWeight);

    cout << fixed << setprecision(1);

    cout << "Homework Average: " << hwAvg << "%\n";
    cout << "Quiz Average: " << qzAvg << "%\n";
    cout << "Exam Average: " << exAvg << "%\n\n";

    cout << color(finalGrade)
         << "Weighted Final Grade: "
         << finalGrade << "%"
         << "\033[0m\n";

    cout << "Letter Grade: "
         << getLetterGrade(finalGrade, scheme)
         << '\n';

    pause();
}

// --------------------------------------------------
// SORT ITEMS
// --------------------------------------------------
void sortItems(vector<unique_ptr<GradedItem>>& items) {
    header("SORT ITEMS");

    sort(items.begin(), items.end(),
        [](const unique_ptr<GradedItem>& a,
           const unique_ptr<GradedItem>& b) {

            return a->getPercentage() > b->getPercentage();
        });

    cout << "Items sorted by percentage.\n";

    pause();
}

// --------------------------------------------------
// SAVE FILE
// --------------------------------------------------
void saveGrades(const vector<unique_ptr<GradedItem>>& items) {
    ofstream file("grades.txt");

    if (!file) {
        cout << "Error saving file.\n";
        pause();
        return;
    }

    for (const auto& item : items) {
        file << item->getCategory() << '\n';
        file << item->getName() << '\n';
        file << item->getPointsEarned() << '\n';
        file << item->getPointsPossible() << '\n';
    }

    file.close();

    cout << "Grades saved to grades.txt\n";

    pause();
}

// --------------------------------------------------
// LOAD FILE
// --------------------------------------------------
void loadGrades(vector<unique_ptr<GradedItem>>& items) {
    ifstream file("grades.txt");

    if (!file) {
        cout << "No save file found.\n";
        pause();
        return;
    }

    items.clear();

    string category;
    string name;

    float earned;
    float possible;

    while (getline(file, category)) {

        getline(file, name);

        file >> earned;
        file >> possible;

        file.ignore();

        if (category == "Homework") {
            items.push_back(
                make_unique<Homework>(name, earned, possible));
        }

        else if (category == "Quiz") {
            items.push_back(
                make_unique<Quiz>(name, earned, possible));
        }

        else if (category == "Exam") {
            items.push_back(
                make_unique<Exam>(name, earned, possible));
        }
    }

    file.close();

    cout << "Grades loaded successfully.\n";

    pause();
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main() {

    GradingScheme scheme;

    vector<unique_ptr<GradedItem>> items;

    int choice;

    do {

        clearScreen();

        header("GRADE CALCULATOR");

        displayDashboard(items);

        displayMenu();

        choice = getValidInt("Enter choice: ");

        switch (choice) {

            case 1:
                setScheme(scheme);
                break;

            case 2:
                addItem(items, 1);
                break;

            case 3:
                addItem(items, 2);
                break;

            case 4:
                addItem(items, 3);
                break;

            case 5:
                viewItems(items);
                break;

            case 6:
                removeItem(items);
                break;

            case 7:
                calculatePointsBased(items, scheme);
                break;

            case 8:
                calculateWeighted(items, scheme);
                break;

            case 9:
                sortItems(items);
                break;

            case 10:
                saveGrades(items);
                break;

            case 11:
                loadGrades(items);
                break;

            case 0:
                header("GOODBYE");
                cout << "Thanks for using Grade Calculator!\n";
                break;

            default:
                cout << "Invalid menu option.\n";
                pause();
        }

    } while (choice != 0);

    return 0;
}
