/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class AbstractReader {
protected:
    ifstream ifs;
public:
    AbstractReader(string &filename) {
        ifs.open(filename);
        if (!ifs)
            throw invalid_argument("filename:" + filename);
    }

    virtual ~AbstractReader() = default;
};

