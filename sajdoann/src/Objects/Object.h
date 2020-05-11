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

    virtual ostream &PrintObject(ostream &os) = 0;

    virtual istream &LoadObject(istream &is) = 0;


    virtual ostream &PrintInfo(ostream &os) const = 0;

    virtual bool isMovingObject() const = 0;

    virtual bool isEmpty() const = 0;

    virtual bool isVirus() const = 0;


    friend std::ostream &operator<<(std::ostream &os, Object *object) {
        object->PrintObject(os);
        return os;
    }

    friend std::istream &operator<<(std::istream &is, Object *object) {
        object->LoadObject(is);
        return is;
    }
};