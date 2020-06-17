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
    return out;
}

int Hotfix::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    Coords *targetCoords = strategy->getTargetCoords(oldBoard, newBoard, startCoords);
    if (targetCoords == nullptr) return 0;
    strategy->execMove(oldBoard->At(startCoords), newBoard, oldBoard, startCoords, *targetCoords);
    delete targetCoords;
    return 0;
}

Hotfix &Hotfix::operator=(const Hotfix &other) {
    if (this == &other) return *this;
    name = other.name;
    strategy = other.strategy->Clone();
    movementType = other.movementType;
    movementDirection = other.movementDirection;
    return *this;
}

istream &Hotfix::LoadObject(istream &in) {
    in >> name;
    if (in.eof()) return in;
    MovementFromIn(in, movementType);
    DirectionFromIn(in, movementDirection);
    setStrategy();
    return in;
}

ostream &Hotfix::PrintInfo(ostream &out) const {
    out << "hotfix :" << name << "movement: ";
    MovementToOut(out, movementType);
    out << " direction: ";
    DirectionsToOut(out, movementDirection);
    return out;
}
