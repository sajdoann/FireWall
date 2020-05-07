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
 *  .
 *  .   puts the game and interface together
 */
class App {
    Game game;
    Interface interface;
    Commands commands;

public:
    App() : game(), interface(cin, cout) {
        commands.CreateCommands();
    }



    Board & GameBoard(){return game.GameBoard(); }

    void GameState(State & state){ game.GameState(state); }

    void Greet();
    int PrepLoop();
    int AttackLoop();
    /**
     * game loop
     * @return no errors 0 / app errors nonzero number
     */
    int Run();

};



