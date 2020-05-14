/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <iomanip>
#include "ObjectWithMoveAttributes.h"
#include "Hotfix.h"

using namespace std;

/**
 * patch is an Object that has name, type, price and range
 * In the FireWall game it can be placed on Board
 * It shoots hotfixes
 */
class Patch : public ObjectWithMoveAttributes {
protected:
    //char name = 'W';
    int price = 10;

    //FOR THEIR HOTFIXES


public:
    Patch() noexcept = default;

    Patch(char name, int price, MovementType movementType, MovementDirection movementDirection) noexcept
            : ObjectWithMoveAttributes(name, movementType, movementDirection), price(price) {}

    ~Patch() = default;

    virtual  Object * Clone() const {return new Patch(name, price, movementType, movementDirection);}


    Patch(Patch &patch) {
        *this = patch;
    }

    Patch &operator=(Patch &patch) {
        if (this == &patch) return *this;
        movementType = patch.movementType;
        movementDirection = patch.movementDirection;

        this->name = patch.name;
        this->price = patch.price;
        return *this;
    }

    /** gets the name of the patch */
    char Name() const { return name; }


    /** gets the price of the patch */
    int Price() const { return price; }


    /** gets the movement type of the hotfix that can be shooted */
    MovementType MovementTypePatch() const { return movementType; }

    /** gets the movement direction of hotfix that can be shooted */
    // MovementDirection movementDirectionPatch()const{return movementDirection;}


    /** returns false because patch is not a moving object */
    bool isMovingObject() const override { return false; }

    bool isEmpty() const { return false; }

    virtual bool isVirus() const { return false; };

    /** returns true if patch can shoot, here it cannot -> false */
    virtual bool CanShoot() const { return movementType != MovementType::NONE; }


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

    /** gets patch atributes from istream */
    friend istream &operator>>(istream &in, Patch &patch) {
        in >> patch.name;
        if (in.eof())
            return in;
        in >> patch.price;
        patch.MovementFromIn(in, patch.movementType);
        patch.DirectionFromIn(in, patch.movementDirection);
        return in;
    }


    istream &LoadObject(istream &is) override {
        is >> *this;
        return is;
    }

    /** prints all available information for patches */
    ostream &PrintInfo(ostream &os) const override {
        os << "name: " << name << " price: " << price << " movement: ";
        MovementToOut(os, movementType);
        os << " direction: ";
        DirectionsToOut(os, movementDirection);
        os << endl;
        return os;
    }

    Hotfix *ShootHotfix() {
        //return new Hotfix(movementType, movementDirection);
    }


    /** prints just the name representation of object */
    ostream &SaveObject(ostream &os) override {
        os << name << setw(10) << price << setw(10);
        MovementToOut(os, movementType);
        os << setw(10);
        DirectionsToOut(os, movementDirection);
        return os;
    }

    static ostream &Heading(ostream &os) {
        return os << "NAME" << setw(10) << "PRICE" << setw(10) << "MOVEMENT" << setw(10)
                  << "DIRECTION" << endl;
    }


};


