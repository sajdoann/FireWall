/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/10/2020
*/

#include "Board.h"

Board::Board(Board &other) {
    *this = other;
}

void Board::ClearButPatches() {
    for (int i = 0; i < MaxX(); ++i) {
        for (int j = 0; j < MaxY(); ++j) {
            Coords c(i, j);
            if (!At(c)->isPatch())
                setEmpty(c);

        }
    }
}

Board &Board::operator=(Board &other) {
    if (this == &other) return *this;

    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            delete tiles[i][j];
            tiles[i][j] = nullptr;
        }
    }

    //because I use push back
    // -> needs to free the row to so the rows dont get to be placed after previous rows
    for (int k = 0; k < maxX; ++k) {
        tiles.pop_back();
    }

    maxX = other.maxX;
    maxY = other.maxY;
    for (int i = 0; i < maxX; ++i) {
        vector<Object *> tmp;
        for (int j = 0; j < maxY; ++j) {
            tmp.push_back(other.tiles[i][j]->Clone());
        }
        tiles.push_back(tmp);
    }
    return *this;
}

Board::~Board() {
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            delete tiles[i][j];
            tiles[i][j] = nullptr;
        }
    }

}

void Board::InsertPatch(Patch &patch, const Coords &coords) {
    delete tiles[coords.X()][coords.Y()];
    tiles[coords.X()][coords.Y()] = nullptr;
    tiles[coords.X()][coords.Y()] = new Patch(patch);
}

void Board::setEmpty(const Coords &coords) {
    Object *object = tiles[coords.X()][coords.Y()];
    if (object->isEmpty()) return;
    delete object;
    tiles[coords.X()][coords.Y()] = new Empty();
}

void Board::AddAllPatches(Board *other) {
    //for all tiles, if tile is a patch insert it to this board
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            Object *o = (Object *) (other->At(Coords(i, j)));
            if (!o->isEmpty() && !o->isMovingObject()) {
                Patch *p = (Patch *) o;
                InsertObject(*p, Coords(i, j));
            }
        }
    }
}
