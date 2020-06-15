/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/13/2020
*/

#include "Reader.h"




Reader::Reader(const string &filename) : filename(filename) {
    in.open(filename);
    if (!in)
        throw runtime_error(filename + " not found");
}

map<Coords, char> Reader::ReadBoard(int &mx, int &my) {
    map<Coords, char> coords;

    mx = my = -1;
    in >> mx >> my;
    if (mx < MIN_BOARD_MEASURE || my < MIN_BOARD_MEASURE || mx > MAX_BOARD_MEASURE || my > MAX_BOARD_MEASURE ||
        !(in.good()))
        throw invalid_argument(
                "Board does not fit max/min specifications.");

    int x, y;
    char br1, br2, sep;
    char c;
    while (in >> br1 >> x >> sep >> y >> br2 >> c) {
        if (br1 != '(' || sep != ',' || br2 != ')')
            throw invalid_argument("Wrong format in board input.");

        Coords coord(x, y);

        if (coord.X() >= mx || coord.Y() >= my || coord.X() < 0 || coord.Y() < 0)
            throw invalid_argument("Coords " + coord.toStr() + " are out of board.");

        if (coords.find(coord) == coords.end()) {
            if (isalpha(c)) c = toupper(c);
            coords.insert({coord, c});
            continue;
        }
        throw invalid_argument("Coordinations " + coord.toStr() + " already taken on this board.");
    }

    if (!in.eof())
        EofError();
    return coords;
}

void Reader::EofError() {
    string str = "Error loading input from this file: " + filename + " wrong file format.";
    throw invalid_argument(str);
}
