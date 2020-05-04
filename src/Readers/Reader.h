/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include "../Objects/Patch.h"

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

    std::map<char, Patch> ReadPatches(){
        std::map<char, Patch > patches;
        Patch patch;
        char name;
        while(ifs >> name >> patch){
            bool found = patches.find(name) != patches.end();
            if(!found)
                patches.insert({name, move(patch)});
        }
        return patches;
    }

    virtual ~Reader() = default;
};




