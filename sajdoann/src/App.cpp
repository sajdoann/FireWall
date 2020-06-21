/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include <thread>
#include "App.h"

int App::Run() {
    Greet();
    while (true) {
        switch (game.GameState()) {
            case State::MENU: {
                interface.ClearScreen();
                interface.PrintState(game.GameState());

                int error = to_menu_Switch();
                if (error == 1) return 0;
                else if (error > 0) return error;

                game.GameState(State::PREPARATION);
                interface.ClearScreen();
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

                //if user looses then go to MENU
                if (game.GameResult() == LOSE) {
                    game.GameState(State::MENU);
                    break;
                }
                game.GameState(State::PREPARATION);
                interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
                break;
            }
        }

    }

}

void App::Greet() {
    interface.Greet();
}

int App::PrepLoop() {
    interface.ClearBuffers();
    while (game.GameState() == State::PREPARATION) {
        string command = interface.PromptCommand();


        CommandEndType endType;
        try {
            endType = FindAndExecCommand(command);
        }
        catch (system_error &systemError) {
            cerr << systemError.what() << endl;
        }

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


void App::AttackLoop() {

    MoveLoop();

    interface.ClearScreen();
    interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
    interface.PrintResult(game.GameResult());
    interface.ClearBuffers();

    game.GameBoard().ClearButPatches();
    if (game.GameResult() != LOSE) {
        game.getScoreCounter().AddMoney();
        game.getScoreCounter().IncreaseLevel();
    }

}

CommandEndType App::MenuSwitcher() {
    while (true) {
        string recievedString = interface.AskWhichGame();
        if (recievedString.empty()) continue;
        string command;
        for (unsigned int i = 0; i < recievedString.size(); i++) {
            if (isalpha(recievedString[i]))
                command.push_back(tolower(recievedString[i]));

        }
        if (command == NEW) {
            commands.New().Exec(command, game, interface);
            return CommandEndType::VALID;
        }
        if (command == LOAD) {
            commands.Load().Exec(command, game, interface);
            return CommandEndType::VALID;
        }
        if (command == EXIT) {
            commands.Exit().Exec(command, game, interface);
            return CommandEndType::ENDGAME;
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
            interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
            CommandEndType typeOfCommand = com.second.Exec(command, game, interface);  //executes command

            if (typeOfCommand == ENDGAME || typeOfCommand == INVALID)
                return typeOfCommand;

            found = true;
            break;
        }
    }
    // no command was found, suggest to use help
    if (!found) {
        interface.ClearScreen();
        interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
        interface.HelpAdvertiser();

    }
    return CommandEndType::VALID;
}


int App::to_menu_Switch() {
    CommandEndType end;
    try {
        end = MenuSwitcher();
    } catch (invalid_argument &invalid_argument) {
        cerr << invalid_argument.what() << endl;
        return 2;
    } catch (runtime_error &runtime_error) {
        cerr << runtime_error.what() << endl;
        return 3;
    } catch (logic_error &logic_error) {
        cerr << logic_error.what() << endl;
        return 4;
    }
    if (end == CommandEndType::ENDGAME)
        return 1;
    return 0;
}

void App::MoveLoop() {
    int virusPoints = 0;
    int loopMax =
            (game.GameBoard().MaxY() + game.GameBoard().MaxY() / 2) + (2 * game.getScoreCounter().Level() + 2) * 2;
    for (int i = 0; i < loopMax; ++i) {
        virusPoints = 0;

        game.GenerateAndPlaceViruses();

        virusPoints += game.MoveAll();
        game.getScoreCounter().takeRam(virusPoints);

        if (game.getScoreCounter().Ram() < 0) {
            game.GameResult(LOSE);
            game.GameState(State::MENU);
            break;
        }

        interface.ClearScreen();
        interface.PrintGamePane(game.GameState(), game.getScoreCounter(), game.GameBoard());
        interface.PrintClock(loopMax - i - 1);

        this_thread::sleep_for(0.3s);
    }
}



