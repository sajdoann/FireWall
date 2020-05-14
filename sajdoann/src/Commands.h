/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/6/2020
*/

#pragma once

#include <string>
#include "Command.h"
#include "Game/IOLoaders/Writer.h"
#include "constants.h"

using namespace std;

/**
 * remembers all commands that can be executed during game
 */
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


    Command Save() {
        return Command(SAVE_NAME,
                       SAVE_HELP,
                       saveFunction());
    }

    function<CommandEndType(string, Game &, Interface &)> saveFunction() {
        return [](const string &, Game &g, Interface &i) {

            Writer patchWriter("../sajdoann/saves/ahoj.txt");
            patchWriter.getHeading(*(g.Patches().begin()->second));
            patchWriter.writeToFile(g.Patches());

            Writer VirusWriter("../sajdoann/saves/jak.txt");
            VirusWriter.getHeading(*(g.Viruses().begin()->second));
            VirusWriter.writeToFile(g.Viruses());


            return CommandEndType::VALID;

        };
    }


};

