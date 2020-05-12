/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/5/2020
*/

#pragma once

#include "MovingObject.h"

class Virus : public MovingObject {
    int lives;
    int difficulty = 0;

    void setDifficulty() {
        //TODO: imlement this
        //if(type == 'C')
    }

public:
    Virus() noexcept = default;

    Virus(char name, int lives, MovementType movementType, MovementDirection movementDirection)
            : MovingObject(name, movementType, movementDirection), lives(lives) {

        setDifficulty();
    }


    ~Virus() override = default;

    char Name() { return name; }

    int Lives() { return lives; }

    bool isVirus() const { return true; };

    ostream &SaveObject(ostream &out) override {
        out << name << " " << lives << " ";
        MovementToOut(out, movementType);
        out << " ";
        DirectionsToOut(out, movementDirection);
        return out;
    }

    istream &LoadObject(istream &in) {
        in >> *this;
    }

    ostream &PrintInfo(ostream &out) const override {
        return out << *this;
    }


    friend ostream &operator<<(ostream &out, const Virus &virus) {
        out << virus.name << " " << virus.lives;
        virus.MovementToOut(out, virus.movementType);
        virus.DirectionsToOut(out, virus.movementDirection);


    }

    friend istream &operator>>(istream &in, Virus &v) {
        in >> v.name;
        if (in.eof())
            return in;
        in >> v.lives;
        v.MovementFromIn(in, v.movementType);
        v.DirectionFromIn(in, v.movementDirection);
        return in;

    }

    void Hitted() {
        if (lives) --lives;
        else Destroy();
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


};

