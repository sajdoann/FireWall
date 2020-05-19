/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Coords.h"
#include "../Board/Board.h"


bool Coords::canStep(Board *b) {
    return b->MaxX() > x && x >= 0 && b->MaxY() > y && y >= 0;
}
