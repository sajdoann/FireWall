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

int Hotfix::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    Coords *targetCoords = strategy->getTargetCoords(oldBoard, newBoard, startCoords);
    if (targetCoords == nullptr) return 0;
    strategy->execMove(oldBoard->At(startCoords), newBoard, oldBoard, startCoords, *targetCoords);
    delete targetCoords;
    return 0;
}
