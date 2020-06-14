/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Virus.h"
#include "../Board/Board.h"

Virus &Virus::operator=(const Virus &other) {
    if (this == &other) return *this;
    if (strategy != nullptr) delete strategy;
    name = other.name;
    lives = other.lives;
    movementType = other.movementType;
    movementDirection = other.movementDirection;
    strategy = other.strategy->Clone();
    return *this;
}

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

ostream &operator<<(ostream &out, const Virus &virus) {
    out << virus.name << " " << virus.lives << " ";
    virus.MovementToOut(out, virus.movementType);
    out << " ";
    virus.DirectionsToOut(out, virus.movementDirection);
    return out;
}

istream &operator>>(istream &in, Virus &v) {
    in >> v.name;
    if (in.eof())
        return in;
    in >> v.lives;
    v.MovementFromIn(in, v.movementType);
    v.DirectionFromIn(in, v.movementDirection);
    v.setStrategy();
    return in;

}

ostream &Virus::PrintInfo(ostream &out) const {
    out << "virus: " << name << " lives: " << lives << " movement: ";
    MovementToOut(out, movementType);
    out << " directions: ";
    DirectionsToOut(out, movementDirection);
    return out << endl;
}

bool Virus::Hitted() {
    if (lives) {
        --lives;
        return true;
    }
    return false;
}




