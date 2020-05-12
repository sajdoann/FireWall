/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <ostream>
#include "Object.h"

using namespace std;

class Empty : public Object {
    char name = '-';

public:
    Empty() : Object('-') {};

    ~Empty() = default;

    ostream &SaveObject(ostream &os) override { os << *this; }

    ostream &PrintInfo(ostream &os) const { os << "empty"; }

    bool isMovingObject() const override { return false; }

    bool isEmpty() const override { return true; }

    bool isVirus() const { return false; }


    friend ostream &operator<<(ostream &os, const Empty &empty) {
        os << "-";
    }

    istream &LoadObject(istream &is) {
        is >> name;
    }

};