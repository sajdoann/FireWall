/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/18/2020
*/

#include "Coords.h"
#include "../Board/Board.h"


bool Coords::isOnBoard(Board *b) const {
    return b->MaxX() > x && x >= 0 && b->MaxY() > y && y >= 0;
}

std::vector<Coords> Coords::getNeighbours(Board *board) {
    vector<Coords> c;
    int xC[4] = {-1, 1, 0, 0};
    int yC[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int neibX = xC[i] + x;
        int neibY = yC[i] + y;
        Coords neibCoords = Coords(neibX, neibY);
        if (!neibCoords.isOnBoard(board))
            continue;
        //is a patch -> cannot step
        auto a = board->At(neibCoords);
        if (!a->isEmpty() && !a->isMovingObject()) continue;
        c.push_back(neibCoords);
    }
    return c;
}

Coords &Coords::operator=(const Coords &other) {
    if (*this == other) return *this;
    x = other.x;
    y = other.y;
    return *this;
}
