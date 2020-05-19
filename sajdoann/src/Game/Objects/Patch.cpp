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
    Hotfix h = (patch->ShootHotfix());
    //h.Attack(oldBoard, newBoard, startCoords);
    //h.setInserted(true);
    Coords *targetCoords = h.getStrategy()->getMovedCoords(startCoords);
    h.setInserted(false);
    h.getStrategy()->execMove(&h, newBoard, *targetCoords);
    h.setInserted(true);
    delete targetCoords;

    /* //stepping out of board or stepping on patch
     if (!targetCoords.canStep(oldBoard) ||
         (!newBoard.At(targetCoords)->isEmpty() && !newBoard.At(targetCoords)->isMovingObject()))
         return;

     //place is not empty -> is a moving object
     if (!newBoard.At(targetCoords)->isEmpty()) {
         //TODO: take lives away
         cout << "not empty" << targetCoords.X() << " " << targetCoords.Y() << " " << endl;
         return;
     }

     newBoard.InsertObject(h, targetCoords);*/
}