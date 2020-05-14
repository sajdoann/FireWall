/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include "App.h"

void App::Greet() {
    interface.Greet();
    interface.ClearScreen();
}

int App::PrepLoop() {
    while (game.GameState() == State::ATTACK) {
        interface.PrintBoardPrep(game.GameBoard());

        string command = interface.PromptCommand();
        bool found = false;

        for (auto &com : commands.CommandsMap()) {
            //makes regex from com name
            regex c(com.first);

            //if command matches with regex key in map of commands
            if (regex_match(command, c)) {
                interface.ClearScreen();

                //ececutes command
                CommandEndType typeOfCommand = com.second.Exec(command, game, interface);
                // finds out what to do next
                switch (typeOfCommand) {
                    case CommandEndType::ENDGAME: {
                        return 0;
                    }
                    case CommandEndType::INVALID: {
                        interface.InvalidMove();
                        break;
                    }
                }
                found = true;
                break;
            }
        }

        // no command was found, suggest to use help
        if (!found) interface.HelpAdvertiser();
    }
    return 1;
}

int App::Run() {
    bool firstPrep = true;
    game.GameState(State::PREPARATION);
    while (true) {
        switch (game.GameState()) {
            case State::WELCOME: {
                Greet();
                game.GameState(State::PREPARATION);
                break;
            }
            case State::PREPARATION: {
                if (firstPrep) {
                    interface.ExplainPrepState();
                    firstPrep = false;
                }
                if (!PrepLoop()) return 0;
                break;
            }
            case State::ATTACK: {
                interface.ClearScreen();
                AttackLoop();
                interface.PrintResult(game.GameResult());
                game.GameState(State::PREPARATION);
                break;
            }
            case State::END: {
                return 0;
            }
        }

    }

}

int App::AttackLoop() {
    game.MoveLoop();
    return 0;
}
