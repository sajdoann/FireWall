/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/27/2020
*/
#pragma once
const static char *ENTER_COMMAND = "Enter command: ";
const static char *HELP_ADVERTISE = "Unknown command. \n To see help type \"help\"";

const static char *EXPLANATION = "Now your goal is to place patches so no virus could break through your wall. \n"
                                 "To do that type in name of patch (coord1, coord2) (fe: \"W(0,0)\" ) \n"
                                 "To see:\n"
                                 "        .    all possible commands type \"help\"\n"
                                 "        .    all possible patches and their info type \"patches\"\n\n"
                                 "This is what the IT departament came with so far:\n\n"
                                 " what the letters mean:\n"
                                 "         .   E - empty\n"
                                 "         .   W - wall\n"
                                 "         .   other letter - some super special patch you can google up (use: \"google\" + name of patch)\n\n"

                                 "After you are done, just type in \"done\" and the hackers might try to breach in.\n";
const static char *GREETING = "Hello!\n"
                              "There is a very important mission ahead of you.\n"
                              "The FireWall has breaches, your goal is to survive next vicious attack from the hackers.\n"
                              "Try your best while placing patches, so the dangerous mallware cannot survive through your barrier\n"
                              "Your entire computer could fall apart if you dont!"
                              "I wish you good luck :) \n\n"
                              "To continue press enter";

const static char *INVALID_MOVE = "This move cannot be executed.\n"
                                  "Check if the names, coordinates are valid "
                                  "and you have enough RAM to support the patch";

const static char *LOST_MESSAGE = "You lost!";
const static char *WIN_MESSAGE = "Congrats! You won!";