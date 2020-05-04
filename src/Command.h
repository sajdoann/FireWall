/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <map>
#include <functional>
#include <utility>

#include "Game/Game.h"
#include "Interface.h"

using namespace std;

class Command {
    string help;
    // std wrapper that can call any callable target ( <=> stores functions )
    function<bool(Game &, Interface &)> exec;

public:
    Command(string help, function<bool(Game &, Interface &)> exec) : help(std::move(help)), exec(std::move(exec)){}

    string Help() const{ return help; }

    /** calls function hidden in variable exec */
    bool Exec(Game & game, Interface & interface){
        return exec(game, interface);
    }

   /* functor that compares commands based on their names ( which are required to ne unique )
    struct cmp{
        int operator()(const Command & a, const Command & b){
            if( a.name != b.name ) return a.name < b.name;
            return 0;
        }
    };*/

};



