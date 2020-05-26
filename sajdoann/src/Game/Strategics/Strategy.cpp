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
    // it should never happen that virus encounters patch
    if (!objectTarget->isEmpty() && !objectTarget->isMovingObject()) {
        return;
    }


    //target position is not empty -> deal with collisions
    if (!objectTarget->isEmpty()) {
        // cout << "interaction should be there\n";
        //virus steps on hotfix
        if (object->isVirus() && !objectTarget->isVirus()) {
            ((Virus *) object)->Hitted();
        }
        //interaction with objects
        //  object->Interact(objectTarget);
    }

    //abstract method needs exact type
    if (!object->isEmpty() && object->isMovingObject() && !object->isVirus())
        newBoard.InsertObject(*((Hotfix *) object), targetCoords);
    else if (object->isMovingObject() && object->isVirus())
        newBoard.InsertObject(*((Virus *) object), targetCoords);

}
