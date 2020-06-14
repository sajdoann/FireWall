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
#include "../State_Enum.h"

using namespace std;

/**
 * class to read objects and board from files
 */
class Reader {
protected:
    ifstream in;
    const string filename;

    /** throws invalid argument exception */
    void EofError();

    void ReadLineScore(const string &name, int &variable) {
        string nameIn;
        in >> nameIn >> variable;
        if (nameIn != name)
            throw invalid_argument("not provided/corrupted \'" + name + "\' headline");

    }

public:

    explicit Reader(const string &filename);

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
        if (!in.eof()) {
            for (auto &obj : objects) {
                delete obj.second;
            }
            EofError();
        }
        return objects;
    }

    map<Coords, char> ReadBoard(int &mx, int &my);

    //todo: osetrit new line
    Counter ReadScore() {
        int ram, startRam, lvl, money;
        string input;
        getline(in, input);
        stringstream ss(input);
        ss >> ram >> startRam >> lvl >> money;

        if (!ss.good())
            EofError();
        getline(in, input);
        if (input.size() > 1)
            EofError();

        if (ram > startRam)
            throw logic_error("Ram cannot be bigger than start ram.");
        if (startRam > MAX_RAM_CONSTANT || lvl > MAX_LVL_CONSTANT)
            throw logic_error("One of arguments exceeded max allowed constant.");
        if (!in.eof())
            EofError();

        Counter ctr(ram, startRam, lvl, money);
        return ctr;
    }
};
