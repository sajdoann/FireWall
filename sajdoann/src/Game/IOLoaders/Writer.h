/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "../ScoreCounter.h"

using namespace std;

class Board;

class Writer {
protected:
    const string filename;
    ofstream out;

public:
    Writer(const string filename);

    /**
     * closes the stream (file)
     */
    void Close() {
        out.close();
    }

    /**
     * writes object data to file
     * @tparam O
     * @param object
     */
    template<typename O>
    void writeObjectsFromMap(O object) {
        for (const auto &p :object) {
            auto single = *p.second;
            single.SaveObject(out);
            out << endl;
        }
    }

    /**
     * writes board to stream
     * @param b - board
     */
    void writeBoard(Board &b);

    /**
     * writes score to file
     * @param c - counter that counts score
     */
    void writeCounter(const Counter &c);
};

