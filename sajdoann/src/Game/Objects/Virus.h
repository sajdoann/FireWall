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
    int lives;


public:
    Virus() {

    }

    Virus(char name, int lives, MovementType movementType, MovementDirection movementDirection)
            : MovingObject(name, movementType, movementDirection), lives(lives) {
    }


    ~Virus() override {
        delete strategy;
    }

    virtual Object *Clone() const {
        return new Virus(*this);
    }

    Virus(const Virus &other) {
        *this = other;
    }

    Virus &operator=(const Virus &other) {
        if (this == &other) return *this;
        if (strategy != nullptr) delete strategy;
        name = other.name;
        lives = other.lives;
        movementType = other.movementType;
        movementDirection = other.movementDirection;
        strategy = other.strategy->Clone();
        return *this;
    }

    virtual int Attack(Board *oldBoard, Board &newBoard, Coords startCoords) override;


    int Lives() { return lives; }

    bool isVirus() const { return true; };

    ostream &SaveObject(ostream &out) override;

    istream &LoadObject(istream &in) {
        return in >> *this;
    }

    ostream &PrintInfo(ostream &out) const override {
        out << "virus: " << name << " lives: " << lives << " movement: ";
        MovementToOut(out, movementType);
        out << " directions: ";
        DirectionsToOut(out, movementDirection);
        return out << endl;
    }


    friend ostream &operator<<(ostream &out, const Virus &virus) {
        out << virus.name << " " << virus.lives << " ";
        virus.MovementToOut(out, virus.movementType);
        out << " ";
        virus.DirectionsToOut(out, virus.movementDirection);
        return out;
    }

    friend istream &operator>>(istream &in, Virus &v) {
        in >> v.name;
        if (in.eof())
            return in;
        in >> v.lives;
        v.MovementFromIn(in, v.movementType);
        v.DirectionFromIn(in, v.movementDirection);
        v.setStrategy();
        return in;

    }

    bool Hitted() {
        if (lives) {
            --lives;
            return true;
        }
        return false;
    }

    void Destroy() {
        delete this;

    }

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

