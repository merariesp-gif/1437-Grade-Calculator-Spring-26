#ifndef EXAM_H
#define EXAM_H

#include "GradedItem.h"

class Exam : public GradedItem {
public:
    Exam(string n, float e, float p)
        : GradedItem(n, e, p) {}

    string getCategory() const override {
        return "Exam";
    }
};

#endif
