/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Patch.h"
#include "../Board/Board.h"

Patch::Patch(Patch &patch) {
    *this = patch;
}

int Patch::Attack(Board *oldBoard, Board &newBoard, Coords startCoords) {
    if (!canShoot()) return 0;

    Object *o = (*oldBoard)(startCoords.X(), startCoords.Y());
    Patch *patch = (Patch *) o;
    Hotfix h = (patch->ShootHotfix());


    Coords *targetCoords = h.getStrategy()->getMovedCoords(startCoords);
    h.getStrategy()->execMove(&h, newBoard, oldBoard, startCoords, *targetCoords);
    h.setInserted(true);
    delete targetCoords;
    return 0;
}

Patch &Patch::operator=(const Patch &patch) {
    if (this == &patch) return *this;
    movementType = patch.movementType;
    movementDirection = patch.movementDirection;

    this->name = patch.name;
    this->price = patch.price;
    return *this;
}

istream &operator>>(istream &in, Patch &patch) {
    char n;
    in >> n;

    if (in.eof())   //no patch for input
        return in;

    if (patch.check_input_state(!(in.good()) || !isalpha(n), in)) return in;
    patch.name = toupper(n);

    int pr = -5;
    in >> pr;
    if (patch.check_input_state(!(in.good()) || pr < 0, in)) return in;
    patch.price = pr;

    patch.MovementFromIn(in, patch.movementType);
    if (!(in.good()) || patch.movementType == NONE) return in;

    patch.DirectionFromIn(in, patch.movementDirection);
    return in;
}

istream &Patch::LoadObject(istream &is) {
    is >> *this;
    return is;
}

ostream &Patch::PrintInfo(ostream &out) const {
    out << "patch: " << name << " price: " << price << " movement: ";
    MovementToOut(out, movementType);

    if (movementType == MovementType::NONE) return out << endl;

    out << " direction: ";
    DirectionsToOut(out, movementDirection);
    return out << endl;
}

ostream &Patch::SaveObject(ostream &os) {
    os << name << setw(15) << price << setw(15);
    MovementToOut(os, movementType);
    os << setw(15);

    if (movementType == MovementType::NONE) return os << endl;
    DirectionsToOut(os, movementDirection);
    return os;
}

ostream &Patch::Heading(ostream &os) {
    return os << "NAME" << setw(15) << "PRICE" << setw(15) << "MOVEMENT" << setw(15)
              << "DIRECTION" << endl;
}
