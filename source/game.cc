#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "game.h"
#include "PlayerGenerator.h"
using namespace std;

//Hard Coded Rooms 
static int ur1 = 3;  static int uc1 = 3;  static int lr1 = 8;  static int lc1 = 30;// Room 1
static int ur2 = 3;  static int uc2 = 39; static int lr2 = 8;  static int lc2 = 63;// Room 2
static int ur3 = 5;  static int uc3 = 61; static int lr3 = 14; static int lc3 = 77;// Room 2 (aswell)
static int ur4 = 16; static int uc4 = 37; static int lr4 = 23; static int lc4 = 77;// Room 3
static int ur5 = 15; static int uc5 = 5;  static int lr5 = 23; static int lc5 = 26;// Room 4
static int ur6 = 10; static int uc6 = 38; static int lr6 = 14; static int lc6 = 51;// Room 5

int whatRoom(int y, int x, char c){
    if(char == '.'){
        if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1))      return 1;
        else if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1)) return 2;
        else if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1)) return 3;
        else if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1)) return 4;
        else if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1)) return 5;
        else return 0;
    }
    else return 0;
}

/////////////////////////////////////////////////////////////////

//Cell Class//

Cell::Cell(): Type{' '}, room{0}, onCell{nullptr} {};
Cell::~Cell()= default;

    //Puts an object on Cell if empty
bool Cell::setonCell(shared_ptr<Object> o){
    if(onCell) return false;
    else{
        onCell = o;
        this->notifyAll();
        return true;
    }
};

    //Getters
char Cell::getType() const{
    if(onCell) return onCell->getType();
    else return Type;
};
int  Cell::getRoom() const{return room;};

    //Notify surrounding cells when something enters this Cell
void Cell::notifyAll() const{
    for(auto ob : Observers){
        ob->notify(onCell);
    };
};

    //When notified, call notify of object in this cell
void Cell::notify(shared_ptr<Object> who){
    if(onCell) onCell->notify(who);
};
/////////////////////////////////////////////////////////////////

//Room Class// mostly for RNG purposes


int Room::getFree() const{return free;};
int Room::addFree(Cell *c){
    freeCells.push_back(c);
    return ++free;
};
    //Pick a random open cell in the room, remove it from opencells and return it
Cell *Room::removeFree(){
    int r = rand() % free;
    Cell *cell = freeCells[r];// Could use shared pointers
    freeCells.erase(r);
    return cell;
};
/////////////////////////////////////////////////////////////////

//Floor Class// stores this floor

Floor::Floor(int dimx, int dimy){
    ground.assign(dimy,vector<Cell>(dimx,Cell()));
    rooms.assign(6, Room());
};
char Floor::Cellstr(int y,int x) const{
    return ground[y][x].getType();
};
void Floor::addCell(int y,int x,char c){
    ground[y][x].Type = c;
    ground[y][x].Room = whatRoom(y,x,c);
    rooms[ground[y][x].Room.addFree(&ground[y][x])];
};


int Floor::getx(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if ground[y][x].getType() == '@' return x;
        }
    }
};


int Floor::gety(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if ground[y][x].getType() == '@' return y;
        }
    }
};

void Floor::init(shared_ptr<Object> player){
    int r = rand() % 5;
    Cell *me = rooms[r+1].removeFree();
    me->setonCell(player);
    int noLadder = me->getRoom();
};

/////////////////////////////////////////////////////////////////

//Info Class// stores Maps information
Info::Info(int dimy, shared_ptr<Object> player): dimy{dimy}, player{player}, level{1} {};

void Info::levelUp(){++level;};

ostream &operator<<(ostream &out, const Info info){
    string race = "Shade";
    string line(56 - race.length(),' ');
    out << "Race: " << race << " Gold: " << 0;
    out << line << "Floor: " << info.level << endl;
    out << "HP:  " << 0 << endl;
    out << "Atk: " << 0 << endl;
    out << "Def: " << 0 << endl;
    out << "Action: " << endl;
    return out;
};
/////////////////////////////////////////////////////////////////

//Map class// Stores an instance of the game

    //Create all floors of map
Map::Map(int dimx, int dimy,string filename, string race): 
dimx{dimx}, dimy{dimy}, level{0}, player{spawnPlayer(race[0])}, info{dimy, player} {
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

    //get the position of the player when the level starts
    void Map::getx(){
        x = Maps[level].getx();
    };
    void Map::gety(){
        y = Maps[level].gety();
    };
    //Initialize the current Level
    void Map::newLevel(){
        Maps[++level].init();
        getx();
        gety();
    };

//Gets the character in a cell on the current floor
char Map::Cellstr(int y, int x) const{
    return Maps[level].Cellstr(y,x);
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
    out << floor.info;
    return out;
};