/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iosfwd>
#include <iostream>
#include "Object.h"
#include "ObjectWithMoveAttributes.h"
#include "../Movement/MovementType.h"
#include "../Movement/MovementDirection.h"
#include "../Strategics/Strategy.h"
#include "../Strategics/FrontStrategy.h"
#include "../Strategics/RandomStrategy.h"
#include "../Strategics/BfsStrategy.h"

using namespace std;

/**
 * class that roofs moving objects
 * It remembers movement type, direction and strategy the moving object moves with.
 */
class MovingObject : public ObjectWithMoveAttributes {
protected:
    Strategy *strategy = nullptr;
public:
    MovingObject() {
        setStrategy();
    }

    MovingObject(char name, MovementType movementType, MovementDirection movementDirection)
            : ObjectWithMoveAttributes(name, movementType, movementDirection) {
        setStrategy();
    };

    virtual ~MovingObject() = default;

    virtual Object *Clone() const override = 0;

    /** virtual method for attack - object attack by this method */
    virtual int Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override = 0;

    /** moving object is not emty -> false */
    bool isEmpty() const override { return false; }

    /** moving object cannot be a patch */
    virtual bool isPatch() const override { return false; };

    /**
     * sets strategy for object
     */
    void setStrategy() {
        if (strategy != nullptr) {
            delete strategy;
        }
        if (movementType == MovementType::FRONT) {
            strategy = new FrontStrategy(movementDirection);
        } else if (movementType == MovementType::RAND) {
            strategy = new RandomStrategy(movementDirection);
        } else if (movementType == MovementType::SHORTEST) {
            strategy = new BfsStrategy(movementDirection);
        }

    }

    virtual ostream &SaveObject(ostream &out) override = 0;
    virtual ostream &PrintInfo(ostream &out) const override = 0;
    bool isMovingObject() const override { return true; }
    virtual bool isVirus() const override = 0;
};



