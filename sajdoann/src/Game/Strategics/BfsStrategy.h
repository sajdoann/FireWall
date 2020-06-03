/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/22/2020
*/

#pragma once


#include "Strategy.h"
#include <vector>
#include <map>


class BfsStrategy : public Strategy {
    std::vector<Coords> path;
    bool pathExists;
    Coords start;
    Coords destination;
    bool findPath = true;

    bool Bfs(Board *board, Coords start, Coords &dest, std::map<Coords, Coords> &pred);

    void setPath(std::map<Coords, Coords> &pred);

public:

    BfsStrategy(MovementDirection movementDirection) : Strategy(movementDirection) {}

    BfsStrategy(MovementDirection movementDirection, std::vector<Coords> path, bool pathExists, Coords start,
                Coords destination, bool findPath)
            : Strategy(movementDirection), path(path), pathExists(pathExists), start(start), destination(destination),
              findPath(findPath) {}

    Strategy *Clone() const {
        return new BfsStrategy(movementDirection, path, pathExists, start, destination, findPath);
    }

    Coords *getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords);

    void printRoute(Board &newBoard);
};



