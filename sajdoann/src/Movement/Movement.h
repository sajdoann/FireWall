/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "../Board/Board.h"
/**
 * class for movement of the moving objects on the board
 */
class Movement {
    Board * board;
public:
    Movement(Board * board) : board(board){};
    ~Movement(){};

    //game gives order and the entire board moves
    void MoveAll(){};

};

