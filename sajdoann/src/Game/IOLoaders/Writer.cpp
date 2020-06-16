/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/15/2020
*/

#include "Writer.h"
#include "../Board/Board.h"

void Writer::writeBoard(Board &b) {
    out << b.MaxX() << " " << b.MaxY() << endl;
    for (int i = 0; i < b.MaxX(); ++i) {
        for (int j = 0; j < b.MaxY(); ++j) {
            Coords act(i, j);
            if (!b.At(act)->isEmpty()) {
                out << act.toStr() << " " << b.At(act)->Name() << endl;
            }
        }
    }
    out << endl;
}

void Writer::writeCounter(const Counter &c) {
    out << c.Ram() << " " << c.RamStart() << " " << c.Level() << " " << c.Money() << endl;
}

Writer::Writer(string filename) : filename(filename) {
    out.open(filename);
    if (!out)
        throw runtime_error("filename:" + filename + "not found");
}
