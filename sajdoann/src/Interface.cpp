/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#include "Interface.h"
#include "Interface_Constants.h"

string Interface::PromptCommand() const {
    string command;
    os << ENTER_COMMAND << endl;
    getline(in, command);
    return command;
}

void Interface::HelpAdvertiser() {
    os << HELP_ADVERTISE << endl;
}

void Interface::PrintHelp(const string &name, const string &help) {
    os << setw(12) << left << name << " -   " << help << endl;
}

void Interface::GetPatchInfo(const string &s, char &patchName, Coords &coords) {
    istringstream is(s);
    int x, y;
    char p = '(';
    char c = ')';
    char sep = ',';
    is >> patchName >> p >> x >> sep >> y >> c;
    coords.setCoords(x, y);
    patchName = toupper(patchName);
}

void Interface::Greet() {
    os << GREETING << endl;
    string s;
    while (!(getline(in, s))) {}
    ClearScreen();
}

void Interface::NumberLinePrep(int max) const {
    os << setw(3) << " ";
    for (int i = 0; i < max; ++i) {
        os << setw(3) << i;
    }
    os << endl;
}

void Interface::getColorOfObject(Object *o) const {
    if (o->isEmpty()) {
        clr = colorClass.Color(ColorClass::CYAN);
    }
    if (!o->isMovingObject() && !o->isEmpty()) {
        if (((Patch *) o)->canShoot())
            clr = colorClass.Color(ColorClass::BLUE);
        else
            clr = colorClass.Color(ColorClass::RED);
    }
}

void Interface::resetClr() const {
    clr = colorClass.Color(ColorClass::RESET);
    os << clr;

}


void Interface::PrintBoardPrep(Board &board) const {
    os << "patches:" << endl;
    NumberLinePrep(board.MaxY());

    for (int i = 0; i < board.MaxX(); ++i) {
        for (int j = 0; j < board.MaxY(); ++j) {
            if (j == 0) os << setw(3) << i;
            Object *o = board(i, j);

            getColorOfObject(o);


            os << clr << setw(3) << (board(i, j));
            resetClr();
        }
        os << endl;
    }
}

void Interface::InvalidMove() const {
    os << INVALID_MOVE << endl;
}

void Interface::ExplainPrepState() {
    os << EXPLANATION << endl;
}

void Interface::PrintResult(ResultEnum gameResult) {
    if (gameResult == ResultEnum::LOSE)
        os << LOST_MESSAGE << endl;
    else os << WIN_MESSAGE << endl;
}

void Interface::PrintBoardAttack(Board &board) {
    for (int i = 0; i < board.MaxX(); ++i) {
        for (int j = 0; j < board.MaxY(); ++j) {
            Object *o = board(i, j);
            getColorOfObject(o);
            os << clr << setw(3) << (o);
            resetClr();
        }
        os << endl;
    }

    os << endl << endl;
}