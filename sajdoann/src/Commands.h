/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/6/2020
*/

#pragma once

#include <string>
#include <dirent.h>
//#include <filesystem>          //TODO: -lstdc++fs to flags
#include "Command.h"
#include "Game/IOLoaders/Writer.h"

using namespace std;

/**
 * all possible commands that can be executed
 * in commands map are all commands that can be done during prep state
 */
class Commands {
    map<string, Command> commands;


public:

    /** gets commands map */
    map<string, Command> &CommandsMap() {
        return commands;
    }

    /**
     * creates commands puts them in the commands map
     */
    void CreateCommands();

    /** places patch */
    Command PlacePatch();

    /** goes to attack stage */
    Command Done();

    /** exits the game without saving */
    Command Exit();

    /** prints all available commands */
    Command Help();

    /** googles object */
    Command Google();


    /**
     * saves the game when called
     * @return command to save the game
     */
    Command Save();

    /**
     * makes directory (asks user for name) and saves all neadable data for game to it
     * @return function to execute for saving
     */
    function<CommandEndType(string, Game &, Interface &)> saveFunction();

    /**
     * returns function that asks from where to load and loads game
     * @return  function to execute
     */
    function<CommandEndType(string, Game &g, Interface &)> loadFunction();

    function<CommandEndType(string, Game &g, Interface &)> newFunction();

    /**
     * prints all saved game and user picks the game to load
     * @return
     */
    Command Load();

    Command New();

    /** shows patches */
    Command Patches();

    /** shows viruses */
    Command Viruses();

    /** shows board */
    Command ShowBoard();

    /** quits the game goes to menu */
    Command Quit();

    /** explains prep state */
    Command Explain();
};

