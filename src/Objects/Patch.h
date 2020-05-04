/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include "Object.h"

using namespace std;

class Patch : public Object {
protected:
    char type = 'D';
    char name = 'D';
    int price = 10;
    int range = 2;
public:
    Patch() = default;
    Patch( char name,char type, int price, int range) : Object(),type(type), name(name), price(price), range(range){}
    ~Patch() override = default;
    char Name() const {return name;}
    char Type() const {return type;}
    int Price() const {return price;}
    int Range() const {return range;}

    int  operator < ( const Patch & patch) const {
        if(name != patch.name)
            return (name < patch.name) ? -1 : 1;
        return 0;
    }

    struct cmp{
        int operator()(const Patch & a, const Patch & b){
            return a < b;
        }
    };

    friend ostream & operator << (ostream & os, const Patch & patch){
        os  << " " << patch.name << " " <<patch.type << " " << patch.price << " " << patch.range;
        return os;
    }

    ostream & PrintBoard(ostream & os) override {
        return os << (*this).name;
    }

    ostream & PrintInfo(ostream & os) override {
        return os << (*this);
    }

    friend istream & operator >> (istream & ifs, Patch & patch) {
        return ifs >> patch.name >> patch.type >> patch.price >> patch.range;
    }

    };


