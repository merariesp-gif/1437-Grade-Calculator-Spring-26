#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "GradedItem.h"

class Homework : public GradedItem {
public:
    Homework(string n, float e, float p)
        : GradedItem(n, e, p) {}

    string getCategory() const override {
        return "Homework";
    }
};

#endif
