/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <climits>
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

    /** prints message waits for enter */
    void PrintMessageWaitForEnter(const string &message);

    /** prints message */
    void Print(const string &message) const;

    /** prints message in color */
    void PrintInColor(const char *color, const string &message) const;

    /** prints ram that was used in grey */
    void PrintGreyRam(int ram) const;

private:
    /** prints numbers from 0-max
    * @param max - till what number it prints
    */
    void numberRow(int max) const;

    /**
     * gets the right color for object o
     * @param o - object that we want the color of
     */
    void getColorOfObject(Object *o) const;

    /**
     * resets the stream color
     */
    void ResetClr() const;

public:
    Interface(istream &in, ostream &os) : in(in), os(os), colorClass() {}

    ~Interface() = default;

    /** asks the user to enter command */
    string PromptCommand();

    /** prints string s */
    void PrintString(const string &s) { os << s << endl; }

    /** prints state */
    void PrintState(const State &state) const {
        string s;

        if (state == State::PREPARATION)
            s = "PREPARATION: ";
        else if (state == State::ATTACK)
            s = "ATTACK: ";
        else s = "MENU: ";

        os << colorClass.Color(ColorClass::BLUE) << s << colorClass.Color(ColorClass::RESET) << endl;
    }

    /** suggests to use help to print commands and their syntax */
    void HelpAdvertiser();

    /** prints help for the user */
    void PrintHelp(const string &name, const string &help);

    /** extracts patch from  InsertPatch command */
    void GetPatchInfo(const string &s, char &patchName, Coords &coords);

    /** clears in buffer */
    void ClearBuffers();

    /** clears the screen by printing 100 new lines */
    void ClearScreen() {
        //in clion term variable not found -> not functioning (on other sys should not be a prob)
        int err = system("clear");
        if (err == -1) {
            for (int i = 0; i < 10; ++i) {
                Print("\n");
            }
            //todo: throw logic error
        }
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

    /** prits all available information about given object */
    void PrintObjectInfo(const Object &object) const {
        object.PrintInfo(os);
    }

    /** asks for folder to save the game */
    string PromptSaveFolder();

    /** asks user to choose from files */
    string chooseFile(vector<string> filenames);

    /** prints ram */
    void PrintRam(int ram, int startRam) const;

    /** prints money */
    void PrintMoney(int money) const;

    /** asks youser to input either new/ load/ exit to see what to do next */
    string AskWhichGame();

    /**
     * prints entire game pane <-> prints all params
     * @param gameState
     * @param scoreCounter
     * @param board
     */
    void PrintGamePane(const State &gameState, Counter scoreCounter, const Board &board) const;

    void PrintClock(int time) const;

    void PrintLvl(int lvl) const;

    vector<string> getFilenames(const char *PATH);
};

