/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <iomanip>
#include "ObjectWithMoveAttributes.h"
#include "Hotfix.h"
class Board;

using namespace std;

/**
 * patch is an Object that has name, type, price and range
 * In the FireWall game it can be placed on Board
 * It shoots hotfixes
 */
class Patch : public ObjectWithMoveAttributes {
protected:
    int price = 10;

public:
    Patch() noexcept = default;

    Patch(char name, int price, MovementType movementType, MovementDirection movementDirection) noexcept
            : ObjectWithMoveAttributes(name, movementType, movementDirection), price(price) {}

    ~Patch() override = default;

    virtual Object *Clone() const { return new Patch(name, price, movementType, movementDirection); }


    Patch(Patch &patch);


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

    /** returns false because patch is not empty object */
    bool isEmpty() const { return false; }

    /** returns false because patch is not a virus*/
    virtual bool isVirus() const { return false; };

    /** returns true because it is a patch*/
    virtual bool isPatch() const { return true; };

    /** returns true if patch can shoot, if movement none -> false */
    virtual bool canShoot() const { return movementType != MovementType::NONE; }

    /** if can shoot it shoots hotfix and places it on board if strategy exec move conditions are met (it can be placed there) */
    int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) override;

    Hotfix ShootHotfix() {
        return Hotfix('*', movementType, movementDirection);
    }

    /** less comparator for patch by its name*/
    /* int operator<(const Patch &patch) const {
         if (name != patch.name)
             return (name < patch.name) ? -1 : 1;
         return 0;
     }*/

    /** compare function by name */
    /*struct cmp {
        int operator()(const Patch &a, const Patch &b) {
            return a < b;
        }
    };*/

    /** gets patch atributes from istream */
    friend istream &operator>>(istream &in, Patch &patch) {
        char n;
        in >> n;
        if (in.eof())
            return in;

        if (!isalpha(n)) {
            in.setstate(iostream::failbit);
            return in;
        }
        patch.name = toupper(n);

        int pr;
        in >> pr;
        if (pr < 0 || pr > 150) {
            in.setstate(iostream::failbit);
            return in;
        }
        patch.price = pr;

        patch.MovementFromIn(in, patch.movementType);
        if (!in.good())
            return in;

        if (patch.movementType == NONE) return in;
        patch.DirectionFromIn(in, patch.movementDirection);
        return in;
    }


    istream &LoadObject(istream &is) override {
        is >> *this;
        return is;
    }

    /** prints all available information for patches */
    ostream &PrintInfo(ostream &out) const override {
        out << "patch: " << name << " price: " << price << " movement: ";
        MovementToOut(out, movementType);

        if (movementType == MovementType::NONE) return out << endl;

        out << " direction: ";
        DirectionsToOut(out, movementDirection);
        return out << endl;
    }


    /** prints just the name representation of object */
    ostream &SaveObject(ostream &os) override {
        os << name << setw(15) << price << setw(15);
        MovementToOut(os, movementType);
        os << setw(15);

        if (movementType == MovementType::NONE) return os << endl;
        DirectionsToOut(os, movementDirection);
        return os;
    }

    static ostream &Heading(ostream &os) {
        return os << "NAME" << setw(15) << "PRICE" << setw(15) << "MOVEMENT" << setw(15)
                  << "DIRECTION" << endl;
    }


};



