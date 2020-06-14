/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include "Coords.h"
class Board;

using namespace std;

/**
 * abstract object is a parent class that roofs all objects in game
 * object has its name
 *
 */
class Object {
protected:
    char name = 'a';
public:
    Object(char name) : name(name) {}

    Object() = default;

    virtual ~Object() = default;

    virtual Object *Clone() const = 0;


    /**
     * saves object into stream for storing
     * @param out - output stream
     * @return out stream
     */
    virtual ostream &SaveObject(ostream &out) = 0;

    /**
     * class to load objects from stream in
     * @param in - stream
     * @return in stream
     */
    virtual istream &LoadObject(istream &in) = 0;

    /** prints name of object */
    char Name() {
        return name;
    }

    /**
     * says what to do when object needs to attack - that means shoot hotfix or move
     * @param newBoard - board that constains objects that already moved/attacked
     * @param oldBoard - pre move board, contains last move
     * @param startCoords - coords of object before move
     * @return virus points that were gained during this move
     */
    virtual int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) = 0;


    /** prints object for user */
    virtual ostream &PrintInfo(ostream &out) const = 0;

    /** returns true if object is a moving object */
    virtual bool isMovingObject() const = 0;

    /** returns true if object is empty */
    virtual bool isEmpty() const = 0;

    /** returns true if object is virus */
    virtual bool isVirus() const = 0;

    /** returns true if object is a patch */
    virtual bool isPatch() const = 0;


    //friend std::ostream &operator<<(std::ostream &out, Object *object);

    friend std::istream &operator>>(std::istream &in, Object *object) {
        object->LoadObject(in);
        return in;
    }


};

