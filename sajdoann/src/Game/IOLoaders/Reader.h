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
#include "../StateEnum.h"

using namespace std;

/**
 * class to read objects and board from files
 */
class Reader {
protected:
    ifstream in;
    const string filename;

    const char *ERR_FILE_NOT_FOUND = " file not found ";
    const char *ERR_BOARD_MEASURES = "Board does not fit max/min specifications.";
    const char *ERR_BOARD_INPUT_FORMAT = "Wrong format in board input.";
    const char *ERR_BOARD_COORDS_OUT = "Coords are out of board ";
    const char *ERR_BOARDS_COORDS_DUPLICATE = "Coordinations already taken on this board";
    const char *ERR_WRONG_FILE_FORMAT = "Error loading input from this file. Wrong file format. ";
    const char *ERR_OBJECT_EXISTS = " object already exists.";
    const char *ERR_FILE_CORRUPTED = "File corrupted: no/wrong object input ";
    const char *ERR_RAM = "Ram cannot be bigger than start ram.";
    const char *ERR_EXCEEDS_MAX_ALLOWED_CONSTANT = "One of arguments exceeded max allowed constant.";

    /** throws invalid argument exception */
    void EofError();

    /**
     * frees localy allocated still objects
     * @tparam StillObj - object structure
     * @param objects - map key(name) + object
     */
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

    /**
     * reads board
     * @param mx - x board max io param
     * @param my - y board max io param
     * @return map (coords, name of patch)
     */
    map<Coords, char> ReadBoard(int &mx, int &my);

    /**
     * reads score from file
     * @return counter that has the score
     */
    Counter ReadScore();

    /**
    * reads viruses or patches
    * @tparam RObject - virus/patch
    * @return map (name,object)
    */
    template<typename RObject>
    std::map<char, RObject *> ReadObjects() {
        std::map<char, RObject *> objects;

        RObject *object = new RObject();
        while (in >> (*object)) {

            bool found = objects.find(object->Name()) != objects.end();
            if (!found)
                objects.insert({object->Name(), object});
            else {
                delete object;
                freeObjects(objects);
                throw invalid_argument(ERR_OBJECT_EXISTS);
            }

            object = new RObject();

        }

        delete object;

        if (!in.eof()) {
            freeObjects(objects);
            EofError();
        }

        if (objects.empty()) {
            string mess = filename;
            mess += ERR_FILE_CORRUPTED;
            throw invalid_argument(mess);
        }
        return objects;
    }

};
