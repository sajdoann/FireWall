/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Patch.h"
#include "../Board/Board.h"

Patch::Patch(Patch &patch) {
    *this = patch;
}

void Patch::Attack(Board *board, Coords startCoords) {
    if (!canShoot()) return;

    Object *o = (*board)(startCoords.X(), startCoords.Y());
    Patch *patch = (Patch *) o;
    Hotfix h = patch->ShootHotfix();
    board->InsertObject(h, Coords({startCoords.X(), startCoords.Y() + 1}));

    //StraightStrategy().Move(board, startCoords);
}