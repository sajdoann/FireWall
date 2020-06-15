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

    template<typename StillObj>
    void freeObjects(std::map<char, StillObj *> &objects) {
        for (auto &obj : objects) {
            delete obj.second;
            obj.second = nullptr;
        }
    }

public:

    explicit Reader(const string &filename);

    virtual ~Reader() = default;

    template<typename StillObj>
    std::map<char, StillObj *> ReadStillObjects() {
        std::map<char, StillObj *> objects;

        StillObj *object = new StillObj();
        while (in >> (*object)) {

            bool found = objects.find(object->Name()) != objects.end();
            if (!found)
                objects.insert({object->Name(), object});
            else {
                char name = object->Name();
                delete object;
                freeObjects(objects);
                throw invalid_argument("Object already exists. Name: " + name);
            }

            object = nullptr;
            object = new StillObj();

        }

        delete object;
        if (objects.empty())
            throw invalid_argument("At least one object needs to be inputed " + filename);

        if (!in.eof()) {
            freeObjects(objects);
            EofError();
        }
        return objects;
    }

    map<Coords, char> ReadBoard(int &mx, int &my);

    Counter ReadScore() {
        int ram = -1, startRam = -1, lvl = -1, money = -1;
        string input;
        getline(in, input);
        stringstream ss(input);
        ss >> ram >> startRam >> lvl >> money;
        if (ram <= 0 || startRam <= 0 || lvl < 0 || money < 0)
            throw logic_error("Invalid input. Arguments missing/negative in " + filename);

        if (!ss.good() && !ss.eof())
            EofError();

        getline(in, input);
        if (input.size() > 1)
            EofError();
        getline(in, input);
        if (input.size() > 1)
            EofError();

        if (ram > startRam)
            throw logic_error("Ram cannot be bigger than start ram.");
        if (startRam > MAX_RAM_CONSTANT || lvl > MAX_LVL_CONSTANT)
            throw logic_error("One of arguments exceeded max allowed constant.");
        if (!in.eof()) {
            //cout << in.eof() << in.good() << in.bad() << endl;
            EofError();
        }


        Counter ctr(ram, startRam, lvl, money);
        return ctr;
    }
};
