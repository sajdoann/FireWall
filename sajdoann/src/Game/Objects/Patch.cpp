/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Patch.h"
#include "../Board/Board.h"

Patch::Patch(Patch &patch) {
    *this = patch;
}

int Patch::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    if (!canShoot()) return 0;

    Object *o = (*oldBoard)(startCoords.X(), startCoords.Y());
    Patch *patch = (Patch *) o;
    Hotfix h = (patch->ShootHotfix());


    Coords *targetCoords = h.getStrategy()->getMovedCoords(startCoords);
    h.getStrategy()->execMove(&h, newBoard, oldBoard, startCoords, *targetCoords);
    h.setInserted(true);
    delete targetCoords;
    return 0;
}