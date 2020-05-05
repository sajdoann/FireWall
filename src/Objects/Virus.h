/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/5/2020
*/

#pragma once

class Virus {
    char name;
    char type;  //C-clever, L - left (moves just stright left if sees patch/wall goes up then left)
    int lives;
    int radius;
public:
    Virus() = default;
    Virus(char name, char type, int lives, int radius) : name(name), type(type), lives(lives), radius(radius){}

    char Name(){ return name; }
    int Lives(){return lives; }

    void Hitted(){
        if(lives) --lives;
        else Destroy();
    }

    void Destroy(){
        delete this;
    }

};

