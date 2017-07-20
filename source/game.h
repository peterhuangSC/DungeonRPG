#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "player.h"

class Object;
/////////////////////////////////////////////////////////////////

//Cell Class
class Cell{
    char Type;
    int room;
    Object *onCell;
    std::vector<Cell*> Observers;

    public:
    Cell();
    ~Cell();

    //Puts an object on Cell if empty
    bool setonCell(Object &o);

    char getType() const;
    int  getRoom() const;

    //Notify surrounding cells when something enters this Cell
    void notifyAll() const;

    //When notified, call notify of object in this cell
    void notify(Object *who);

friend class Floor; // So floors can set type (can make setter)
};
/////////////////////////////////////////////////////////////////

//Room Class, mostly for RNG purposes
class Room{
    int free;
    std::vector<Cell*> freeCells;
    public:
    int getFree() const;
    int addFree(Cell *c);
    void removeFree(int i);
};
/////////////////////////////////////////////////////////////////

//Floor Class, stores this floor
class Floor {
    std::vector<Room> rooms;
    std::vector<std::vector<Cell>> ground;
    public:
    Floor(int dimx, int dimy);

    char Cellstr(int y,int x) const;
    void addCell(int y,int x,char c);
};
/////////////////////////////////////////////////////////////////

//Information, for storing floor information
struct Info{
    *Player player;
    int level;
    int dimx, dimy;
    public:
    Info(int dimx, int dimy, *Player);
    void levelUp();

    friend std::ostream &operator<<(std::ostream &out, const Info info);
};

std::ostream &operator<<(std::ostream &out, const Info info);
/////////////////////////////////////////////////////////////////

//Map// Stores an instance of the game
class Map{
    //The Layout
    int dimx,dimy,level;
    std::vector<Floor> Maps;

    //The Player
    //Player player;

    //Information
    Info info;

    public:
    char Cellstr(int y, int x) const;

    //Create all floors of map
    Map(int dimx, int dimy,std::string filename);

    friend std::ostream &operator<<(std::ostream &out, const Map floor);
};

std::ostream &operator<<(std::ostream &out, const Map floor);
/////////////////////////////////////////////////////////////////
#endif