/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <map>
#include <functional>

#include "Game/Game.h"
#include "CommandEndType.h"
#include "Interface.h"

using namespace std;

/**
 *   class for command - remembers name, help and function what to do if this command is called
 *   strucutre of this class inspired by https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/blob/master/src/CCommand.h
 *   author @bernhdav
 */
class Command {
    string name;
    string help;
    // std wrapper that can call any callable target ( <=> stores functions ) string - userInput
    function<CommandEndType(string, Game &, Interface &)> exec;

public:

    Command(string name, string help, function<CommandEndType(string, Game &, Interface &)> exec) : name(
            std::move(name)), help(std::move(help)), exec(std::move(exec)) {}

    string Help() const { return help; }

    string Name() const { return name; }

    /** calls function hidden in variable exec */
    CommandEndType Exec(string &userInput, Game &game, Interface &interface) {
        return exec(userInput, game, interface);
    }
};
