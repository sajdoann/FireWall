/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/15/2020
*/

#include "Movement.h"

int Movement::MoveAll() {
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
