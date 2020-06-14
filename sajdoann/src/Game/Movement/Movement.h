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
    Movement(Board *board) : board(board), interface(cin, cout) {}

    ~Movement() {}


    /**
     * moves all objects on the board by one step
     * creates new board, adds all patches, interates and adds all objects on moved(target) position
     * assigns board new board
     * @return how many viruses broke through the wall
     */
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
        return virusPoints;
    }

};
