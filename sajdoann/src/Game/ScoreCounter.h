/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "ResultEnum.h"
#include "GameConstants.h"

/**
 * counts score based on how many viruses survive through the wall
 */
class ScoreCounter {
    ResultEnum gameResult = ResultEnum::UNKNOWN;
    int ram = RAM_CONSTANT;        //TODO: zapojit do třídy
    int ramStart = RAM_CONSTANT;
    int level = 0;
    int money = 50;


public:
    //TODO: implement this
    ScoreCounter() = default;

    ScoreCounter(ResultEnum gameResult, int ram, int ramStart, int level, int money)
            : gameResult(gameResult), ram(ram), ramStart(ramStart), level(level), money(money) {}


};


