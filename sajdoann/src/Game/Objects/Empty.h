/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iomanip>
#include "Object.h"

using namespace std;

class Board;

/**
 * emty object its name is always -
 * can be placed on board
 */
class Empty : public Object {
    char name = '-';

public:
    Empty() : Object('-') {};

    ~Empty() = default;

    Empty(Empty &e) { *this = e; }

    Empty &operator=(Empty &empty);

    int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) override;

    Object *Clone() const override { return new Empty(); }


    ostream &SaveObject(ostream &os) override;

    ostream &PrintInfo(ostream &os) const { return os << "empty"; }

    bool isMovingObject() const override { return false; }

    bool isEmpty() const override { return true; }

    bool isVirus() const override { return false; }

    bool isPatch() const override { return false; }


    friend ostream &operator<<(ostream &os, const Empty &empty) { return os << "-"; }

    istream &LoadObject(istream &is) override { return is >> name; }

};