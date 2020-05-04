/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

class Coords {
    int x=0;
    int y=0;
public:
    Coords() = default;
    ~Coords() = default;
    int X() const {return x;}
    int Y() const {return y;}
    void setCoords(int x, int y){
        this->x = x;
        this->y = y;
    }
};

