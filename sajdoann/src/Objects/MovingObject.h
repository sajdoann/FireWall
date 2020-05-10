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
class MovingObject : public Object {
    MovementType movementType = MovementType::STRAIGHT;
    MovementDirection movementDirection = MovementDirection::RIGHT;

public:
    MovingObject() : Object() {};

    virtual ~MovingObject() = default;

    MovementType MovementTypeObject() const { return movementType; }

    MovementDirection MovementDirectionObject() const { return movementDirection; }


    //object methods

    virtual ostream &PrintObject(ostream &os) override = 0;

    virtual ostream &PrintInfo(ostream &os) override = 0;

    bool isMovingObject() override { return true; }

};



