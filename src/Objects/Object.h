/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include "Coords.h"

using namespace std;

class Object {
public:
    Object() = default;

    virtual ~Object() = default;

    virtual ostream &PrintBoard(ostream &os) = 0;

    virtual ostream &PrintInfo(ostream &os) = 0;

    friend std::ostream &operator<<(std::ostream &os, Object *object) {
        object->PrintBoard(os);
        return os;
    }
};