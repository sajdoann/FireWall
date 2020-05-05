/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include "App.h"


int App::Run() {

    interface.PrintBoard(game.GameBoard());

    if(game.GameState() == State::WELCOME){
        interface.Greet();
        game.GameState(State::PREPARATION);
    }


    while (game.GameState() == State::PREPARATION){
        string command = interface.PromptCommand();
        bool found = false;

        for(auto & com : commands){
            regex c(com.first);

            //if command matches with regex key in map of commands
            if(regex_match(command, c)){
                CommandEndType toDoNext = com.second.Exec(command, game, interface);
                //executes command and finds out what to do next
                switch (toDoNext) {
                    case CommandEndType::ENDGAME:{
                        return 0;
                    }
                    case CommandEndType::INVALID:{
                        //the text matches but its an invalid move
                        cout << "This move cannot be executed." << endl;
                        cout << "Check if the names, coordinates are valid and you have enough RAM to support the patch" << endl;
                    }
                    case CommandEndType::DONE:{
                        game.GameState(State::ATTACK);
                        found = true;
                    }
                }
                break;
            }
        }

        // no command was found, suggest to use help
        if(!found) interface.HelpAdvertiser();
    }





}
