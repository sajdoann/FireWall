/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Game/Objects/Coords.h"
#include "Game/Board/Board.h"
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

private:
    /** prints numbers from 0-max in the same format as PrintBoardPrep
    * @param max till what number it prints
    */
    void NumberLinePrep(int max) const;

    /**
     * gets the right color for object o
     * @param o - object that we want the color of
     */
    void getColorOfObject(Object *o) const;

    /**
     * resets the stream color
     */
    void resetClr() const;

public:
    Interface(istream &in, ostream &os) : in(in), os(os), colorClass() {}

    ~Interface() = default;

    /** asks the user to enter command */
    string PromptCommand() const;

    /** suggests to use help to print commands and their syntax */
    void HelpAdvertiser();

    /** prints help for the user */
    void PrintHelp(const string &name, const string &help);

    /** extracts patch from  InsertPatch command */
    void GetPatchInfo(const string &s, char &patchName, Coords &coords);

    /** clears the screen by printing 100 new lines */
    void ClearScreen() {
        //TODO: in clion term variable not found -> not functioning (on other sys should not be a prob)
        system("clear");
        //os << string(100, '\n');
    }

    /** tells the story of FireWall game */
    void Greet();

    /**
     * prints the board for the preparation mode
     * @param board - the board it prints
     */
    void PrintBoardPrep(Board &board) const;


    /** prints the invalid move text to the user */
    void InvalidMove() const;

    /** explains the preparation state of the game */
    void ExplainPrepState();

    /** prints the result */
    void PrintResult(ResultEnum gameResult);


    void ClearBuffers() {
        //TODO: IMPLEMENT
    }


    void PrintPatchInfo(const Patch &p) const {
        p.PrintInfo(os);
    }

    void PrintBoardAttack(Board &board);

};

