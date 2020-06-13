/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include <thread>
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
    int MoveAll() {
        Board newBoard(board->MaxX(), board->MaxY());
        newBoard.AddAllPatches(board);

        int virusPoints = 0;
        for (int i = 0; i < board->MaxX(); ++i) {
            for (int j = 0; j < board->MaxY(); ++j) {
                Object *object = (*board)(i, j);
                Coords coords(i, j);
                virusPoints += object->Attack(board, newBoard, coords);
            }
        }

        *board = newBoard;
        //interface.PrintBoardAttack(*board);
        // interface.PrintBoard(*board);
        return virusPoints;
    }

};
