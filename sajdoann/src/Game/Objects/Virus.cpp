/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Virus.h"
#include "../Board/Board.h"
#include "MovingObject.h"
#include "Object.h"
#include "ObjectWithMoveAttributes.h"

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
    char n;
    in >> n;
    if (in.eof())
        return in;
    v.name = n;

    if (v.check_input_state(!(in.good()), in)) return in;

    int liv;
    in >> liv;
    if (v.check_input_state(!(in.good()) || liv <= 0, in)) return in;
    v.lives = liv;

    MovementType mt = MovementType::SHORTEST;
    v.MovementFromIn(in, mt);
    if (v.check_input_state(!(in.good()), in)) return in;

    MovementDirection md = MovementDirection::LEFT;
    v.DirectionFromIn(in, md);
    if (v.check_input_state(!(in.good()), in)) return in;

    v.movementType = mt;
    v.movementDirection = md;
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
    if (lives > 1) {
        --lives;
        return true;
    }
    return false;
}




