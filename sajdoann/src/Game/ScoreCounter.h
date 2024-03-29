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
class Counter {
    int ram = RAM_CONSTANT;
    int ramStart = RAM_CONSTANT;
    int level = 0;
    int money = 50;
    const static int INCREASE = 10;


public:
    Counter() = default;

    Counter(int ram, int ramStart, int level, int money)
            : ram(ram), ramStart(ramStart), level(level), money(money) {}

    Counter &operator=(const Counter &other);

    Counter(const Counter &other) {
        *this = other;
    }

    int Ram() const { return ram; }

    /**
     * substracts take from ram
     * @param take - what to substract from ram
     */
    void takeRam(int take) { ram -= take; }

    int RamStart() const { return ramStart; }

    int Level() const { return level; }

    void IncreaseLevel() { ++level; }

    void AddMoney() { money += INCREASE; }

    int Money() const { return money; }

    bool Buy(int cost);
};


