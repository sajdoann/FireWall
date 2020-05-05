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
    App() : game(), interface(cin, cout) {
        CreateCommands();
    }


    void CreateCommands(){
        //exit command
        Command exit = Command("exits the game witout saving",[](const string& , Game &, Interface &){ return CommandEndType::ENDGAME;} );
        commands.insert( {"exit" , exit});

        //placePatch command, it places the patch and the prints the changed board
        Command placePatch = Command("places patch, syntax: \"( patch type, coord x, coord y )\" "
                                     "\n for instance: \"D( 2, 5)\"",
                                     []( const string& userInput, Game & g, Interface & i){
                                        char patchName;
                                        Coords coords;
                                        i.GetPatchInfo(userInput, patchName, coords);

                                        //validates input
                                        if(!g.isPatch(patchName) || g.OutOfGameBoard(coords)){
                                            return CommandEndType::INVALID;
                                        }

                                        g.InsertPatch(patchName, coords);

                                        //TODO: CLEAR screen
                                        i.ClearScreen();

                                         i.PrintBoard(g.GameBoard());
                                         return CommandEndType::VALID;
                                        }
                                     );
        commands.insert({"[ ]*[a-zA-Z][ ]*\\([ ]*[0-9]{1,}[ ]*,[ ]*[0-9]{1,}[ ]*\\)[ ]*", placePatch});

        //put online (done)
        Command done = Command("Type it when you are done - you think FireWall can survive the next attack.",
                []( const string& userInput, Game & g, Interface & i){
                    g.GameState(State::ATTACK);
                    return CommandEndType::VALID;
                    }
                );
        commands.insert({"done", done});
    }


    Board & GameBoard(){return game.GameBoard(); }
    void GameState(State & state){
        game.GameState(state);
    }
/**
 * game loop
 * @return no errors 0 / app errors nonzero number
 */
int Run();
};



