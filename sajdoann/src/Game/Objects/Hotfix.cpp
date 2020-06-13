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

Hotfix &Hotfix::operator=(const Hotfix &other) {
    if (this == &other) return *this;
    name = other.name;
    strategy = other.strategy->Clone();
    movementType = other.movementType;
    movementDirection = other.movementDirection;
    return *this;
}

istream &Hotfix::LoadObject(istream &is) {
    is >> name;
    if (is.eof()) return is;
    MovementFromIn(is, movementType);
    DirectionFromIn(is, movementDirection);
    setStrategy();

}

ostream &Hotfix::PrintInfo(ostream &os) const {
    os << "hotfix :" << name << "movement: ";
    MovementToOut(os, movementType);
    os << " direction: ";
    DirectionsToOut(os, movementDirection);
}
