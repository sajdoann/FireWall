/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "StraightStrategy.h"
#include "../Board/Board.h"

bool StraightStrategy::Move(Board *board, const Coords &startCoords) {
      Coords targetCoords(startCoords.X(), startCoords.Y() + 1);

      Object * o = board->At(targetCoords);
      if(o->isEmpty()){
          board->InsertObject(*((Hotfix *) board->At(startCoords)), targetCoords);
          board->setEmpty(startCoords);
      }
}
