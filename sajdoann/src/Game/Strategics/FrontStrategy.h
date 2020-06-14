/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#pragma once

#include "Strategy.h"
/**
 * object with tis strategy always continues it the direction that was given to it
 */
class FrontStrategy : public Strategy {

public:
    FrontStrategy() = default;

    FrontStrategy(MovementDirection movementDirection) : Strategy(movementDirection) {}

    /** gets target coords */
    Coords *getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) override;

    Strategy *Clone() const override {
        return new FrontStrategy(movementDirection);
    }
};

