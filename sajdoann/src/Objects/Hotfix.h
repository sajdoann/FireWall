/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/7/2020
*/

#pragma once

#include <functional>
#include "Object.h"
#include "MovingObject.h"
#include "MovingInterface.h"

using namespace std;

/**
 * moving object that is emited by patches
 * it travels on board till it encounters other object, then its destroyed (if encounters virus it takes its one live away)
 */
class Hotfix : public MovingObject {
    char name;

public:

    Hotfix(MovementType movementType, MovementDirection movementDirection) : MovingObject(movementType,
                                                                                          movementDirection) {}

    ~ Hotfix() = default;

    bool isVirus() const { return false; };

    ostream &PrintObject(ostream &os) {
        os << name;
    }

    istream &LoadObject(istream &is) {
        is >> name;
        if (is.eof()) return is;
        MovementFromIn(is, movementType);
        DirectionFromIn(is, movementDirection);

    }

    ostream &PrintInfo(ostream &os) const override {
        os << name << " ";
        MovementToOut(os, movementType);
        DirectionsToOut(os, movementDirection);
        //<< " "  << movementDirection;
    }


};

