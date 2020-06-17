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
#include "../Strategics/FrontStrategy.h"
#include "../Strategics/RandomStrategy.h"

using namespace std;

/**
 * moving object that is emited by patches
 * it travels on board till it encounters other object, then its destroyed (if encounters virus it takes its one live away)
 */
class Hotfix : public MovingObject {

    mutable bool just_inserted = false;

public:
    Hotfix() = default;

    Hotfix(char name, MovementType movementType, MovementDirection movementDirection)
            : MovingObject(name, movementType, movementDirection) {

    }

    ~ Hotfix() override {
        delete strategy;
    }

    Hotfix(const Hotfix &other) { *this = other; }

    Hotfix &operator=(const Hotfix &other);


    Object *Clone() const override { return new Hotfix(name, movementType, movementDirection); }


    bool isVirus() const override { return false; };

    bool JustInserted() { return just_inserted; }

    void setInserted(bool w) {
        just_inserted = w;
    }

    int Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override;

    Strategy *getStrategy() { return strategy; }

    ostream &SaveObject(ostream &out) override;

    istream &LoadObject(istream &in) override;

    ostream &PrintInfo(ostream &out) const override;


};

