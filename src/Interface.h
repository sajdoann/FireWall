/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iostream>
#include <sstream>
#include "Objects/Coords.h"

using namespace std;


class Interface {
    istream &in;
    ostream &os;
public:
    Interface(istream &in, ostream &os) : in(in), os(os) {}

    string PromptCommand() const {
        string command;
        os << "Enter command: " << endl;
        while (!(in >> command)) {}
        return command;
    }

    void HelpAdvertiser() {
        os << "To see help type \"help\"" << endl;
    }

    char GetPatchInfo(string s, char &patchName, Coords &coords) {
        istringstream is(s);
        int x, y;
        is >> patchName >> x >> y;
        coords.setCoords(x, y);
    }
};

