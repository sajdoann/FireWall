/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/12/2020
*/

#pragma once

/**
 * constants for commands - their names, regex, help
 */
const static char *EXIT_NAME = "exit";
const static char *EXIT_HELP = "exits the game witout saving. To save type save";

const static char *PATCH_NAME = "type(x,y)";
const static char *PATCH_REGEX = "[a-z][ ]*\\([ ]*[0-9]{1,}[ ]*,"
                                 "[ ]*[0-9]{1,}[ ]*\\)";
const static char *PATCH_HELP = "places patch, syntax: "
                                "\" patch Type (coord x, coord y)\""
                                " ... for example \"W(0,0)\"";

const static char *DONE_NAME = "done";
const static char *DONE_HELP = "type it when you are done - you think FireWall can survive the next attack.";

const static char *HELP_NAME = "help";
const static char *HELP_HELP = "lists all the commands";

const static char *GOOGLE_NAME = "google";
const static char *GOOGLE_REGEX = "[ ]*google[ ]*[a-z!@#$%^&?]{1}[ ]*";
const static char *GOOGLE_HELP = "type the name of the object and all you will get all info about it";

const static char *SAVE_NAME = "save";
const static char *SAVE_HELP = "saves the game into files";

const static char *LOAD_NAME = "load";
const static char *LOAD_HELP = "loads game from saved games";

const static char *PATCHES_NAME = "patches";
const static char *PATCHES_HELP = "describes all patches";

const static char *VIRUSES_NAME = "viruses";
const static char *VIRUSES_HELP = "describes all viruses";

const static char *SHOW_NAME = "show";
const static char *SHOW_HELP = "shows the entire firewall that was till now coded.";

const static char *NOT_AN_OBJECT = "is not object in the game.";
const static char *QUIT_NAME = "quit";
const static char *QUIT_HELP = "quits the current game and goes to menu (where new game or load saved game can be choosed)";

const static char *EXPLAIN_NAME = "explain";
const static char *EXPLAIN_HELP = "explains game";

const static char *INVALID_NOT_A_PATCH_OR_OUT_OF_BOARD = "Not a patch or coords are out of board.";
const static char *INVALID_NOT_ENOUGH_MONEY = "Not enough money to buy patch.";

const static char *MKDIR = "mkdir ";