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
    void MoveAll() {
        Board newBoard(*board);


        //!!!!!!!! TODO: do it with attack from object emit hotfixes
        for (int i = 0; i < board->MaxX(); ++i) {
            for (int j = 0; j < board->MaxY(); ++j) {
                Object * object = (*board)(i,j);
                Coords coords(i,j);

                //object->Attack(board, coords);

                //empty object is not moving
                if(object->isEmpty())
                    continue;

                //patch condition
                if(!object->isMovingObject() && !object->isEmpty()){
                    if(board->OutOfBoard(Coords{i+1,j})){ continue;}

                    Object * nextObject = (*board)(i +1,j);
                    //if next tile is empty and on board
                    if(nextObject->isEmpty() && !board->OutOfBoard(Coords({i+1,j}))){
                        Patch * patch = (Patch *)(*board)(i ,j);
                        Hotfix * hotfix = patch->ShootHotfix();
                        Patch p(*patch);
                        newBoard.InsertPatch(p,Coords({i+1,j}));
                        newBoard.setEmpty(Coords(i,j));
                        //swap(object, nextObject);*/
                    }
                }

            }
        }
        *board = newBoard;
        interface.PrintBoardAttack(*board);
        //this_thread::sleep_for(1s);
    }

};

