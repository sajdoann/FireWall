#include <iostream>
#include "App.h"

int main() {
    //printf("\u001b[31mHELLO!\n", 0x1B, 32);
    const char * text = "HELLOOO\n";
    //cout << "\u001b[31m" << text << endl;

    App().Run();
    return 0;
}
