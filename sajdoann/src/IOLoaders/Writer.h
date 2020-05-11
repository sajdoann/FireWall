/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include <iomanip>

using namespace std;

class Writer {
protected:
    ostream os;

public:
    //writes the data to file
    bool writeToFile(ostringstream input);

};

