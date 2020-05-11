/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once

#include <map>
#include <vector>

using namespace std;


using namespace std;


class ColorClass {
public:
    enum Color {
        RED, BLUE, CYAN, GREY, RESET
    };
private:
    map<Color, const char *> colors;


    const char *RED_ANSI = "\u001b[31m";
    const char *BLUE_ANSI = "\u001b[34m";
    const char *CYAN_ANSI = "\u001b[36m";
    const char *GREY_ANSI = "\u001b[37;1m";
    const char *RESET_ANSI = "\u001b[0m";

    vector<const char *> ANSI = {RED_ANSI, BLUE_ANSI, CYAN_ANSI, GREY_ANSI, RESET_ANSI};

public:
    vector<Color> COLORS = {RED, BLUE, CYAN, GREY, RESET};

    ColorClass() {
        for (int i = 0; i < ANSI.size(); ++i) {
            colors.insert({COLORS[i], ANSI[i]});
        }
    }

    const char *Color(Color colorEnum) const {
        return colors.at(colorEnum);
    }
};