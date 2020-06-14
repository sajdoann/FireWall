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
    ClearScreen();
    os << colorClass.Color(ColorClass::BLUE) << "FireWall" << endl;
    ResetClr();
    PrintMessageWaitForEnter(GREETING);
    ClearScreen();
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

void Interface::ResetClr() const {
    clr = colorClass.Color(ColorClass::RESET);
    os << clr;

}

void Interface::numberRow(int max) const {
    os << setw(3) << " ";
    for (int i = 0; i < max; ++i) {
        os << setw(3) << i;
    }
    os << endl;
}

void Interface::PrintBoard(const Board &board) const {
    numberRow(board.MaxY());

    for (int i = 0; i < board.MaxX(); ++i) {
        for (int j = 0; j < board.MaxY(); ++j) {
            if (j == 0) os << setw(3) << i;
            Object *o = board(i, j);

            getColorOfObject(o);


            os << clr << setw(3) << (board(i, j))->Name();
            ResetClr();
        }
        os << endl;
    }
}

void Interface::InvalidMove() const {
    os << INVALID_MOVE << endl;
}

void Interface::ExplainPrepState() {
    PrintMessageWaitForEnter(EXPLANATION);
}

void Interface::PrintResult(ResultEnum gameResult) {
    if (gameResult == ResultEnum::LOSE)
        PrintInColor(colorClass.Color(ColorClass::RED), LOST_MESSAGE);
    else PrintInColor(colorClass.Color(ColorClass::GREEN), WIN_MESSAGE);
    PrintMessageWaitForEnter("To continue press enter.");
    ClearScreen();
}

string Interface::PromptSaveFolder() {

    string s;
    while (true) {
        os << "Enter name to save the game: " << endl;
        in >> s;
        ClearBuffers();
        bool isOK = true;
        if (s.empty()) continue;
        for (unsigned int i = 0; i < s.size(); ++i) {
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

string Interface::chooseFile(vector<string> filenames) {
    os << "Saved games:" << endl;
    for (unsigned int i = 1; i <= filenames.size(); ++i) {
        os << i << setw(15) << " " << filenames[i - 1] << endl;
    }

    os << "Write number of game you want to load:" << endl;
    int choosed = -1;
    while (true) {
        string s;
        getline(in, s);
        stringstream ss(s);
        ss >> choosed;
        if (choosed <= (int) filenames.size() && choosed > 0) {
            break;
        } else {
            os << "The input was incorrect. Write a number of the game you want to load." << endl;
        }
    }

    ClearBuffers();
    return filenames[choosed - 1];
}

void Interface::PrintRam(int ram, int startRam) const {
    os << "Ram: ";
    if (ram <= 0) {
        PrintGreyRam(startRam);
        os << " " << 0 << endl;
        return;
    }
    int poc = 11;
    double skok = poc / (double) ram;
    for (double i = skok; i - poc <= DBL_EPSILON * fabs(i + poc) * 10000; i += skok) {
        cout << RAM_COLOR_START + to_string(7 * 16 + (int) i) + "m " << " " << "\u001b[0m" << flush;
    }
    PrintGreyRam(startRam - ram);
    os << " " << ram << "/" << startRam << endl;
}

void Interface::PrintMessageWaitForEnter(const string &message) {
    Print(message);
    string s;
    getline(in, s);
}

void Interface::Print(const string &message) const {
    os << message;
    ResetClr();
    os << endl;
}

string Interface::AskWhichGame() {
    Print(LOAD_OR_NEW);
    string s;
    getline(in, s);
    return s;
}

void Interface::PrintGreyRam(int ram) const {
    for (int j = ram; j > 0; --j) {
        os << RAM_COLOR_START + to_string(15 * 16 + 12) + "m " << ' ' << "\u001b[0m";
    }
}

void Interface::PrintMoney(int money) const {
    os << "Money: ";
    PrintInColor(colorClass.Color(ColorClass::GREEN), to_string(money));
    os << endl;
}

void Interface::PrintGamePane(const State &gameState, Counter scoreCounter, const Board &board) const {
    PrintState(gameState);
    PrintBoard(board);
    PrintLvl(scoreCounter.Level());
    PrintRam(scoreCounter.Ram(), scoreCounter.RamStart());
    PrintMoney(scoreCounter.Money());
}

void Interface::PrintInColor(const char *color, const string &message) const {
    os << color;
    Print(message);
}

void Interface::PrintClock(int time) const {
    Print("System time: " + to_string(time));
}

void Interface::PrintLvl(int lvl) const {
    Print("lvl: " + to_string(lvl));
}

