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
    // Strategy() = default;

    Strategy(MovementDirection movementDirection) : movementDirection(movementDirection) {}

    virtual ~Strategy() = default;

    virtual bool Move(Board *oldBoard, Board &newBoard, const Coords &startCoords) = 0;

    Coords getMovedCoords(const Coords &startCoords) {
        if (movementDirection == MovementDirection::RIGHT) {
            return Coords(startCoords.X(), startCoords.Y() + 1);
        }
        if (movementDirection == MovementDirection::LEFT) {
            return Coords(startCoords.X(), startCoords.Y() - 1);
        }
        if (movementDirection == MovementDirection::DOWN) {
            return Coords(startCoords.X() + 1, startCoords.Y());
        }
        if (movementDirection == MovementDirection::UP) {
            return Coords(startCoords.X() - 1, startCoords.Y());
        }
        if (movementDirection == MovementDirection::DIAGONAL_U) {
            return Coords(startCoords.X() - 1, startCoords.Y() + 1);
        }
        if (movementDirection == MovementDirection::DIAGONAL_D) {
            return Coords(startCoords.X() + 1, startCoords.Y() + 1);
        }
    }


};

