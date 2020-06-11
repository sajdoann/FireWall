/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#pragma once

#include "../Movement/MovementDirection.h"
#include "../Objects/Coords.h"

class Board;

class Object;

class Strategy {
protected:
    MovementDirection movementDirection = MovementDirection::RIGHT;
public:
    // Strategy() = default;

    Strategy(MovementDirection movementDirection) : movementDirection(movementDirection) {}

    virtual ~Strategy() = default;

    virtual Strategy *Clone() const = 0;

    /**
     * gets where object on start position should be moved (target position)
     * @param oldBoard - board from which we take objects
     * @param newBoard  - board to which we insert objects
     * @param startCoords - start position of object we will be moving
     * @return target coords
     */
    virtual Coords *getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) = 0;

    /**
     * executes move, places object to target coords if all conditions are met
     * @param object - what will we move
     * @param newBoard - the board it is inserted to
     * @param targetCoords - the position object is inserted to
     */
    int
    execMove(Object *object, Board &newBoard, Board *oldBoard, const Coords &startCoords, const Coords &targetCoords);

    Coords *getMovedCoords(const Coords &startCoords);


};

