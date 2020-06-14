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
#include "Commands_Constants.h"

using namespace std;

/**
 * all possible commands that can be executed
 * in commands map are all commands that can be done during prep state
 */
class Commands {
    map<string, Command> commands;


public:

    map<string, Command> &CommandsMap() {
        return commands;
    }

    /**
     * creates commands puts them in the commands map
     */
    void CreateCommands();

    Command PlacePatch();

    Command Done();

    Command Exit();

    Command Help();

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


    function<CommandEndType(string, Game &g, Interface &)> loadFunction();

    /**
     * prints all saved game and user picks the game to load
     * @return
     */
    Command Load();

    Command Patches();

    Command Viruses();

    Command ShowBoard();

    Command Quit();

    Command Explain();
};

