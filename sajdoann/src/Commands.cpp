/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/14/2020
*/

#include "Commands.h"
#include "CommandsConstants.h"
#include "PathsConstants.h"

void Commands::CreateCommands() {
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

Command Commands::PlacePatch() {
    return Command(PATCH_NAME, PATCH_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       char patchName;
                       Coords coords;
                       i.GetPatchInfo(userInput, patchName, coords);

                       //validates input
                       if (!g.isPatch(patchName) || g.OutOfGameBoard(coords)) {
                           i.PrintString(INVALID_NOT_A_PATCH_OR_OUT_OF_BOARD);
                           return CommandEndType::INVALID;
                       }

                       if (g.BuyPatch(g.getPatch(patchName).Price()))
                           g.InsertPatch(patchName, coords);
                       else {
                           i.PrintString(INVALID_NOT_ENOUGH_MONEY);
                           return CommandEndType::INVALID;
                       }

                       i.ClearScreen();
                       i.PrintGamePane(g.GameState(), g.getScoreCounter(), g.GameBoard());
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::Done() {
    return Command(DONE_NAME, DONE_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       g.GameState(State::ATTACK);
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::Exit() {
    return Command(EXIT_NAME,
                   EXIT_HELP,
                   [](const string &, Game &g, Interface &) {

                       return CommandEndType::ENDGAME;
                   });
}

Command Commands::Help() {
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

Command Commands::Google() {
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

Command Commands::Save() {
    return Command(SAVE_NAME,
                   SAVE_HELP,
                   saveFunction());
}

function<CommandEndType(string, Game &, Interface &)> Commands::saveFunction() {
    return [](const string &, Game &g, Interface &i) {
        string name = SAVES_PATH + i.PromptSaveFolder();

        DIR *dir = opendir(name.c_str());
        if (dir == nullptr) {
            int err = system((MKDIR + name).c_str());
            if (err == -1)
                throw runtime_error("File cannot be created");
        }
        closedir(dir);

        g.SaveGame(name);
        return CommandEndType::VALID;

    };
}

function<CommandEndType(string, Game &g, Interface &)> Commands::loadFunction() {
    return [](const string &, Game &g, Interface &anInterface) {
        vector<string> fileNames = anInterface.getFilenames(
                SAVES_PATH);                        //will contain filenames from save directory
        string s = SAVES_PATH;
        s = s + "/" + anInterface.chooseFile(fileNames);
        g.LoadGame(s);
        return CommandEndType::VALID;
    };
}

function<CommandEndType(string, Game &g, Interface &)> Commands::newFunction() {
    return [](const string &, Game &g, Interface &anInterface) {
        vector<string> fileNames = anInterface.getFilenames(
                DEFAULT_PATH);                        //will contain filenames from save directory
        string s = DEFAULT_PATH;
        s = s + "/" + anInterface.chooseFile(fileNames);
        g.LoadGame(s);
        return CommandEndType::VALID;
    };
}

Command Commands::Load() {
    return Command(LOAD_NAME, LOAD_HELP, loadFunction());
}

Command Commands::New() {
    return Command(LOAD_NAME, LOAD_HELP, newFunction());
}


Command Commands::Patches() {
    return Command(PATCHES_NAME, PATCHES_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       for (auto iterP : g.Patches()) {
                           i.PrintObjectInfo(*iterP.second);
                       }
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::Viruses() {
    return Command(VIRUSES_NAME, VIRUSES_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       for (auto iterV : g.Viruses()) {
                           i.PrintObjectInfo(*iterV.second);
                       }
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::ShowBoard() {
    return Command(SHOW_NAME, SHOW_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       i.PrintGamePane(g.GameState(), g.getScoreCounter(), g.GameBoard());
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::Quit() {
    return Command(QUIT_NAME, QUIT_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       g.GameState(MENU);
                       return CommandEndType::VALID;
                   }
    );
}

Command Commands::Explain() {
    return Command(EXPLAIN_NAME, EXPLAIN_HELP,
                   [](const string &userInput, Game &g, Interface &i) {
                       i.ExplainPrepState();
                       return CommandEndType::VALID;
                   }
    );
}




