/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/22/2020
*/

#include "BfsStrategy.h"
#include <queue>
#include <algorithm>
#include "../Board/Board.h"

using namespace std;

bool BfsStrategy::Bfs(Board *board, Coords start, Coords &dest, std::map<Coords, Coords> &pred) {
    queue<Coords> q;
    vector<Coords> visited;


    q.push(start);
    visited.push_back(start);
    pred.insert({start, Coords(-1, -1)});

    while (!q.empty()) {
        Coords c = q.front();
        q.pop();
        auto neighbours = c.getNeighbours(board);

        for (auto neighbour : neighbours) {
            auto f = find(visited.begin(), visited.end(), neighbour);

            //yet not processed
            if (f == visited.end()) {
                q.push(neighbour);
                visited.push_back(neighbour);

                if (!pred.count(neighbour))
                    pred.insert({neighbour, c});
                else
                    pred.at(neighbour) = c;

                //end condition (route found)
                if (neighbour.Y() == 0) {
                    dest = neighbour;
                    return true;
                }
            }
        }
    }
    return false;
}

void BfsStrategy::setPath(map<Coords, Coords> &pred) {
    if (!pathExists) return;
    Coords itr = destination;
    while (itr != pred.at(start)) {
        path.push_back(itr);
        itr = pred.at(itr);
    }

}

Coords *BfsStrategy::getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) {
    {
        if (findPath) {
            start = startCoords;
            findPath = false;
            std::map<Coords, Coords> pred;
            pathExists = Bfs(&newBoard, startCoords, destination, pred);
            setPath(pred);

            //printRoute(newBoard);

        }

        //no next coord was found
        if (path.empty()) {
            if (!pathExists)
                return new Coords(startCoords.X(), startCoords.Y() - 1);
            else return new Coords(-1, -1);
        }


        Coords *c = new Coords(path[path.size() - 1]);
        path.erase(path.end());
        return c;
    }
}

void BfsStrategy::printRoute(Board &newBoard) {
    cout << "\n @ route: \n";
    for (int i = 0; i < newBoard.MaxX(); ++i) {
        for (int j = 0; j < newBoard.MaxY(); ++j) {
            if (find(path.begin(), path.end(), Coords(i, j)) == path.end())
                cout << "-";
            else cout << "@";
        }
        cout << endl;
    }
    cout << endl;
}
