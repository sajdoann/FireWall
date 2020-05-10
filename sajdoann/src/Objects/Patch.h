/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include "Object.h"
#include "Hotfix.h"

using namespace std;

/**
 * patch is an Object that has name, type, price and range
 * In the FireWall game it can be placed on Board
 * It shoots hotfixes
 */
class Patch : public Object {
protected:
    char type = 'W';
    char name = 'W';
    int price = 10;
    int range = 0;
    //MovementType movementType;            //commented becasue not impllemented, but later on will be there
    //MovementDirection movementDirection;
public:
    Patch() = default;

    Patch(char name, char type, int price, int range) noexcept
            : Object(), type(type), name(name), price(price), range(range) {}

    ~Patch() override = default;

    /** gets the name of the patch */
    char Name() const { return name; }

    /** gets the type of the patch */
    char Type() const { return type; }

    /** gets the price of the patch */
    int Price() const { return price; }

    /** gets the range patch can reach */
    int Range() const { return range; }

    /** less comparator for patch by its name*/
    int operator<(const Patch &patch) const {
        if (name != patch.name)
            return (name < patch.name) ? -1 : 1;
        return 0;
    }

    /** compare function by name */
    struct cmp {
        int operator()(const Patch &a, const Patch &b) {
            return a < b;
        }
    };

    /** prints all available information for patches */
    friend ostream &operator<<(ostream &os, const Patch &patch) {
        os << " " << patch.name << " " << patch.type << " " << patch.price << " " << patch.range;
        return os;
    }

    /** prints just the name representation of object */
    ostream &PrintObject(ostream &os) override {
        //TODO: ansi escape sequence zabira misto
        // -> setw3 si mysli ze nemusi vypisovat mezery navic <- vyresit nedavat na tvrdo jak ted za ansi escape :D
        //TODO: predelat do const char *
        return os << "\u001b[31m  " << (*this).name << "\u001b[0m";
    }

    /** prints all available information for patches */
    ostream &PrintInfo(ostream &os) override {
        return os << (*this);
    }

    bool isMovingObject() override { return false; }

    /** gets patch atributes from istream */
    friend istream &operator>>(istream &ifs, Patch &patch) {
        return ifs >> patch.name >> patch.type >> patch.price >> patch.range;
    }

    Hotfix *ShootHotfix() {
        //    return new Hotfix(movementType, movementDirection);
    }

};

