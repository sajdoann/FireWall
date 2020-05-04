/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/4/2020
*/

#pragma once

#include <vector>
#include <iostream>
#include "../Objects/Object.h"
#include "../Objects/Empty.h"
#include "../Objects/Patch.h"

using namespace std;
class Board {
 int max_X;
 int max_Y;
 vector<vector< Object *>> tiles;

public:
    Board(int max_X, int max_Y) : max_X(++max_X), max_Y(++max_Y){
        for (int i = 0; i < max_X; ++i) {
            vector<Object *> temp;
            for (int j = 0; j <max_Y ; ++j) {
                temp.push_back(new Empty());
            }
            tiles.push_back(temp);
        }
    }

    ~Board(){
        for (int i = 0; i < max_X; ++i) {
            for (int j = 0; j < max_Y; ++j) {
                delete tiles[i][j];
            }
        }
    }

    bool OutOfBoard(const Coords & coords ){
        return coords.X() > max_X || coords.X() < 0 || coords.Y() > max_Y || coords.Y() < 0;
    }

    bool InsertPatch(Patch * patch, const Coords & coords){
        if(OutOfBoard(coords)) return false;
        delete tiles[coords.X()][coords.Y()];
        tiles[coords.X()][coords.Y()] = patch;
    }

    void Print(){
        for (int i = 0; i < max_X; ++i) {
            for (int j = 0; j < max_Y; ++j) {
                cout << tiles[i][j];
            }
            cout << endl;
        }
    }


};

