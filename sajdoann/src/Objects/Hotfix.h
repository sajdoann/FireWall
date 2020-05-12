/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/7/2020
*/

#pragma once

#include <functional>
#include "Object.h"
#include "MovingObject.h"

using namespace std;

/**
 * moving object that is emited by patches
 * it travels on board till it encounters other object, then its destroyed (if encounters virus it takes its one live away)
 */
class Hotfix : public MovingObject {

public:

    Hotfix(char name, MovementType movementType, MovementDirection movementDirection) : MovingObject(name, movementType,
                                                                                                     movementDirection) {}

    ~ Hotfix() = default;

    bool isVirus() const { return false; };

    ostream &SaveObject(ostream &out) override {
        out << name << " ";
        MovementToOut(out, movementType);
        out << " ";
        DirectionsToOut(out, movementDirection);
    }

    istream &LoadObject(istream &is) {
        is >> name;
        if (is.eof()) return is;
        MovementFromIn(is, movementType);
        DirectionFromIn(is, movementDirection);

    }

    ostream &PrintInfo(ostream &os) const override {
        os << "name :" << name << "movement: ";
        MovementToOut(os, movementType);
        os << " direction: ";
        DirectionsToOut(os, movementDirection);
        //<< " "  << movementDirection;
    }


};

