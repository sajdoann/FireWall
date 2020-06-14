/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once

#include <map>
#include <vector>

using namespace std;

/**
 * class for colors that are used in game interface
 * has colors that are assigned ansi escape sequences
 */
class ColorClass {
public:
    enum Color {
        RED, BLUE, CYAN, GREY, GREEN, VIRUS, HOTFIX, RESET
    };
private:
    map<Color, const char *> colors;


    const char *RED_ANSI = "\u001b[31m";
    const char *BLUE_ANSI = "\u001b[1m\u001b[34m";
    const char *CYAN_ANSI = "\u001b[38;5;51m"; //"\u001b[36m";
    const char *GREY_ANSI = "\u001b[37;1m";
    const char *GREEN_ANSI = "\u001b[32m";
    const char *PURPLE_LIGHT_ANSI = "\u001b[38;5;141m";
    const char *YELLOW = "\u001b[38;5;84m";
    const char *VIRUS_ANSI = "\u001b[1m";
    const char *HOTFIX_ANSI = "\u001b[36m";
    const char *RESET_ANSI = "\u001b[0m";

    vector<const char *> ANSI = {RED_ANSI, BLUE_ANSI, CYAN_ANSI, GREY_ANSI, GREEN_ANSI, VIRUS_ANSI, HOTFIX_ANSI,
                                 RESET_ANSI};

public:
    vector<Color> COLORS = {RED, BLUE, CYAN, GREY, GREEN, VIRUS, HOTFIX, RESET};

    /**
     * assigns color enum its char representation
     */
    ColorClass() {
        for (unsigned int i = 0; i < ANSI.size(); ++i) {
            colors.insert({COLORS[i], ANSI[i]});
        }
    }

    /** gets color ansi escape sequence */
    const char *Color(Color colorEnum) const {
        return colors.at(colorEnum);
    }
};