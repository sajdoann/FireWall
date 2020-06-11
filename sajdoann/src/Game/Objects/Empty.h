/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iomanip>
#include "Object.h"

using namespace std;

class Board;

class Empty : public Object {
    char name = '-';

public:
    Empty() : Object('-') {};

    ~Empty() = default;

    Empty(Empty &e) { *this = e; }

    Empty &operator=(Empty &empty) {
        if (this == &empty) return *this;
        name = empty.name;
    }

    int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) override;


    Object *Clone() const override { return new Empty(); }


    ostream &SaveObject(ostream &os) override;

    ostream &PrintInfo(ostream &os) const { os << "empty"; }

    bool isMovingObject() const override { return false; }

    bool isEmpty() const override { return true; }

    bool isVirus() const { return false; }

    virtual bool isPatch() const { return false; }


    friend ostream &operator<<(ostream &os, const Empty &empty) {
        os << "-";
    }

    istream &LoadObject(istream &is) {
        is >> name;
    }

};