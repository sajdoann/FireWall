/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <string>
#include <vector>

class Board;    //foward declaration because of includes would otherwise not function

/**
 * class for coordination remembers x and y coords
 */
class Coords {
    int x = 0;
    int y = 0;
public:
    Coords() = default;

    Coords(int x, int y) : x(x), y(y) {}

    Coords(const Coords &other) { *this = other; }

    ~Coords() = default;

    Coords &operator=(const Coords &other);

    /** gets x*/
    int X() const { return x; }

    /** gets y */
    int Y() const { return y; }

    /** sets coords */
    void setCoords(int x, int y) {
        this->x = x;
        this->y = y;
    }

    std::string toStr() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }

    friend int operator==(const Coords &a, const Coords &b) { return a.x == b.x && a.y == b.y; }

    friend int operator!=(const Coords &a, const Coords &b) { return !(a == b); }

    bool operator<(const Coords &b) const { return (x < b.x) || ((x == b.x) && (y < b.y)); }

    /*struct cmp {
        bool operator()(const Coords &a, const Coords &b) {
            return a < b;
        }
    };*/

    /** gets all coords of tiles in one distance
     * @param b - board
     * */
    std::vector<Coords> getNeighbours(Board *b);

    /**
     * says if this coords are on board
     * @param b - board
     * @return true if this coord is on board
     */
    bool isOnBoard(Board *b) const;

};

