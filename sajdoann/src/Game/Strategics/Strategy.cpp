/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Strategy.h"
#include "../Board/Board.h"

int Strategy::execMove(Object *object, Board &newBoard, Board *oldBoard, const Coords &startCoords,
                       const Coords &targetCoords) {
    if (!targetCoords.isOnBoard(&newBoard)) {
        if (!object->isVirus()) return 0;
        //virus sucessfully gone
        if (object->isVirus() && startCoords.Y() == 0) {
            //todo
            return 1;
        }
        return 0;

    }

    Object *objectTarget = newBoard.At(targetCoords);

    //there is patch on target position
    // todo: it should never happen that virus encounters patch
    if (!objectTarget->isEmpty() && !objectTarget->isMovingObject()) {
        return 0;
    }


    //target position is not empty -> deal with collisions
    if (!objectTarget->isEmpty()) {

        //virus steps on hotfix -> if not virus alive after hitted destroy
        if (object->isVirus() && !objectTarget->isVirus()) {
            bool isAlive = ((Virus *) object)->Hitted();
            if (!isAlive) {
                oldBoard->setEmpty(startCoords);
                return 0;
            }
        }

        //todo: pokud chci vic jak jeden zivot pro patche zmenit

        // hotfix steps on virus
        if (!object->isVirus() && objectTarget->isVirus()) {
            bool isAlive = ((Virus *) objectTarget)->Hitted();
            if (!isAlive) {
                oldBoard->setEmpty(targetCoords);
                return 0;
            }
            return 0;
        }


    }

    //abstract method needs exact type
    if (!object->isEmpty() && object->isMovingObject() && !object->isVirus())
        newBoard.InsertObject(*((Hotfix *) object), targetCoords);
    else if (object->isMovingObject() && object->isVirus())
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
    if (movementDirection == MovementDirection::DIAGONAL_U) {
        return new Coords(startCoords.X() - 1, startCoords.Y() + 1);
    }
    if (movementDirection == MovementDirection::DIAGONAL_D) {
        return new Coords(startCoords.X() + 1, startCoords.Y() + 1);
    }
    //TODO: OSETRIT DEFAULT
    return nullptr;
}
