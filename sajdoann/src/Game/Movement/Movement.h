/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "../Board/Board.h"
#include "../../Interface.h"

/**
 * class for movement of the moving objects on the board
 */
class Movement {
    Board *board;
    Interface interface;

public:
    Movement(Board *board) : board(board), interface(cin, cout){}

    ~Movement() {}

    //game gives order and the entire board moves
    // first vawe are moving objects then patches
    void MoveAll() {
        Board newBoard(board->MaxX(), board->MaxY());
        newBoard.AddAllPatches(board);

        //moving objects loop
        for (int i = board->MaxX() - 1; i >= 0; --i) {
            for (int j = board->MaxY() - 1; j >= 0; --j) {
                Object *object = (*board)(i, j);
                Coords coords(i, j);
                object->Attack(board, newBoard, coords);
            }
        }

        *board = newBoard;
        interface.PrintBoardAttack(*board);
        //this_thread::sleep_for(1s);
    }

};

