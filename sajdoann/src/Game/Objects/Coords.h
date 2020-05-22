/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once
#include <string>
#include <vector>
class Board;

class Coords {
    int x = 0;
    int y = 0;
public:
    Coords() = default;

    Coords(int x, int y) : x(x), y(y) {}

    Coords(const Coords &other) {
        *this = other;
    }

    ~Coords() = default;

    Coords &operator=(const Coords &other) {
        if (this == &other) return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

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

    friend int operator!=(const Coords &a, const Coords &b) {
        return !(a == b);
    }

    bool operator<(const Coords &b) const {
        return (x < b.x) || ((x == b.x) && (y < b.y));
    }

    struct cmp {
        bool operator()(const Coords &a, const Coords &b) {
            return a < b;
        }
    };

    std::vector<Coords> getNeighbours(Board *board);

    bool canStep(Board *b) const;

};

