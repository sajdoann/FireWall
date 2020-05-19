/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Strategy.h"
#include "../Board/Board.h"

void Strategy::execMove(Object *object, Board &newBoard, const Coords &targetCoords) {
    if (!targetCoords.canStep(&newBoard)) {
        return;
    }

    Object *objectTarget = newBoard.At(targetCoords);

    //there is patch on target position
    if (!objectTarget->isEmpty() && !objectTarget->isMovingObject()) {
        return;
    }


    //abstract method needs exact type
    if (!object->isEmpty() && object->isMovingObject() && !object->isVirus())
        newBoard.InsertObject(*((Hotfix *) object), targetCoords);
    else if (object->isMovingObject() && object->isVirus())
        newBoard.InsertObject(*((Virus *) object), targetCoords);

}
