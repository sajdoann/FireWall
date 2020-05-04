/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#include <string>
#include <regex>
#include "App.h"

int App::Run() {


    while (true){
        string command = interface.PromptCommand();

        for(auto com = commands.begin()  ; com != commands.end(); ++com){
            regex c(com->first);
            bool match = regex_match(command, c);
            if(match){
                //execute command, in case it returns false exit program
                if(!(com->second.Exec(game, interface))) return 0;
            }
        }

        interface.HelpAdvertiser();
    }
}
