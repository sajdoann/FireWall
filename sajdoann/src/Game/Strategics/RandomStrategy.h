/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/19/2020
*/

#pragma once


#include "Strategy.h"
class Board;

class RandomStrategy : public Strategy {

public:
    RandomStrategy() = default;

    ~RandomStrategy() = default;


    virtual Coords *getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) override;

    RandomStrategy(MovementDirection movementDirection) : Strategy(movementDirection) {}

    Strategy *Clone() const {
        return new RandomStrategy(movementDirection);
    }
};



