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
    const string filename;

public:

    explicit Reader(const string &filename) : filename(filename) {
        ifs.open(filename);
        if (!ifs)
            throw runtime_error("filename:" + filename + "not found");
    }

    //TODO: exeptions for invalid input

    template<typename StillObj>
    std::map<char, StillObj *> ReadStillObjects() {
        string s;
        getline(ifs, s);

        std::map<char, StillObj *> objects;

        StillObj *object = new StillObj();
        while (ifs >> (*object)) {
            bool found = objects.find(object->Name()) != objects.end();
            if (!found)
                objects.insert({object->Name(), object});
            else
                delete object;

            object = nullptr;
            object = new StillObj();

        }

        if (!ifs.eof()) {
            throw runtime_error(filename + " - Error loading input from this file.");
        }

        delete object;

        return objects;
    }

    map<Coords, char> ReadBoard(int &mx, int &my) {
        map<Coords, char> coords;
        ifs >> mx >> my;
        int x, y;
        char c;
        while (ifs >> x >> y >> c) {
            Coords coord(x, y);
            if (coords.find(coord) == coords.end()) {
                coords.insert({coord, c});
                continue;
            }
            throw invalid_argument("coordinations " + coord.toStr() + " in board already exists");
        }
        return coords;
    }

    virtual ~Reader() = default;
};




