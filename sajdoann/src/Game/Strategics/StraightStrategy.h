/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#pragma once

#include "Strategy.h"

class StraightStrategy : public Strategy {

public:
    StraightStrategy() = default;

    StraightStrategy(MovementDirection movementDirection) : Strategy(movementDirection) {}

    bool Move(Board *oldBoard, Board &newBoard, const Coords &startCoords) override;

};

