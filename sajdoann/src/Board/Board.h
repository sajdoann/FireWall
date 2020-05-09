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

    Board(int maxX, int maxY, set<Coords> coords) : Board(maxX, maxY) {
        for (auto &coord : coords) {
            Patch *defaultPatch = new Patch();
            InsertPatch(defaultPatch, coord);
        }
    }

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

    bool OutOfBoard(const Coords &coords) const {
        return coords.X() > maxX || coords.X() < 0 || coords.Y() > maxY || coords.Y() < 0;
    }

    void InsertPatch(Patch *patch, const Coords &coords) {
        delete tiles[coords.X()][coords.Y()];
        //tiles[coords.X()][coords.Y()] = nullptr;
        tiles[coords.X()][coords.Y()] = new Patch();
        tiles[coords.X()][coords.Y()] = move(patch);
        patch = nullptr;
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

