/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/12/2020
*/

#pragma once

const static char *EXIT_NAME = "exit";
const static char *EXIT_HELP = "exits the game witout saving. To save type save";

const static char *PATCH_NAME = "type(x,y)";
const static char *PATCH_REGEX = "[ ]*[a-zA-Z][ ]*\\([ ]*[0-9]{1,}[ ]*,"
                                 "[ ]*[0-9]{1,}[ ]*\\)[ ]*";
const static char *PATCH_HELP = "places patch, syntax: "
                                "\" patch Type (coord x, coord y)\""
                                " ... for example \"W(0,0)\"";

const static char *DONE_NAME = "done";
const static char *DONE_HELP = "Type it when you are done - you think FireWall can survive the next attack.";

const static char *HELP_NAME = "help";
const static char *HELP_HELP = "lists all the commands";

const static char *GOOGLE_NAME = "google";
const static char *GOOGLE_REGEX = "[ ]*google[ ]*[a-zA-Z]{1}";
const static char *GOOGLE_HELP = "You dont know what the leters on board mean? Type google and the name"
                                 "ot the patch";

const static char *SAVE_NAME = "save";
const static char *SAVE_HELP = "saves the game into files.";