/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/13/2020
*/

#include "Reader.h"

void Reader::check_eof(bool endsWithEof) {
    if (endsWithEof)
        return;

    string str = "Error loading input from this file: " + filename + " wrong file format.";
    throw invalid_argument(str);

}

Reader::Reader(const string &filename) : filename(filename) {
    in.open(filename);
    if (!in)
        throw runtime_error(filename + " not found");
}
