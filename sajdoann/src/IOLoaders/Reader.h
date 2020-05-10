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

/**
 * class to read objects and board from files
 */
class Reader {
protected:
    ifstream ifs;

public:

    explicit Reader(const string &filename) {
        ifs.open(filename);
        if (!ifs)
            throw invalid_argument("filename:" + filename);
    }

    //TODO: exeptions for invalid input

    template<typename StillObj>
    std::map<char, StillObj *> ReadStillObjects(){
        std::map<char, StillObj *> objects;

        StillObj * object = new StillObj();
        while (ifs >> *object) {
            bool found = objects.find(object->Name()) != objects.end();
            if (!found)
                objects.insert({object->Name(), move(object)});
            else
                delete object;

            object = nullptr;
            object = new StillObj();
        }

        delete object;

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




