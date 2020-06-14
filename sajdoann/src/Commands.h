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

class Commands {
    map<string, Command> commands;


public:

    map<string, Command> &CommandsMap() {
        return commands;
    }

    void CreateCommands() {
        Command exit = Exit();
        commands.insert({EXIT_NAME, exit});

        Command placePatch = PlacePatch();
        commands.insert({PATCH_REGEX, placePatch});

        Command done = Done();
        commands.insert({DONE_NAME, done});

        Command help = Help();
        commands.insert({HELP_NAME, help});

        Command google = Google();
        commands.insert({GOOGLE_REGEX, google});

        Command save = Save();
        commands.insert({SAVE_NAME, save});

        // Command load = Load();
        //commands.insert({LOAD_NAME, load});

        Command patches = Patches();
        commands.insert({PATCHES_NAME, patches});

        Command viruses = Viruses();
        commands.insert({VIRUSES_NAME, viruses});


        Command showBoard = ShowBoard();
        commands.insert({SHOW_NAME, showBoard});

        Command quit = Quit();
        commands.insert({QUIT_NAME, quit});

        Command explain = Explain();
        commands.insert({EXPLAIN_NAME, explain});


    }

    Command PlacePatch() {
        return Command(PATCH_NAME, PATCH_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           char patchName;
                           Coords coords;
                           i.GetPatchInfo(userInput, patchName, coords);

                           //validates input
                           if (!g.isPatch(patchName) || g.OutOfGameBoard(coords)) {
                               i.PrintString("Not a patch or coords are out of board.");
                               return CommandEndType::INVALID;
                           }

                           if (g.BuyPatch(g.getPatch(patchName).Price()))
                               g.InsertPatch(patchName, coords);
                           else {
                               i.PrintString("Not enough money to buy patch.");
                               return CommandEndType::INVALID;
                           }


                           return CommandEndType::VALID;
                       }
        );
    }

    Command Done() {
        return Command(DONE_NAME, DONE_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           g.GameState(State::ATTACK);
                           return CommandEndType::VALID;
                       }
        );
    }

    Command Exit() {
        return Command(EXIT_NAME,
                       EXIT_HELP,
                       [](const string &, Game &g, Interface &) {

                           return CommandEndType::ENDGAME;
                       });
    }

    Command Help() {
        return Command(HELP_NAME,
                       HELP_HELP,
                       [this](const string &, Game &, Interface &i) {
                           i.PrintString(HELP_NAME);
                           for (const auto &c : commands) {
                               i.PrintHelp(c.second.Name(), c.second.Help());
                           }
                           i.PrintString("\n");

                           return CommandEndType::VALID;
                       });
    }

    Command Google() {
        return Command(GOOGLE_NAME, GOOGLE_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           const char *strInput = userInput.c_str();
                           stringstream s(strInput);
                           string google;
                           s >> google;
                           char c;
                           s >> c;
                           c = toupper(c);

                           if (g.isPatch(c)) {
                               i.PrintObjectInfo(g.getPatch(c));
                           } else if (g.isVirus(c)) {
                               i.PrintObjectInfo(g.getVirus(c));
                           } else {
                               i.PrintString(c + NOT_AN_OBJECT);
                           }
                           return CommandEndType::VALID;
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

            string s = SAVES_PATH;
            s = s + "/" + anInterface.chooseFile(fileNames);
            g.LoadGame(s);

            return CommandEndType::VALID;

        };
    }

    /**
     * prints all saved game and user picks the game to load
     * @return
     */
    Command Load() {
        return Command(LOAD_NAME, LOAD_HELP, loadFunction());
    }

    Command Patches() {
        return Command(PATCHES_NAME, PATCHES_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           for (auto iterP : g.Patches()) {
                               i.PrintObjectInfo(*iterP.second);
                           }
                           return CommandEndType::VALID;
                       }
        );
    }

    Command Viruses() {
        return Command(VIRUSES_NAME, VIRUSES_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           for (auto iterV : g.Viruses()) {
                               i.PrintObjectInfo(*iterV.second);
                           }
                           return CommandEndType::VALID;
                       }
        );
    }

    Command ShowBoard() {
        return Command(SHOW_NAME, SHOW_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           i.PrintGamePane(g.GameState(), g.getScoreCounter(), g.GameBoard());
                           return CommandEndType::VALID;
                       }
        );
    }

    Command Quit() {
        return Command(QUIT_NAME, QUIT_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           g.GameState(MENU);
                           return CommandEndType::VALID;
                       }
        );
    }

    Command Explain() {
        return Command(EXPLAIN_NAME, EXPLAIN_HELP,
                       [](const string &userInput, Game &g, Interface &i) {
                           i.ExplainPrepState();
                           return CommandEndType::VALID;
                       }
        );
    }
};

