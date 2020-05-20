/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Virus.h"
#include "../Board/Board.h"

ostream &Virus::SaveObject(ostream &out) {
    out << name << setw(10) << lives << setw(10);
    MovementToOut(out, movementType);
    out << setw(10);
    DirectionsToOut(out, movementDirection);
    return out;
}

void Virus::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    Coords *targetCoords = strategy->getTargetCoords(oldBoard, newBoard, startCoords);
    if (targetCoords == nullptr)
        return;
    strategy->execMove(oldBoard->At(startCoords), newBoard, *targetCoords);
    delete targetCoords;
}



