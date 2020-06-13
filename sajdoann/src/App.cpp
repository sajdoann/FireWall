/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include "Game/GameConstants.h"
#include "App.h"

int App::Run() {
    Greet();
    while (true) {
        switch (game.GameState()) {
            case State::MENU: {
                interface.PrintState(game.GameState());
                bool end;

                int error = to_menu_Switch();
                if (error == 1) return 0;
                else if (error) return error;


                game.GameState(State::PREPARATION);
                interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
                break;
            }
            case State::PREPARATION: {
                if (!PrepLoop()) return 0;
                break;
            }
            case State::ATTACK: {
                interface.ClearScreen();
                AttackLoop();
                interface.PrintResult(game.GameResult());

                //if user looses then go to MENU
                if (game.GameResult() == LOSE) {
                    game.GameState(State::MENU);
                    break;
                }
                game.GameState(State::PREPARATION);
                break;
            }
        }

    }

}

void App::Greet() {
    interface.Greet();
    interface.ClearScreen();
}

int App::PrepLoop() {
    while (game.GameState() == State::PREPARATION) {
        // interface.PrintBoard(game.GameBoard());
        string command = interface.PromptCommand();
        CommandEndType endType = FindAndExecCommand(command);
        if (endType == CommandEndType::ENDGAME)
            return 0;
        else if (endType == CommandEndType::INVALID) {
            interface.InvalidMove();
        } else {
            break;
        }
    }
    return 1;
}


int App::AttackLoop() {
    game.MoveLoop(interface);
    return 0;
}

bool App::MenuSwitcher() {
    while (true) {
        string recievedString = interface.AskWhichGame();
        string command;
        for (int i = 0; i < recievedString.size(); i++) {
            if (isalpha(recievedString[i]))
                command.push_back(toupper(recievedString[i]));

        }
        if (command == "NEW") {
            game.LoadGame(DEFAULT_PATH);
            return false;
        }
        if (command == "LOAD") {
            commands.Load().Exec(command, game, interface);
            return false;
        }
        if (command == "EXIT") {
            commands.Exit().Exec(command, game, interface);
            return true;
        }
    }

}

CommandEndType App::FindAndExecCommand(string &command) {
    bool found = false;
    for (auto &com : commands.CommandsMap()) {

        regex c("[ ]*" + com.first + "[ ]*",                //makes regex from com name
                regex_constants::icase);   //spaces before after allowed + case insensitive

        if (regex_match(command, c)) {                  //if command matches with regex key in map of commands
            interface.ClearScreen();

            //executes command
            CommandEndType typeOfCommand = com.second.Exec(command, game, interface);

            if (typeOfCommand == ENDGAME || typeOfCommand == INVALID)
                return typeOfCommand;

            found = true;
            break;
        }
    }
    // no command was found, suggest to use help
    if (!found)
        interface.HelpAdvertiser();
}

int App::to_menu_Switch() {
    int end;
    try {
        end = MenuSwitcher();
    } catch (invalid_argument &invalid_argument) {
        cerr << invalid_argument.what();
        return 2;
    } catch (runtime_error &runtime_error) {
        cerr << runtime_error.what();
        return 3;
    } catch (logic_error &logic_error) {
        cerr << logic_error.what();
        return 4;
    }
    if (end)
        return 1;
    return 0;
}


