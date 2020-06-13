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

    void PrintMessageWaitForEnter(const string &message);

    void Print(const string &message);

    void PrintGreyRam(int ram) const;

private:
    /** prints numbers from 0-max in the same format as PrintBoard
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

    void PrintString(const string &s) { os << s << endl; }

    /** suggests to use help to print commands and their syntax */
    void HelpAdvertiser();

    /** prints help for the user */
    void PrintHelp(const string &name, const string &help);

    /** extracts patch from  InsertPatch command */
    void GetPatchInfo(const string &s, char &patchName, Coords &coords);

    /** clears the screen by printing 100 new lines */
    void ClearScreen() {
        //TODO: in clion term variable not found -> not functioning (on other sys should not be a prob)
        //system("clear");
        //os << string(100, '\n');
    }

    /** tells the story of FireWall game */
    void Greet();

    /**
     * prints the board for the preparation mode
     * @param board - the board it prints
     */
    void PrintBoard(const Board &board) const;


    /** prints the invalid move text to the user */
    void InvalidMove() const;

    /** explains the preparation state of the game */
    void ExplainPrepState();

    /** prints the result */
    void PrintResult(ResultEnum gameResult);


    void ClearBuffers() {
        //TODO: IMPLEMENT
        //in.ignore(numeric_limits<streamsize>::max(),'\n');
    }


    void PrintObjectInfo(const Object &object) const {
        object.PrintInfo(os);
    }

    void PrintBoardAttack(Board &board);

    string PromptSaveFolder();

    string chooseFile(vector<string> filenames);

    void PrintRam(int ram, int startRam) const;

    void PrintMoney(int money) const;

    string AskWhichGame();

    void PrintGamePane(ScoreCounter scoreCounter, const Board &board) const;

};

