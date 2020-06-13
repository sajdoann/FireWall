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
#include "../GameConstants.h"
#include "../ScoreCounter.h"
#include "../State.enum"

using namespace std;

/**
 * class to read objects and board from files
 */
class Reader {
protected:
    ifstream in;
    const string filename;

    /**
     * check if loading ends with eof if not throws invalid argument exception
     * @param endsWithEof - bool that says if file ends with eof
     */
    void check_eof(bool endsWithEof) {
        if (endsWithEof)
            return;

        string str = "Error loading input from this file: " + filename + " wrong file format.";
        throw invalid_argument(str);

    }

public:

    explicit Reader(const string &filename) : filename(filename) {
        in.open(filename);
        if (!in)
            throw runtime_error(filename + " not found");
    }

    virtual ~Reader() = default;

    //TODO: exeptions for invalid input

    template<typename StillObj>
    std::map<char, StillObj *> ReadStillObjects() {
        string s;
        getline(in, s);

        std::map<char, StillObj *> objects;

        StillObj *object = new StillObj();
        while (in >> (*object)) {
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

        delete object;
        check_eof(in.eof());
        return objects;
    }

    map<Coords, char> ReadBoard(int &mx, int &my) {
        map<Coords, char> coords;

        in >> mx >> my;
        if (mx < MIN_BOARD_MEASURE || my < MIN_BOARD_MEASURE || mx > MAX_BOARD_MEASURE || my > MAX_BOARD_MEASURE)
            throw invalid_argument(
                    "Board does not fit max/min specifications. Measures input was :" + to_string(mx) + " " +
                    to_string(my));

        int x, y;
        char br1, br2, sep;
        char c;
        while (in >> br1 >> x >> sep >> y >> br2 >> c) {
            if (br1 != '(' || sep != ',' || br2 != ')')
                throw invalid_argument("Wrong format in board input.");

            Coords coord(x, y);

            if (coord.X() >= mx || coord.Y() >= my || coord.X() < 0 || coord.Y() < 0)
                throw invalid_argument("Coords " + coord.toStr() + " are out of board.");

            if (coords.find(coord) == coords.end()) {
                coords.insert({coord, c});
                continue;
            }
            throw invalid_argument("Coordinations " + coord.toStr() + " already taken on this board.");
        }

        check_eof(in.eof());

        return coords;
    }


    void ReadLineScore(const string &name, int &variable) {
        string nameIn;
        in >> nameIn >> variable;
        if (nameIn != name)
            throw invalid_argument("not provided/corrupted \'" + name + "\' headline");

    }

    ScoreCounter &ReadScore() {
        int variable;
        string name;
        ReadLineScore("Ram:", variable);
        if (variable > MAX_RAM_CONSTANT) {
            throw invalid_argument(variable + "exceeeds max ram allowed");
        }

        if (name != "gameState:")
            throw invalid_argument("not provided/corrupted \'gameState:\' headline");
        in >> name >> variable;
        if (name != "gameState:")
            throw invalid_argument("not provided/corrupted \'gameResult:\' headline");


    }
};




