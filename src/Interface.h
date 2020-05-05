/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Objects/Coords.h"
#include "Board/Board.h"

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

    /** suggests to use help to print commands and their syntax */
    void HelpAdvertiser() {
        os << "Your command was invalid. \n To see help type \"help\"" << endl;
    }


    void GetPatchInfo(const string & s, char &patchName, Coords &coords) {
        istringstream is(s);
        int x, y;
        char p = '(';
        char c = ')';
        char sep = ',';
        is >> patchName >> p >> x >> sep >> y >> c;
        coords.setCoords(x, y);
        patchName = toupper(patchName);
    }

    /** tells the story of FireWall game */
    void Greet() const{
        os << "Hello!" << endl;
        os << "There is a very important mission ahead of you." << endl;
        os << "The FireWall has breaches, your goal is to survive next vicious attack from the hackers." << endl;
        os << "Try your best while placing patches, so the dangerous mallware cannot survive through your barrier" << endl;
        os << "Your entire computer could fall apart if you dont!" << endl;
        os << "I wish you good luck :) " << endl << endl;
        os << "To continue press enter" << endl;
        string s;
        while(!(getline(in,s))){}
    }

    void NumberLine(int max) const{
        os << " ";
        for (int i = 0; i < max; ++i) {
            os << setw(3) << i;
        }
        os << endl;

    }

    void PrintBoard( Board & board) const{
        NumberLine(board.MaxX());

        for (int i = 0; i < board.MaxX(); ++i) {
            for (int j = 0; j < board.MaxY(); ++j) {
                if(j==0) os << i;
                os << setw(3) << (board(i,j));
            }
            os << endl;
        }
    }
};

