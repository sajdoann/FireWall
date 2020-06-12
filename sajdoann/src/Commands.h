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
#include "constants.h"

using namespace std;

class Commands {
    map<string, Command> commands;


public:

    map<string, Command> &CommandsMap() {
        return commands;
    }

    void CreateCommands() {
        //TODO place const chars in separate file
        //exit command
        Command exit = Exit();
        commands.insert({EXIT_NAME, exit});

        //placePatch command, it places the patch
        Command placePatch = PlacePatch();
        commands.insert({PATCH_REGEX, placePatch});

        //put online (done)
        Command done = Done();
        commands.insert({DONE_NAME, done});

        //help
        Command help = Help();
        commands.insert({HELP_NAME, help});

        //google patch
        Command google = Google();
        commands.insert({GOOGLE_REGEX, google});

        //save game
        Command save = Save();
        commands.insert({SAVE_NAME, save});

        Command load = Load();
        commands.insert({LOAD_NAME, load});

    }

    Command PlacePatch() {
        return Command(PATCH_NAME, PATCH_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           char patchName;
                           Coords coords;
                           i.GetPatchInfo(userInput, patchName, coords);

                           //validates input
                           if (!g.isPatch(patchName) || g.OutOfGameBoard(coords)) {
                               return CommandEndType::INVALID;
                           }

                           g.InsertPatch(patchName, coords);


                           return CommandEndType::VALID;
                       }
        );
    }

    Command Done() {
        return Command(DONE_NAME, DONE_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           g.GameState(State::ATTACK);
                           return CommandEndType::DONE;
                       }
        );
    }

    Command Exit() {
        return Command(EXIT_NAME,
                       EXIT_HELP,
                       [](const string &, Game &, Interface &) { return CommandEndType::ENDGAME; });
    }

    Command Help() {
        return Command(HELP_NAME,
                       HELP_HELP,
                       [this](const string &, Game &, Interface &i) {
                           for (const auto &c : commands) {
                               i.PrintHelp(c.second.Name(), c.second.Help());
                           }
                           return CommandEndType::VALID;
                       });
    }

    Command Google() {
        return Command(GOOGLE_NAME, GOOGLE_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           stringstream s(userInput);
                           string google;
                           s >> google;
                           char c;
                           s >> c;
                           c = toupper(c);

                           if (!g.isPatch(c)) {
                               return CommandEndType::INVALID;
                           } else {
                               i.PrintPatchInfo(g.getPatch(c));
                               return CommandEndType::VALID;
                           }

                       }
        );
    }


    /**
     * saves the game when called
     * @return command to save the game
     */
    Command Save() {
        return Command(SAVE_NAME,
                       SAVE_HELP,
                       saveFunction());
    }

    /**
     * makes directory (asks user for name) and saves all neadable data for game to it
     * @return function to execute for saving
     */
    function<CommandEndType(string, Game &, Interface &)> saveFunction() {
        return [](const string &, Game &g, Interface &i) {
            string name = SAVES_PATH + i.PromptSaveFolder();

            DIR *dir = opendir(name.c_str());
            if (dir == nullptr) {
                system(("mkdir " + name).c_str());
            }
            closedir(dir);

            g.SaveGame(name);
            return CommandEndType::VALID;

        };
    }


    function<CommandEndType(string, Game &g, Interface &)> loadFunction() {
        return [](const string &, Game &g, Interface &anInterface) {
            vector<string> fileNames;                                   //will contain filenames from save directory
            struct dirent *entry;
            DIR *dir = opendir(SAVES_PATH);
            if (dir != nullptr) {
                while ((entry = readdir(dir))) {                         //loads all files in dir
                    if (entry->d_type != DT_DIR) continue;                // not directory -> continue

                    bool isReadable = true;                              //contains only allowed chars
                    for (auto i: entry->d_name) {
                        if (!isdigit(i) && !isalpha(i) && i != '\0') {
                            isReadable = false;
                            break;
                        }
                        if (i == '\0') break;
                    }

                    if (isReadable)
                        fileNames.push_back(entry->d_name);
                }
            }

            closedir(dir);

            string s = anInterface.chooseFile(fileNames);
            // g.LoadGame();

            return CommandEndType::DONE;

        };
    }

    /**
     * prints all saved game and user picks the game to load
     * @return
     */
    Command Load() {
        return Command(LOAD_NAME, LOAD_HELP, loadFunction());
    }

};

