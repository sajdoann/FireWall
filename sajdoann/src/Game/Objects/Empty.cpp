/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "Empty.h"
#include "../Board/Board.h"

ostream &Empty::SaveObject(ostream &os) { os << *this; }

void Empty::Attack(Board *newBoard, Board &oldBoard, Coords startCoords) {
    return;
}
