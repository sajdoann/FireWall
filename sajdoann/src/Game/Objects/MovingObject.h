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
 * class that roofs moving objects, it remembers movement type and direction
 */
class MovingObject : public ObjectWithMoveAttributes {
protected:
    Strategy *strategy = nullptr;
public:
    MovingObject() {
    }

    MovingObject(char name, MovementType movementType, MovementDirection movementDirection)
            : ObjectWithMoveAttributes(name, movementType, movementDirection) {
        setStrategy();
    };

    virtual ~MovingObject() = default;

    virtual Object *Clone() const override = 0;

    virtual void Attack(Board *oldBoard, Board &newBoard, Coords startCoords) = 0;


    bool isEmpty() const { return false; }

    MovementType MovementTypeObject() const { return movementType; }

    MovementDirection MovementDirectionObject() const { return movementDirection; }

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
        } else cout << "fck moving object" << endl;

    }

    //virtual bool Interact(Object * objectTarget) = 0;


    //object methods

    virtual ostream &SaveObject(ostream &out) override = 0;

    virtual ostream &PrintInfo(ostream &out) const override = 0;


    bool isMovingObject() const override { return true; }

    virtual bool isVirus() const = 0;
};



