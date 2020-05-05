/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include "../Objects/Patch.h"
#include "../Objects/Virus.h"

using namespace std;
class Reader {
protected:
    ifstream ifs;

public:

    explicit Reader(const string &filename) {
        ifs.open(filename);
        if (!ifs)
            throw invalid_argument("filename:" + filename);
    }

    template<typename StillObj>
    std::map<char, StillObj> ReadStillObjects(){
        std::map<char, StillObj > objects;
        StillObj object;
        char name;
        while(ifs >> name >> object){
            bool found = objects.find(name) != objects.end();
            if(!found)
                objects.insert({name, move(object)});
        }
        return objects;
    }

    set<Coords> ReadBoard(int & mx, int & my){
        set<Coords> coords;
        ifs >> mx >> my;
        int x,y;
        while (ifs >> x >> y){
            coords.insert(Coords(x,y));
        }
        return coords;
    }

    virtual ~Reader() = default;
};




