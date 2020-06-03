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

int Virus::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    Coords *targetCoords = strategy->getTargetCoords(oldBoard, newBoard, startCoords);
    //no next coord was found
    if (targetCoords == nullptr) {
        return 0;
    }
    int virusPoints = strategy->execMove(oldBoard->At(startCoords), newBoard, oldBoard, startCoords, *targetCoords);
    delete targetCoords;
    return virusPoints;
}



