/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Writer {
protected:
    const string filename;
    ofstream out;

public:
    Writer(const string filename) : filename(filename) {
        out.open(filename);
        if (!out)
            throw runtime_error("filename:" + filename + "not found");
    }

    //writes the data to file
    bool writeToFile() {

    }

};

