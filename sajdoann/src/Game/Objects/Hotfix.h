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

    /**
     * clones hotfix
     * @return new hotfix
     */
    Object *Clone() const override { return new Hotfix(name, movementType, movementDirection); }

    /** hotfix is not a virus -> returns false */
    bool isVirus() const override { return false; };

    /** hotfix attack - moves by one */
    int Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override;

    /** gets strategy of hotfix */
    Strategy *getStrategy() { return strategy; }

    /** saves object */
    ostream &SaveObject(ostream &out) override;

    /** loads object */
    istream &LoadObject(istream &in) override;

    /** prints info about object */
    ostream &PrintInfo(ostream &out) const override;


};

