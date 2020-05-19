/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once
#include <string>
class Board;

class Coords {
    int x = 0;
    int y = 0;
public:
    Coords() = default;

    Coords(int x, int y) : x(x), y(y) {}

    ~Coords() = default;

    int X() const { return x; }

    int Y() const { return y; }

    void setCoords(int x, int y) {
        this->x = x;
        this->y = y;
    }

    std::string toStr() const { return std::to_string(x) + ", " + std::to_string(y); }

    friend int operator==(const Coords &a, const Coords &b) {
        return a.x == b.x && a.y == b.y;
    }

    int operator<(const Coords &b) const {
        if (*this == b) return 0;

        if (x != b.x)
            return (x < b.x) ? 1 : -1;
        else return (y < b.y) ? 1 : -1;
    }

    struct cmp {
        int operator()(const Coords &a, const Coords &b) {
            return a < b;
        }
    };


    bool canStep(Board *b);

};

