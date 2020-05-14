/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Hotfix.h"

ostream &Hotfix::SaveObject(ostream &out) {
    out << name << " ";
    MovementToOut(out, movementType);
    out << " ";
    DirectionsToOut(out, movementDirection);
}

void Hotfix::Attack(Board *board, Coords startCoords) {
    strategy->Move(board, startCoords);
}
