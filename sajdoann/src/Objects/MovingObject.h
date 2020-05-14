/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iosfwd>
#include "Object.h"
#include "../Movement/MovementType.h"
#include "../Movement/MovementDirection.h"

using namespace std;

/**
 * class that roofs moving objects, it remembers movement type and direction
 */
class MovingObject : public ObjectWithMoveAttributes {

public:
    MovingObject() = default;

    MovingObject(char name, MovementType movementType, MovementDirection movementDirection)
            : ObjectWithMoveAttributes(name, movementType, movementDirection) {};

    virtual ~MovingObject() = default;

    virtual Object * Clone() const override = 0;


    bool isEmpty() const { return false; }

    MovementType MovementTypeObject() const { return movementType; }

    MovementDirection MovementDirectionObject() const { return movementDirection; }


    //object methods

    virtual ostream &SaveObject(ostream &out) override = 0;

    virtual ostream &PrintInfo(ostream &out) const override = 0;


    bool isMovingObject() const override { return true; }

    virtual bool isVirus() const = 0;
};



