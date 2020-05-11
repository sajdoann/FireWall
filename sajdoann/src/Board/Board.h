/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <vector>
#include <set>
#include <iostream>

#include "../Objects/Object.h"
#include "../Objects/Empty.h"
#include "../Objects/Patch.h"
#include "../IOLoaders/Reader.h"

using namespace std;

/**
 * grid for objects, it stores the placement of Objects in the playing area
 */
class Board {
    int maxX;
    int maxY;
    vector<vector<Object *>> tiles;

public:
    Board() {}

    Board(int maxX, int maxY) : maxX(maxX), maxY(maxY) {
        for (int i = 0; i < maxX; ++i) {
            vector<Object *> tmp;
            for (int j = 0; j < maxY; ++j) {
                tmp.push_back(new Empty());
            }
            tiles.push_back(tmp);
        }
    }

    Board(int maxX, int maxY, map<Coords, Patch> coords) : Board(maxX, maxY) {
        auto c = coords.begin();
        for (auto c = coords.begin(), c != coords.end();
        ++coords) {
            Patch *defaultPatch = new Patch(coord.second);
            InsertPatch(*defaultPatch, coord.first);
            delete defaultPatch;
            //defaultPatch = nullptr;
        }
    }

//destructs other board
    Board &operator=(Board &other) {
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

    Board(Board &other) {
        *this = other;
    }

    ~Board() {
        for (int i = 0; i < maxX; ++i) {
            for (int j = 0; j < maxY; ++j) {
                delete tiles[i][j];
                tiles[i][j] = nullptr;
            }
        }

    }

    int MaxX() const { return maxX; }

    int MaxY() const { return maxY; }

    /**
     * finds out if coords are still in board
     * @param coords
     * @return true - coords are in board, false - not in board
     */
    bool OutOfBoard(const Coords &coords) const {
        return coords.X() > maxX || coords.X() < 0 || coords.Y() > maxY || coords.Y() < 0;
    }

    /**
     * inserts patch to the coords on board
     * @param patch
     * @param coords
     */
    void InsertPatch(Patch &patch, const Coords &coords) {
        delete tiles[coords.X()][coords.Y()];
        tiles[coords.X()][coords.Y()] = new Patch();
        *((Patch *) tiles[coords.X()][coords.Y()]) = patch;
    }

    /**
        * overload of () operator it returns the object on x,y
        * @param x
        * @param y
        * @return object on coords x,y
        */
    Object *operator()(int x, int y) const {
        return tiles[x][y];
    }


};

