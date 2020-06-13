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
    int ram = RAM_CONSTANT;        //TODO: zapojit do třídy
    int ramStart = RAM_CONSTANT;
    int level = 0;
    int money = 50;


public:
    ScoreCounter() = default;

    ScoreCounter(int ram, int ramStart, int level, int money)
            : ram(ram), ramStart(ramStart), level(level), money(money) {}

    int Ram() const { return ram; }

    int takeRam(int take) { ram -= take; }

    int RamStart() const { return ramStart; }

    int Level() const { return level; }

    void IncreaseLevel() { ++level; }

    int Money() const { return money; }

    bool Buy(int cost) {
        if (money - cost < 0) return false;
        money -= cost;
        return true;
    }
};


