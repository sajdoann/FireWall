/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#pragma once

#include "../Movement/MovementDirection.h"
#include "../Objects/Coords.h"

class Board;

class Strategy {
protected:
    MovementDirection movementDirection = MovementDirection::RIGHT;
public:
    Strategy() = default;

    Strategy(MovementDirection movementDirection) : movementDirection(movementDirection) {}

    virtual ~Strategy() = default;

    virtual bool Move(Board *board, const Coords &startCoords) = 0;


};

