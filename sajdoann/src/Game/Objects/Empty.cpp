/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Empty.h"
#include "../Board/Board.h"

ostream &Empty::SaveObject(ostream &os) { os << *this; }

int Empty::Attack(Board *newBoard, Board &oldBoard, Coords startCoords) {
    return 0;
}

Empty &Empty::operator=(Empty &empty) {
    if (this == &empty) return *this;
    name = empty.name;
}
