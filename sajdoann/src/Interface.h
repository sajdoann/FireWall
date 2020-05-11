/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Objects/Coords.h"
#include "Board/Board.h"
#include "Game/ResultEnum.h"
#include "Color.h"

using namespace std;

/**
 * stream interface for user communication with the game
 */
class Interface {
    istream &in;
    ostream &os;
    ColorClass colorClass;
    mutable const char *clr = colorClass.Color(ColorClass::RESET);

public:
    Interface(istream &in, ostream &os) : in(in), os(os), colorClass() {}

    /** asks the user to enter command */
    string PromptCommand() const {
        string command;
        os << "Enter command: " << endl;
        getline(in, command);
        return command;
    }

    /** suggests to use help to print commands and their syntax */
    void HelpAdvertiser() {
        os << "Unknown command. \n To see help type \"help\"" << endl;
    }

    /** extracts patch from  InsertPatch command */
    void GetPatchInfo(const string &s, char &patchName, Coords &coords) {
        istringstream is(s);
        int x, y;
        char p = '(';
        char c = ')';
        char sep = ',';
        is >> patchName >> p >> x >> sep >> y >> c;
        coords.setCoords(x, y);
        patchName = toupper(patchName);
    }

    /** clears the screen by printing 100 new lines */
    void ClearScreen() {
        //TODO: in clion term variable not found -> not functioning (on other sys should not be a prob)
        system("clear");
        //os << string(100, '\n');
    }

    /** tells the story of FireWall game */
    void Greet() {
        os << "Hello!" << endl;
        os << "There is a very important mission ahead of you." << endl;
        os << "The FireWall has breaches, your goal is to survive next vicious attack from the hackers." << endl;
        os << "Try your best while placing patches, so the dangerous mallware cannot survive through your barrier"
           << endl;
        os << "Your entire computer could fall apart if you dont!" << endl;
        os << "I wish you good luck :) " << endl << endl;
        os << "To continue press enter" << endl;
        string s;
        while (!(getline(in, s))) {}
        ClearScreen();
    }

    /** prints numbers from 0-max in the same format as PrintBoardPrep
     * @param max till what number it prints
     */
    void NumberLinePrep(int max) const {
        os << " ";
        for (int i = 0; i < max; ++i) {
            os << setw(3) << i;
        }
        os << endl;
    }

    void getColorOfObject(Object *o) const {
        if (o->isEmpty()) {
            clr = colorClass.Color(ColorClass::CYAN);
        }
        if (!o->isMovingObject() && !o->isEmpty()) {
            if (((Patch *) o)->CanShoot())
                clr = colorClass.Color(ColorClass::BLUE);
            else
                clr = colorClass.Color(ColorClass::RED);
        }
    }

/**
     * prints the board for the preparation mode
     * @param board - the board it prints
     */
    void PrintBoardPrep(Board &board) const {
        os << "patches:" << endl;
        NumberLinePrep(board.MaxX());

        for (int i = 0; i < board.MaxX(); ++i) {
            for (int j = 0; j < board.MaxY(); ++j) {
                if (j == 0) os << i;
                Object *o = board(i, j);

                getColorOfObject(o);


                os << clr << setw(3) << (board(i, j));
                resetClr();
            }
            os << endl;
        }
    }

    void resetClr() const {
        clr = colorClass.Color(ColorClass::RESET);
        os << clr;

    }


    /** prints the invalid move text to the user */
    void InvalidMove() const {
        os << "This move cannot be executed." << endl;
        os << "Check if the names, coordinates are valid and you have enough RAM to support the patch" << endl;
    }

    /** explains the preparation state of the game */
    void ExplainPrepState() {
        os << "Now your goal is to place patches so no virus could break through your wall." << endl;
        os << "To do that type in name of patch (coord1, coord2) (fe: \"W(0,0)\" )" << endl;
        os << "To see:\n"
              "        .    all possible commands type \"help\"\n"
              "        .    all possible patches and their info type \"patches\"\n" << endl;
        os << "This is what the IT departament came with so far:\n" << endl;
        os << " what the letters mean:\n"
              "         .   E - empty\n"
              "         .   W - wall\n"
              "         .   other letter - some super special patch you can google up (use: \"google\" + name of patch)\n"
           << endl;
        os << "After you are done, just type in \"done\" and the hackers might try to breach in.\n" << endl;
    }

    /** prints the result */
    void PrintResult(ResultEnum gameResult) {
        if (gameResult == ResultEnum::LOSE)
            os << "You lost!" << endl;
        else os << "Congrats! You won!" << endl;
    }


    void ClearBuffers() {
        //TODO: IMPLEMENT
    }

    void PrintHelp(const string &name, const string &help) {
        os << setw(12) << left << name << " -   " << help << endl;
    }

    void PrintPatchInfo(const Patch &p) const {
        p.PrintInfo(os);
    }

};

