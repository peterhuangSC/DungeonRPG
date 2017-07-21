#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "player.h"
#include "PlayerGenerator.h"

class Object;
/////////////////////////////////////////////////////////////////

//Cell Class
class Cell{
    char Type;
    int room;
    std::shared_ptr<Object> onCell;
    std::vector<Cell*> Observers;

    public:
    Cell();
    ~Cell();

    //Puts an object on Cell if empty
    bool setonCell(std::shared_ptr<Object> o);

    //Getters
    char getType() const;
    int  getRoom() const;

    //Notify surrounding cells when something enters this Cell
    void notifyAll() const;

    //When notified, call notify of object in this cell
    void notify(std::shared_ptr<Object> who);

friend class Floor; // So floors can set type (can make setter)
};
/////////////////////////////////////////////////////////////////

//Room Class, mostly for RNG purposes
class Room{
    int free = 0;
    std::vector<Cell*> freeCells;
    public:
    int getFree() const;
    int addFree(Cell *c);
    Cell *removeFree();
};
/////////////////////////////////////////////////////////////////

//Floor Class, stores this floor
class Floor {
    std::vector<Room> rooms;
    std::vector<std::vector<Cell>> ground;
    public:
    Floor(int dimx, int dimy);

    int getx();
    int gety();

    void init(std::shared_ptr<Object> player);
    char Cellstr(int y,int x) const;
    void addCell(int y,int x,char c);

    int move(std::string dir, int y, int x);
};
/////////////////////////////////////////////////////////////////

//Information, for storing floor information
struct Info{
    int dimy;
    std::shared_ptr<Object> player;
    int level;
    Info(int dimy);
    int getx();
    int gety();
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
    std::shared_ptr<Object> player;
    int x,y;
    void getx();
    void gety();

    //Information
    Info info;

    //Initialize the current level;
    void init_Level();

    public:
    //Create all floors of map
    Map(int dimx, int dimy, std::string filename, std::string race);

    char Cellstr(int y, int x) const;

    //Movement
    void move(std::string dir);

    friend std::ostream &operator<<(std::ostream &out, const Map floor);

};

std::ostream &operator<<(std::ostream &out, const Map floor);
/////////////////////////////////////////////////////////////////
#endif