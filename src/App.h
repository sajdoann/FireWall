/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <string>

#include "Game/Game.h"
#include "Interface.h"
#include "Command.h"
using namespace std;

class App {
    Game game;
    Interface interface;
    map< string, Command > commands;

public:
    App() : game(Game()), interface(cin, cout) {
        CreateCommands();

    }
    void CreateCommands(){
        Command exit = Command("exits the game witout saving",[](Game &, Interface &){ return false;} );
        commands.insert( {"exit" , exit});

        Command placePatch = Command("places patch, syntax: \"( patch type, coord x, coord y )\" "
                                     "\n for instance: \"( D 2 5)\"",
                                     []( Game & g, Interface & i){
                                        char patchName;
                                        Coords coords;
                                        i.GetPatchInfo(patchName, coords);
                                        g.InsertPatch(patchName, coords);
                                        return true;
                                        }
                                     );
        commands.insert(make_pair("^[a-zA-Z][ ]*\\([ ]*[0-9 ]*[ ]*,[ ]*[0-9]*[ ]*\\)", placePatch));
    }
/**
 * game loop
 * @return no errors 0 / app errors nonzero number
 */
int Run();
};



