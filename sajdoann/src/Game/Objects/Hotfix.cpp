/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Hotfix.h"
#include "../Board/Board.h"

ostream &Hotfix::SaveObject(ostream &out) {
    out << name << " ";
    MovementToOut(out, movementType);
    out << " ";
    DirectionsToOut(out, movementDirection);
}

void Hotfix::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    Coords *targetCoords = strategy->Move(oldBoard, newBoard, startCoords);
    if (targetCoords == nullptr) return;
    strategy->execMove(oldBoard->At(startCoords), newBoard, *targetCoords);
    delete targetCoords;
}
