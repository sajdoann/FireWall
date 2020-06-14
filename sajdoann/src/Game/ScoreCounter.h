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


public:
    Counter() = default;

    Counter(int ram, int ramStart, int level, int money)
            : ram(ram), ramStart(ramStart), level(level), money(money) {}

    Counter &operator=(const Counter &other) {
        if (this == &other) return *this;
        ram = other.ram;
        ramStart = other.ramStart;
        level = other.level;
        money = other.money;
        return *this;
    }

    Counter(const Counter &other) {
        *this = other;
    }

    int Ram() const { return ram; }

    void takeRam(int take) { ram -= take; }

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


