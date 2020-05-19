/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "StraightStrategy.h"
#include "../Board/Board.h"

bool StraightStrategy::Move(Board *oldBoard, Board &newBoard, const Coords &startCoords) {
    //Coords targetCoords(startCoords.X(), startCoords.Y() + 1);
    Coords targetCoords = getMovedCoords(startCoords);
    if (!targetCoords.canStep(&newBoard)) {
        newBoard.setEmpty(startCoords);
        return true;
    }

    Object *o = newBoard.At(targetCoords);

    //hotfix condition -> if just inserted dont move
    if (!o->isVirus() && o->isMovingObject()) {
        Hotfix *hotfix = (Hotfix *) o;
        hotfix->setInsertedFalse();
        return true;
    }

    //there is patch on target position
    if (!o->isEmpty() && !o->isMovingObject()) {
        //newBoard.setEmpty(startCoords);
        return true;
    }

    newBoard.InsertObject(*((Hotfix *) oldBoard->At(startCoords)), targetCoords);
    //newBoard.setEmpty(startCoords);

    return true;
}
