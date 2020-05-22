/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Coords.h"
#include "../Board/Board.h"


bool Coords::canStep(Board *b) const {
    return b->MaxX() > x && x >= 0 && b->MaxY() > y && y >= 0;
}

std::vector<Coords> Coords::getNeighbours(Board *board) {
    vector<Coords> c;
    int xC[4] = {-1, 1, 0, 0};
    int yC[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int neibX = xC[i] + x;
        int neibY = yC[i] + y;
        if (canStep(board)) continue;
        //is a patch -> cannot step
        if (!board->At(Coords(neibX, neibY))->isEmpty() && !board->At(Coords(neibX, neibY))->isMovingObject()) continue;
        c.push_back(Coords(neibX, neibY));
    }
    return c;
}
