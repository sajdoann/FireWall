/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Patch.h"
#include "../Board/Board.h"

Patch::Patch(Patch &patch) {
    *this = patch;
}

void Patch::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    if (!canShoot()) return;

    Object *o = (*oldBoard)(startCoords.X(), startCoords.Y());
    Patch *patch = (Patch *) o;
    Hotfix h = patch->ShootHotfix();
    Coords targetCoords = h.getStrategy()->getMovedCoords(startCoords);

    //stepping out of board or stepping on patch
    if (!targetCoords.canStep(&newBoard) ||
        (!newBoard.At(targetCoords)->isEmpty() && !newBoard.At(targetCoords)->isMovingObject()))
        return;

    //place is not empty -> is a moving object
    if (!newBoard.At(targetCoords)->isEmpty()) {
        //TODO: take lives away
    }

    newBoard.InsertObject(h, targetCoords);
}