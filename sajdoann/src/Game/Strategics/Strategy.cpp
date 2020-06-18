/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Strategy.h"
#include "../Board/Board.h"

int Strategy::execMove(Object *object, Board &newBoard, Board *oldBoard, const Coords &startCoords,
                       const Coords &targetCoords) {
    //if target is out of board
    if (!targetCoords.isOnBoard(&newBoard)) {       //object is not inserted to newboard
        if (!object->isVirus()) return 0;
        if (object->isVirus() && startCoords.Y() == 0) {
            return 1;       //virus sucessfully on y=0 position -> plus point
        }
        return 0;
    }

    Object *objectTarget = newBoard.At(targetCoords);

    //there is patch on target position -> cannot step not copied
    if (objectTarget->isPatch()) {
        return 0;
    }


    //target position is not empty -> deal with collisions
    if (!objectTarget->isEmpty()) {
        // object target cannot be patch - upper consition
        //virus steps on hotfix -> if not virus alive after hitted destroy
        if (object->isVirus() && !objectTarget->isVirus()) {
            bool isAlive = ((Virus *) object)->Hitted();
            if (!isAlive) {
                oldBoard->setEmpty(startCoords);
            }
            oldBoard->setEmpty(targetCoords);
            return 0;
        }

        // hotfix steps on virus
        if (!object->isVirus() && objectTarget->isVirus()) {
            bool isAlive = ((Virus *) objectTarget)->Hitted();
            if (!isAlive) {
                oldBoard->setEmpty(targetCoords);
            }
            return 0;
        }


    }

    if (object->isMovingObject() && !object->isVirus())    //hotfix
        newBoard.InsertObject(*((Hotfix *) object), targetCoords);
    else if (object->isVirus())
        newBoard.InsertObject(*((Virus *) object), targetCoords);

    return 0;

}

Coords *Strategy::getMovedCoords(const Coords &startCoords) {
    if (movementDirection == MovementDirection::RIGHT) {
        return new Coords(startCoords.X(), startCoords.Y() + 1);
    }
    if (movementDirection == MovementDirection::LEFT) {
        return new Coords(startCoords.X(), startCoords.Y() - 1);
    }
    if (movementDirection == MovementDirection::DOWN) {
        return new Coords(startCoords.X() + 1, startCoords.Y());
    }
    if (movementDirection == MovementDirection::UP) {
        return new Coords(startCoords.X() - 1, startCoords.Y());
    }
    if (movementDirection == MovementDirection::DIAGONALU) {
        return new Coords(startCoords.X() - 1, startCoords.Y() + 1);
    }
    if (movementDirection == MovementDirection::DIAGONALD) {
        return new Coords(startCoords.X() + 1, startCoords.Y() + 1);
    }

    //default case
    return new Coords(startCoords.X() + 1, startCoords.Y() + 1);
}
