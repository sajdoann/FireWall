/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/10/2020
*/

#include "Board.h"

Board::Board(Board &other) {
    *this = other;
}

//TODO: REMOVE
void Board::Print() {
    for (int k = 0; k < MaxX(); ++k) {
        for (int j = 0; j < MaxY(); ++j) {
            cout << At(Coords(k, j)) << " ";
        }
        cout << endl;
    }
}
