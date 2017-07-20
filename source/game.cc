#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "game.h"
using namespace std;
/////////////////////////////////////////////////////////////////

//Cell Class//

Cell::Cell(): Type{' '}, room{0}, onCell{nullptr} {};
Cell::~Cell()= default;

    //Puts an object on Cell if empty
bool Cell::setonCell(Object &o){
    if(onCell) return false;
    else{
        onCell = &o;
        this->notifyAll();
        return true;
    }
};

char Cell::getType() const{return Type;};
int  Cell::getRoom() const{return room;};

    //Notify surrounding cells when something enters this Cell
void Cell::notifyAll() const{
    for(auto ob : Observers){
        ob->notify(onCell);
    };
};

    //When notified, call notify of object in this cell
void Cell::notify(Object *who){
    //if(onCell) onCell->notify(who); *Code Here*
};
/////////////////////////////////////////////////////////////////

//Room Class// mostly for RNG purposes
int Room::getFree() const{return free;};
int Room::addFree(Cell *c){
    freeCells.push_back(c);
    return ++free;
};
void Room::removeFree(int i){};
/////////////////////////////////////////////////////////////////

//Floor Class// stores this floor

Floor::Floor(int dimx, int dimy){
    ground.assign(dimy,vector<Cell>(dimx,Cell()));
};
char Floor::Cellstr(int y,int x) const{
    return ground[y][x].getType();
};
void Floor::addCell(int y,int x,char c){
    ground[y][x].Type = c;
};
/////////////////////////////////////////////////////////////////

//Info Class// stores Maps information
Info::Info(int x, int y,Player *player): dimx{x} dimy{y}, player{player}, level{1} {};

void Info::levelUp(){++level;};

ostream &operator<<(ostream &out, const Info info){
    out << "Race: " << info.player->getHeroType() << " Gold: " << 0;
    
    return out;
};
/////////////////////////////////////////////////////////////////

//Map class// Stores an instance of the game
char Map::Cellstr(int y, int x) const{
    return Maps[level].Cellstr(y,x);
};

    //Create all floors of map
Map::Map(int dimx, int dimy,string filename): dimx{dimx}, dimy{dimy}, level{1} {
    Maps.assign(5,Floor(dimx,dimy));
    ifstream file (filename);
    string line;
    for(int i = 0; i < 5; ++i){
        for(int y = 0; y < dimy; ++y){
            getline(file, line);
            for(int x = 0; x < dimx; ++x){
                char c = line[x];
                Maps[i].addCell(y,x,c);
            }
            cout << endl;
        }
    }
};

//Outputs current floor of Map
ostream &operator<<(ostream &out, const Map floor){
    int dimx = floor.dimx;
    int dimy = floor.dimy;
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            out << floor.Cellstr(y,x);
        }
        out << endl;
    }
    //out << floor.info;
    return out;
};