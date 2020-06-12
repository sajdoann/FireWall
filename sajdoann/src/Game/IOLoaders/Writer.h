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
    template<typename O>
    void writeStillObjectsFromMap(O object) {
        for (const auto &p :object) {
            auto single = *p.second;
            single.SaveObject(out);
            out << endl;
        }
    }

    template<typename T>
    void getHeading(T t) {
        T::Heading(out);
    }

    void writeBoard(Board b) {
        out << b.MaxX() << " " << b.MaxY() << endl;
        for (int i = 0; i < b.MaxX(); ++i) {
            for (int j = 0; j < b.MaxY(); ++j) {
                Coords act(i, j);
                if (!b.At(act)->isEmpty()) {
                    out << act.toStr() << " " << b.At(act)->Name() << endl;
                }
            }
        }
        out << endl;
    }

    void Close() {
        out.close();
    }
};

