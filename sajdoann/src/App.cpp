/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include "Game/GameConstants.h"
#include "App.h"

void App::Greet() {
    interface.Greet();
    interface.ClearScreen();
}

int App::PrepLoop() {
    while (game.GameState() == State::PREPARATION) {
        interface.PrintBoardPrep(game.GameBoard());
        string command = interface.PromptCommand();
        bool found = false;

        for (auto &com : commands.CommandsMap()) {
            //makes regex from com name
            regex c("[ ]*" + com.first + "[ ]*",
                    regex_constants::icase);   //spaces before after allowed + case insensitive

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

    try {
        game.LoadGame(DEFAULT_PATH);
    } catch (invalid_argument &invalid_argument) {
        cerr << invalid_argument.what();
        return 1;
    } catch (runtime_error &runtime_error) {
        cerr << runtime_error.what();
        return 2;
    }

    bool firstPrep = true;
    game.GameState(State::ATTACK);
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

                //if user looses then go to end
                if (game.GameResult() == LOSE) {
                    game.GameState(State::END);
                    break;
                }
                game.GameState(State::PREPARATION);
                break;
            }
            case State::END: {
                //todo: end/new logic
                //play new game/ exit
                // interface.EndAsker();
                return 0;
            }
        }

    }

}

int App::AttackLoop() {
    game.MoveLoop(interface);
    return 0;
}
