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

    Board(int maxX, int maxY);

    Board(int maxX, int maxY, set<Coords> coords);

    Board &operator=(Board &other);

    Board(Board &other);

    ~Board();

    int MaxX() const;

    int MaxY() const;

    /**
     * finds out if coords are still in board
     * @param coords
     * @return true - coords are in board, false - not in board
     */
    bool OutOfBoard(const Coords &coords) const;

    /**
     * inserts patch to the coords on board
     * @param patch
     * @param coords
     */
    void InsertPatch(Patch *patch, const Coords &coords);

    /**
     * overload of () operator it returns the object on x,y
     * @param x
     * @param y
     * @return object on coords x,y
     */
    Object *operator()(int x, int y) const;

};

