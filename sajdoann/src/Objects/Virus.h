/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/5/2020
*/

#pragma once

class Virus : public Object{
    char name;
    char type;  //C-clever, L - left (moves just stright left if sees patch/wall goes up then left)
    int lives;
    int radius;
public:
    Virus() = default;
    Virus(char name, char type, int lives, int radius) : name(name), type(type), lives(lives), radius(radius){}
    ~Virus() override = default;

    char Name(){ return name; }
    int Lives(){return lives; }

    ostream &PrintObject(ostream &os) override {
        return os << name ;
    }

    ostream & PrintInfo(ostream & os) override {
        return os << *this;
    }


    friend ostream & operator << (ostream & os, const Virus & virus){
       return os << virus.name << " " << virus.type << " " << virus.lives << " " << virus.radius;
    }

    friend istream & operator >> (istream & ifs, Virus & virus) {
        return ifs >> virus.name >> virus.type >> virus.lives >> virus.radius;
    }

    void Hitted(){
        if(lives) --lives;
        else Destroy();
    }

    void Destroy(){
        delete this;
    }

};

