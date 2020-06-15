/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/20/2020
*/

#pragma once
/**
 * class that has all constants needed for game
 */

/** how many times virus move during attack stage, in game steadily increased by level */
//const int MOVEMENT_LOOP_MAX = 100;

/** board limit measures */
const static int MAX_BOARD_MEASURE = 100;
const static int MIN_BOARD_MEASURE = 1;

/** how many viruses can espace firewall, hence come through wall */
const static int RAM_CONSTANT = 20;
const static int MAX_RAM_CONSTANT = 50;
const static int MAX_LVL_CONSTANT = 20;

const static char *DEFAULT_PATH = "../sajdoann/data/Default";
const static char *SAVES_PATH = "../sajdoann/data/Saves";
