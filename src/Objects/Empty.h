/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <ostream>
#include "Object.h"

using namespace std;

class Empty : public Object{
    ~Empty() = default;

    ostream & PrintObject(ostream & os) override {
        os << *this;
    }

    ostream & PrintInfo(ostream & os){
        os << "empty";
    }

    friend ostream & operator << (ostream & os, const Empty & empty){
        os << "E";
    }



public:
    Empty() = default;
};