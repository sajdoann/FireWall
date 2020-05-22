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
    int maxX = 0;
    int maxY = 0;
    vector<vector<Object *>> tiles;

public:
    Board() = default;

    Board(int maxX, int maxY) : maxX(maxX), maxY(maxY) {
        for (int i = 0; i < maxX; ++i) {
            vector<Object *> tmp;
            for (int j = 0; j < maxY; ++j) {
                tmp.push_back(new Empty());
            }
            tiles.push_back(tmp);
        }
    }

    Board(int maxX, int maxY, map<Coords, Patch *> coords) : Board(maxX, maxY) {
        auto c = coords.begin();
        for (; c != coords.end(); ++c) {
            Patch defaultPatch((*(c->second)));
            InsertPatch(defaultPatch, c->first);
            //delete defaultPatch;
            //defaultPatch = nullptr;
        }
    }

    Board(Board &other);

    Board &operator=(Board &other) {
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

    Object *At(const Coords &coords) { return tiles[coords.X()][coords.Y()]; }

    /**
     * finds out if coords are still in board
     * @param coords
     * @return true - coords are in board, false - not in board
     */
    bool OutOfBoard(const Coords &coords) const {
        return coords.X() >= maxX || coords.X() < 0 || coords.Y() >= maxY || coords.Y() < 0;
    }

    /**
     * inserts patch to the coords on board
     * @param patch
     * @param coords
     */
    void InsertPatch(Patch &patch, const Coords &coords) {
        delete tiles[coords.X()][coords.Y()];
        tiles[coords.X()][coords.Y()] = nullptr;
        tiles[coords.X()][coords.Y()] = new Patch(patch);
        //*((Patch *) tiles[coords.X()][coords.Y()]) = patch;
    }

    /**
     * template to insert object on board to coords
     * @tparam O type of Object
     * @param o name of object
     * @param coords  where o should be placed
     */
    template<typename O>
    void InsertObject(O &o, const Coords &coords) {
        // dynamic alocation of space in board, but O(type) o(name) is on stack -> gets out of scope (no need to free it)
        delete tiles[coords.X()][coords.Y()];
        tiles[coords.X()][coords.Y()] = new O();
        *((O *) tiles[coords.X()][coords.Y()]) = o;
    }

    void setEmpty(const Coords &coords) {
        Object *object = tiles[coords.X()][coords.Y()];
        if (object->isEmpty()) return;
        delete object;
        tiles[coords.X()][coords.Y()] = new Empty();
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

    void AddAllPatches(Board *board) {
        //if measurement are not the same throw errror
        if (board->maxX != maxX || board->maxY != maxY) {
            throw logic_error("Boards dont have the same size.");
        }

        //for all tiles, if tile is a patch insert it to this board
        for (int i = 0; i < maxX; ++i) {
            for (int j = 0; j < maxY; ++j) {
                Object *o = (Object *) (board->At(Coords(i, j)));
                if (!o->isEmpty() && !o->isMovingObject()) {
                    Patch *p = (Patch *) o;
                    InsertObject(*p, Coords(i, j));
                }
            }
        }
        /*cout << "add all p" << endl;
        for (int i = 0; i < maxX; ++i) {
            for (int j = 0; j < maxY; ++j) {
            cout <<  At(Coords(i,j));
            }
            cout << endl;
        }
        cout <<endl << endl;
        */
    }

    void Print();
};

