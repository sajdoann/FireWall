/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include "Coords.h"

using namespace std;

class Object {
protected:
    char name;
public:
    Object(char name) : name(name) {}

    Object() = default;

    virtual ~Object() = default;

    //saves object into stream for storing
    virtual ostream &SaveObject(ostream &out) = 0;

    //loads objects in save object format
    virtual istream &LoadObject(istream &in) = 0;

    //print object in game
    //virtual ostream &Print(ostream &out) = 0;


    //prints object for user
    virtual ostream &PrintInfo(ostream &out) const = 0;


    virtual bool isMovingObject() const = 0;

    virtual bool isEmpty() const = 0;

    virtual bool isVirus() const = 0;


    friend std::ostream &operator<<(std::ostream &out, Object *object) {
        out << object->name;
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Object *object) {
        object->LoadObject(in);
        return in;
    }
};