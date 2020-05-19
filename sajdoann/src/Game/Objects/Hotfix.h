/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/7/2020
*/

#pragma once

#include <functional>
#include <iomanip>
#include "Object.h"
#include "MovingObject.h"
#include "../Strategics/Strategy.h"
#include "../Strategics/StraightStrategy.h"

using namespace std;

/**
 * moving object that is emited by patches
 * it travels on board till it encounters other object, then its destroyed (if encounters virus it takes its one live away)
 */
class Hotfix : public MovingObject {
    Strategy *strategy = new StraightStrategy(movementDirection);
    mutable bool just_inserted = true;

public:
    Hotfix() = default;

    Hotfix(char name, MovementType movementType, MovementDirection movementDirection)
            : MovingObject(name, movementType, movementDirection) {
        if (movementType == MovementType::STRAIGHT) {
            strategy = new StraightStrategy(movementDirection);
        }

    }

    ~ Hotfix() {
        delete strategy;
    }

    Hotfix(const Hotfix &other) {
        *this = other;
    }

    Hotfix &operator=(const Hotfix &other) {
        if (this == &other) return *this;
        name = other.name;
        movementType = other.movementType;
        movementDirection = other.movementDirection;
        return *this;
    }


    Object *Clone() const override { return new Hotfix(name, movementType, movementDirection); }


    bool isVirus() const { return false; };

    void setInsertedFalse() {
        just_inserted = false;
    }

    void Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override;

    Strategy *getStrategy() {
        return strategy;
    }

    ostream &SaveObject(ostream &out) override;

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

