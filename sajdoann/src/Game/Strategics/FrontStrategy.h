/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#pragma once

#include "Strategy.h"

class FrontStrategy : public Strategy {

public:
    FrontStrategy() = default;

    FrontStrategy(MovementDirection movementDirection) : Strategy(movementDirection) {}

    Coords *getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) override;

    Strategy *Clone() const {
        return new FrontStrategy(movementDirection);
    }
};

