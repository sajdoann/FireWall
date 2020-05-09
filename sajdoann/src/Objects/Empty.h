/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <ostream>
#include "Object.h"

using namespace std;

class Empty : public Object{

public:
    Empty() = default;
    ~Empty() = default;

    ostream & PrintObject(ostream & os) override { os << *this; }

    ostream & PrintInfo(ostream & os){ os << "empty"; }

    bool isMovingObject() override { return false;}

    friend ostream & operator << (ostream & os, const Empty & empty){
        os << "\u001b[37;1m  "<< "-" << "\u001b[0m";
    }

};