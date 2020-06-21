/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <string>

#include "Game/Game.h"
#include "Interface.h"
#include "Command.h"
#include "Commands.h"

using namespace std;

/**
 * class that
 *  .   guides the game
 *  .   puts the game and interface together
 */
class App {
    Game game;
    Interface interface;
    Commands commands;


    /** menu switcher - new goes to default files*/
    const char *NEW = "new";
    /** menu switcher - new goes to saved files*/
    const char *LOAD = "load";
    /** menu switcher - exits the game */
    const char *EXIT = "exit";

    /**
     *  menu mode switches bteweeen new game, load game and exit
     * @return true if exit the game, false stay in game
     */
    CommandEndType MenuSwitcher();

    /**
     * help function to go to menu switcher
     * catches all possible errors
     * @return 0 - all was ok, 1 - exit game, other number - error occured
     */
    int to_menu_Switch();

    /**
     * finds command and executes it
     * @param command - input command from user
     * @return command end type - what to do next
     */
    CommandEndType FindAndExecCommand(string &command);

    /**
     * during Attack loop
     * creates wave of viruses for the attack, moves with the objects on board,
     * sleeps for certain amount of time
     */
    void MoveLoop();

public:
    App() :
            game(),
            interface(cin, cout) {
        commands.CreateCommands();
    }

    ~App() = default;

    /** getter for game board */
    Board &GameBoard() { return game.GameBoard(); }

    /** getter for game state */
    void GameState(State &state) { game.GameState(state); }

    /** welcomes the user */
    void Greet();

    /**loop for prep state
       @return 0 to end game, 1 to continue
     */
    int PrepLoop();

    /**
     * loop for attack, moves objects, deals with collisions
     */
    void AttackLoop();

    /**
     * game loop, goes through game states
     * @return no errors 0 / app errors nonzero number
     */
    int Run();
};

