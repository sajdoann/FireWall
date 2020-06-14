/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/10/2020
*/

#include "ScoreCounter.h"


Counter &Counter::operator=(const Counter &other) {
    if (this == &other) return *this;
    ram = other.ram;
    ramStart = other.ramStart;
    level = other.level;
    money = other.money;
    return *this;
}

bool Counter::Buy(int cost) {
    if (money - cost < 0) return false;
    money -= cost;
    return true;
}
