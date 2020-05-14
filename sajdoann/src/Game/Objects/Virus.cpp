/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/
#include "Virus.h"

ostream &Virus::SaveObject(ostream &out) {
    out << name << setw(10) << lives << setw(10);
    MovementToOut(out, movementType);
    out << setw(10);
    DirectionsToOut(out, movementDirection);
    return out;
}


