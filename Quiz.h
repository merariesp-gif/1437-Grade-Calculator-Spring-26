#ifndef QUIZ_H
#define QUIZ_H

#include "GradedItem.h"

class Quiz : public GradedItem {
public:
    Quiz(string n, float e, float p)
        : GradedItem(n, e, p) {}

    string getCategory() const override {
        return "Quiz";
    }
};

#endif
