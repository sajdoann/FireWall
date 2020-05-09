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
        //TODO place const chars in separate file
        //exit command
        Command exit = Exit();
        commands.insert( {"exit" , exit});

        //placePatch command, it places the patch
        const char * doneRegex = "[ ]*[a-zA-Z][ ]*\\([ ]*[0-9]{1,}[ ]*,[ ]*[0-9]{1,}[ ]*\\)[ ]*";
        Command placePatch = PlacePatch();
        commands.insert({doneRegex, placePatch});

        //put online (done)
        const char * doneName = "done";
        Command done = Done();
        commands.insert({doneName, done});

        //help
        const char * helpName = "help";
        Command help = Help();
        commands.insert({helpName, help});

        //google patch

    }

    Command PlacePatch(){
        return Command("type(x,y)","places patch, syntax: \" patch Type (coord x, coord y)\""
                                     " ... for example \"W(0,0)\"",
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
        return Command("done","Type it when you are done - you think FireWall can survive the next attack.",
                       []( const string& userInput, Game & g, Interface & i){
                           g.GameState(State::ATTACK);
                           return CommandEndType::DONE;
                       }
        );
    }

    Command Exit(){
        return Command("exit",
                "exits the game witout saving",
                [](const string& , Game &, Interface &)
                    { return CommandEndType::ENDGAME;}      );
    }

    Command Help(){
        const char * helpName = "help";
        return Command(helpName,
                "lists all the commands",
                [this](const string& , Game &, Interface & i)
                {
                    for(const auto & c : commands){
                        i.PrintHelp(c.second.Name(), c.second.Help());
                    }
                    return CommandEndType::VALID;}      );
    }


};

