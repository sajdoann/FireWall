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
 * grid for objects in game
 * it stores the placement of Objects on Board
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
        }
    }

    Board(Board &other);

    Board &operator=(Board &other);

    /**
     * destructor that destructs board tiles
     */
    ~Board();

    int MaxX() const { return maxX; }

    int MaxY() const { return maxY; }

    /**
     * returns object at coords
     * @param coords
     * @return object
     */
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
    void InsertPatch(Patch &patch, const Coords &coords);

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

    /**
     * sets place at coords emtpy
     * @param coords
     */
    void setEmpty(const Coords &coords);


    /**
        * overload of () operator it returns the object on x,y
        * @param x
        * @param y
        * @return object on coords x,y
        */
    Object *operator()(int x, int y) const {
        return tiles[x][y];
    }

    /**
     * adds all patches to the other board (! they need to be of the same measurements)
     * @param other - other board
     */
    void AddAllPatches(Board *other);

    /**
     * clears all objects but patches
     */
    void ClearButPatches();
};

