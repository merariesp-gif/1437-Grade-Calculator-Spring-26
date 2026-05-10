#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include <string>

using namespace std;

class GradedItem {
protected:
    string name;
    float pointsEarned;
    float pointsPossible;

public:
    GradedItem(string n, float e, float p)
        : name(n), pointsEarned(e), pointsPossible(p) {}

    virtual ~GradedItem() {}

    string getName() const {
        return name;
    }

    float getPointsEarned() const {
        return pointsEarned;
    }

    float getPointsPossible() const {
        return pointsPossible;
    }

    float getPercentage() const {
        if (pointsPossible == 0)
            return 0;

        return (pointsEarned / pointsPossible) * 100;
    }

    virtual string getCategory() const = 0;
};

#endif
