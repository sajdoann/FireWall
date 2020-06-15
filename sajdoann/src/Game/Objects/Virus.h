/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/5/2020
*/

#pragma once

#include <iomanip>
#include "MovingObject.h"
/**
 * an object that tries to get from right side of board to left
 * it remembers its lives
 */
class Virus : public MovingObject {
    int lives = 5;


public:
    Virus() = default;

    Virus(char name, int lives, MovementType movementType, MovementDirection movementDirection)
            : MovingObject(name, movementType, movementDirection), lives(lives) {
    }

    ~Virus() override {
        if (strategy != nullptr) delete strategy;
    }

    virtual Object *Clone() const override { return new Virus(*this); }

    Virus(const Virus &other) { *this = other; }

    Virus &operator=(const Virus &other);

    virtual int Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override;


    int Lives() { return lives; }

    bool isVirus() const { return true; };

    ostream &SaveObject(ostream &out) override;

    istream &LoadObject(istream &in) {
        return in >> *this;
    }

    ostream &PrintInfo(ostream &out) const override;


    friend ostream &operator<<(ostream &out, const Virus &virus);

    friend istream &operator>>(istream &in, Virus &v);

    /**
     * takes live
     * @return if not enough lives to take one returns false
     */
    bool Hitted();

    /** less comparator for virus by its name*/
    int operator<(const Virus &virus) const {
        if (name != virus.name)
            return (name < virus.name) ? -1 : 1;
        return 0;
    }

    /** compare function by name */
    struct cmp {
        int operator()(const Virus &a, const Virus &b) {
            return a < b;
        }
    };

    static ostream &Heading(ostream &os) {
        return os << "NAME" << setw(10) << "LIVES" << setw(10) << "MOVEMENT"
                  << setw(10) << "DIRECTION" << endl;
    }

};

