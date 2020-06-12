/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#include <cfloat>
#include <cmath>

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
    } else if (o->isPatch()) {
        if (((Patch *) o)->canShoot())
            clr = colorClass.Color(ColorClass::BLUE);
        else
            clr = colorClass.Color(ColorClass::RED);
    } else if (o->isVirus()) {
        clr = colorClass.Color(ColorClass::VIRUS);

    } else {
        clr = colorClass.Color(ColorClass::HOTFIX);
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
    string s;
    getline(in, s);
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

string Interface::PromptSaveFolder() {

    string s;
    while (true) {
        os << "Enter name to save the game: " << endl;
        in >> s;
        bool isOK = true;
        if (s.empty()) continue;
        for (int i = 0; i < s.size(); ++i) {
            if (!isdigit(s[i]) && !isalpha(s[i])) {
                isOK = false;
                break;
            }
        }
        if (isOK) break;
    }
    s = '/' + s;
    return s;
}

string &Interface::chooseFile(vector<string> filenames) {
    os << "Saved games:" << endl;
    for (int i = 0; i < filenames.size(); ++i) {
        os << i << setw(15) << filenames[i] << endl;
    }

    os << "Write number of game you want to load:" << endl;
    int choosed;
    while (in >> choosed) {
        if (choosed < filenames.size() && choosed >= 0) {
            break;
        }
    }
    return filenames[choosed];
}

void Interface::PrintRam(int ram, int startRam) const {
    os << "Ram: ";
    int poc = 11;
    double skok = poc / (double) ram;
    for (double i = skok; i - poc <= DBL_EPSILON * fabs(i + poc) * 10000; i += skok) {
        cout << "\u001b[48;5;" + to_string(7 * 16 + (int) i) + "m " << " " << "\u001b[0m" << flush;
    }
    for (int j = startRam - ram; j > 0; --j) {
        cout << "\u001b[48;5;" + to_string(15 * 16 + 12) + "m " << ' ' << "\u001b[0m";
    }
    os << " " << ram << endl;
}

