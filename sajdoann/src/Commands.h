/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/6/2020
*/

#pragma once
#include <string>
#include "Command.h"

using namespace std;
class Commands {

    map< string, Command > commands;
public:

    map< string, Command > & CommandsMap(){
        return commands;
    }

    void CreateCommands(){
        //exit command
        Command exit = Exit();
        commands.insert( {"exit" , exit});

        //placePatch command, it places the patch
        Command placePatch = PlacePatch();
        commands.insert({"[ ]*[a-zA-Z][ ]*\\([ ]*[0-9]{1,}[ ]*,[ ]*[0-9]{1,}[ ]*\\)[ ]*", placePatch});

        //put online (done)
        Command done = Done();
        commands.insert({"done", done});
    }

    Command PlacePatch(){
        return Command("places patch, syntax: \"( patch type, coord x, coord y )\" "
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


                           return CommandEndType::VALID;
                       }
        );
    }

    Command Done(){
        return Command("Type it when you are done - you think FireWall can survive the next attack.",
                       []( const string& userInput, Game & g, Interface & i){
                           g.GameState(State::ATTACK);
                           return CommandEndType::DONE;
                       }
        );
    }

    Command Exit(){
        return Command(
                "exits the game witout saving",
                [](const string& , Game &, Interface &)
                    { return CommandEndType::ENDGAME;}      );
    }

};

