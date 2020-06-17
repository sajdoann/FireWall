/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/13/2020
*/

#include <cstring>
#include "Reader.h"




Reader::Reader(const string &filename) : filename(filename) {
    in.open(filename);
    if (!in) {
        string filNotFound = filename;
        filNotFound += ERR_FILE_NOT_FOUND;
        throw runtime_error(filNotFound);

    }
}

map<Coords, char> Reader::ReadBoard(int &mx, int &my) {
    map<Coords, char> coords;

    mx = my = -1;
    in >> mx >> my;
    if (mx < MIN_BOARD_MEASURE || my < MIN_BOARD_MEASURE || mx > MAX_BOARD_MEASURE || my > MAX_BOARD_MEASURE ||
        !(in.good()))
        throw invalid_argument(ERR_BOARD_MEASURES);

    int x, y;
    char br1, br2, sep;
    char c;
    while (in >> br1 >> x >> sep >> y >> br2 >> c) {
        if (br1 != '(' || sep != ',' || br2 != ')')
            throw invalid_argument(ERR_BOARD_INPUT_FORMAT);

        Coords coord(x, y);

        if (coord.X() >= mx || coord.Y() >= my || coord.X() < 0 || coord.Y() < 0)
            throw invalid_argument(coord.toStr().append(ERR_BOARD_COORDS_OUT));

        if (coords.find(coord) == coords.end()) {
            if (isalpha(c)) c = toupper(c);
            coords.insert({coord, c});
            continue;
        }
        throw invalid_argument(coord.toStr().append(ERR_BOARDS_COORDS_DUPLICATE));
    }

    if (!in.eof())
        EofError();
    return coords;
}

void Reader::EofError() {
    string str = ERR_WRONG_FILE_FORMAT;
    str += filename;
    throw invalid_argument(str);
}
