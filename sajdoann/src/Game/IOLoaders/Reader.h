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
#include "../../Game_Constants.h"

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
            else {
                char name = object->Name();
                delete object;
                throw invalid_argument("Object already exists. Name: " + name);
            }

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
        if (mx < MIN_BOARD_MEASURE || my < MIN_BOARD_MEASURE || mx > MAX_BOARD_MEASURE || my > MAX_BOARD_MEASURE)
            throw invalid_argument(
                    "Board does not fit max/min specifications. Measures input was :" + to_string(mx) + " " +
                    to_string(my));

        int x, y;
        char c;
        while (ifs >> x >> y >> c) {
            Coords coord(x, y);

            if (coord.X() >= mx || coord.Y() >= my || coord.X() < 0 || coord.Y() < 0)
                throw invalid_argument("Coords " + coord.toStr() + "are out of board.");

            if (coords.find(coord) == coords.end()) {
                coords.insert({coord, c});
                continue;
            }
            throw invalid_argument("coordinations " + coord.toStr() + " already taken on this board");
        }
        return coords;
    }

    virtual ~Reader() = default;
};




