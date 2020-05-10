/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/10/2020
*/

#include "Board.h"

Board::Board(int maxX, int maxY) : maxX(maxX), maxY(maxY) {
    for (int i = 0; i < maxX; ++i) {
        vector<Object *> tmp;
        for (int j = 0; j < maxY; ++j) {
            tmp.push_back(new Empty());
        }
        tiles.push_back(tmp);
    }
}

Board::Board(int maxX, int maxY, set<Coords> coords) : Board(maxX, maxY) {
    for (auto &coord : coords) {
        Patch *defaultPatch = new Patch();
        InsertPatch(defaultPatch, coord);
        //defaultPatch = nullptr;
    }
}

Board &Board::operator=(Board &other) {
    if (this == &other) return *this;
    maxX = other.maxX;
    maxY = other.maxY;
    for (int i = 0; i < maxX; ++i) {
        vector<Object *> tmp;
        for (int j = 0; j < maxY; ++j) {
            tmp.push_back(move(other.tiles[i][j]));
            other.tiles[i][j] = nullptr;
        }
        tiles.push_back(tmp);
    }
}

Board::Board(Board &other) {
    *this = other;
}

Board::~Board() {
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            delete tiles[i][j];
            tiles[i][j] = nullptr;
        }
    }

}

int Board::MaxX() const { return maxX; }

int Board::MaxY() const { return maxY; }

bool Board::OutOfBoard(const Coords &coords) const {
    return coords.X() > maxX || coords.X() < 0 || coords.Y() > maxY || coords.Y() < 0;
}

void Board::InsertPatch(Patch *patch, const Coords &coords) {
    delete (tiles[coords.X()][coords.Y()]);
    //tiles[coords.X()][coords.Y()] = nullptr;
//    tiles[coords.X()][coords.Y()] = new Patch();
    tiles[coords.X()][coords.Y()] = move(patch);
    patch = nullptr;
}


Object *Board::operator()(int x, int y) const {
    return tiles[x][y];
}
