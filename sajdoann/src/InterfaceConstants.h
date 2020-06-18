/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/27/2020
*/
/**
 * constants for interaction with user
 */
namespace IntrConstants {
    const static char *ENTER_COMMAND = "Enter command: ";
    const static char *HELP_ADVERTISE = "Unknown command. \n To see help type \"help\"";

    const static char *EXPLANATION = "Your goal is to place patches so no virus could break through your wall. \n"
                                     "To do that type in name of patch (coord1, coord2) (fe: \"W(0,0)\" ) \n"
                                     " what the letters mean:\n"
                                     "         .   E - empty\n"
                                     "         .   W - wall\n"
                                     "         .   other letter - some super special patch you can google up (use: \"google\" + name of patch)\n"
                                     "To see what the IT departament came with so far type \'show.\'\n"
                                     "When you want to put the patch online where it can be attacked by viruses type \'done\'\n"
                                     "To continue press enter.";

    const static char *GREETING = "There is a very important mission ahead of you.\n"
                                  "The FireWall has breaches, your goal is to survive next vicious attack from the hackers.\n"
                                  "Try your best while placing patches, so the dangerous mallware cannot survive through your barrier\n"
                                  "Your entire computer could fall apart if you dont!"
                                  " I wish you good luck :) \n\n"
                                  "To continue press enter.";

    const static char *INVALID_MOVE = "Cannot be executed.";

    const static char *LOST_MESSAGE = "You lost!";
    const static char *WIN_MESSAGE = "Congrats! You won!";

    const static char *LOAD_OR_NEW = "to start new game type \'new\'\n"
                                     "To load game from existing sources type \'load\'\n"
                                     "to exit type \'exit\'";

    const static char *RAM_COLOR_START = "\u001b[48;5;";
}