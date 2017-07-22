#include "game.h"

using namespace std;

//Hard Coded Rooms 
static int ur1 = 3;  static int uc1 = 3;  static int lr1 = 8;  static int lc1 = 30;// Room 1
static int ur2 = 3;  static int uc2 = 39; static int lr2 = 8;  static int lc2 = 63;// Room 2
static int ur3 = 5;  static int uc3 = 61; static int lr3 = 14; static int lc3 = 77;// Room 2 (aswell)
static int ur4 = 16; static int uc4 = 37; static int lr4 = 23; static int lc4 = 77;// Room 3
static int ur5 = 15; static int uc5 = 5;  static int lr5 = 23; static int lc5 = 26;// Room 4
static int ur6 = 10; static int uc6 = 38; static int lr6 = 14; static int lc6 = 51;// Room 5

int whatRoom(int y, int x, char c){
    if(c == '.'){
             if((ur1 <= y && uc1 <= x) && (y <= lr1 && x <= lc1)) return 1;
        else if((ur2 <= y && uc2 <= x) && (y <= lr2 && x <= lc2)) return 2;
        else if((ur3 <= y && uc3 <= x) && (y <= lr3 && x <= lc3)) return 2;
        else if((ur4 <= y && uc4 <= x) && (y <= lr4 && x <= lc4)) return 3;
        else if((ur5 <= y && uc5 <= x) && (y <= lr5 && x <= lc5)) return 4;
        else if((ur6 <= y && uc6 <= x) && (y <= lr6 && x <= lc6)) return 5;
        else return 0;
    }
    else return 0;
}

/////////////////////////////////////////////////////////////////

//Cell Class//

Cell::Cell(): Type{' '}, room{0}, onCell{nullptr} {};

    //Puts an object on Cell if empty
bool Cell::setonCell(shared_ptr<Object> o){
        onCell = o;
        this->notifyAll();
        return true;
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
    int r = rand() % free--;
    Cell *cell = freeCells[r];// Could use shared pointers
    freeCells.erase(freeCells.begin()+r);
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
    ground[y][x].room = whatRoom(y,x,c);
    rooms[ground[y][x].room].addFree(&ground[y][x]);
};


int Floor::getx(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].getType() == '@') return x;
        }
    }
};


int Floor::gety(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].getType() == '@') return y;
        }
    }
};

void Floor::init(shared_ptr<Object> player){
    //Generators
    LadderGenerator LG;
    PotionGenerator PG;
    GoldGenerator   GG;
    EnemyGenerator  EG;
    
    //Player room cannot be ladder room
    int r = 1 + (rand() % 5);
    int noLadder = r;

    //Place the Player
    rooms[r].removeFree()->setonCell(player);
   
    //Place a ladder
     r = 1 + (rand() % 5);
    if(r == noLadder) r = ++r % 5;
    rooms[r].removeFree()->setonCell(LG.spawnLadder(r));

};

    //Movement
int Floor::move(string dir, int y, int x){
    Cell *curr = &ground[y][x];
    Cell *cell;
         if(dir == "no") cell = &ground[y-1][ x ];
    else if(dir == "ne") cell = &ground[y-1][x+1];
    else if(dir == "ea") cell = &ground[ y ][x+1];
    else if(dir == "se") cell = &ground[y+1][x+1];
    else if(dir == "so") cell = &ground[y+1][ x ];
    else if(dir == "sw") cell = &ground[y+1][x-1];
    else if(dir == "we") cell = &ground[ y ][x-1];
    else if(dir == "nw") cell = &ground[y-1][x-1];

    //Check if cell is valid;
    char type = cell->getType();
    if(type ==  '.' || type ==  '+' || type ==  '#'){
        cell->setonCell(curr->onCell);
        curr->onCell.reset();
        return 3;
    }
    else if(type ==  'G' && cell->onCell->isGuarded()){
        return 2;
    }
    else if (type ==  '\\'){
        return 1;
    }
    else{
        return 0;
    }
};

/////////////////////////////////////////////////////////////////

//Info Class// stores Maps information
Info::Info(int dimy): dimy{dimy}, level{0} {};

void Info::levelUp(){++level;};

ostream &operator<<(ostream &out, const Info info){
    string race = info.player->getHeroType();
    string line(56 - race.length(),' ');
    out << "Race: " << race << " Gold: " <<  0; //info.player->getGold();
    out << line << "Floor: " << info.level + 1 << endl;
    out << "HP:  " << info.player->getHealth() << endl;
    out << "Atk: " << info.player->getAttack() << endl;
    out << "Def: " << info.player->getDefense() << endl;
    out << "Action: " << endl;
    return out;
};
/////////////////////////////////////////////////////////////////

//Map class// Stores an instance of the game

    //Create all floors of map
Map::Map(int dimx, int dimy,string filename, string race): dimx{dimx}, dimy{dimy}, level{0}, info(dimy) {
    PlayerGenerator PG;
    player = PG.spawnPlayer(race[0]);
    cout << "Type: " << player->getHeroType() << endl; 
    cout << "atk: " << player->getHealth() << endl;
    cout << "atk: " << player->getAttack() << endl;
    cout << "def: " << player->getDefense() << endl;
    cout << player->getHeroType() << endl;
    info.player = player;
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
    this->init_Level();
};

    //get the position of the player when the level starts
void Map::getx(){
    x = Maps[level].getx();
};
void Map::gety(){
    y = Maps[level].gety();
};
    //Initialize the current Level
void Map::init_Level(){
    if(level != 5){
        Maps[level].init(player);
        this->getx();
        this->gety();            
    }
    else {
        cout << "CONGRATS, YOU WON! YOUR SCORE WAS: " << 0 << endl;
    }
};

    

//Gets the character in a cell on the current floor
char Map::Cellstr(int y, int x) const{
    return Maps[level].Cellstr(y,x);
};

int Map::getLevel(){ return level;};

    //Movement
void Map::move(string dir){
    int result = Maps[level].move(dir, y, x);
         if(result == 3) {
             if(dir == "no") {--y;      }
        else if(dir == "ne") {--y; ++x;}
        else if(dir == "ea") {     ++x;}
        else if(dir == "se") {++y; ++x;}
        else if(dir == "so") {++y;     }
        else if(dir == "sw") {++y; --x;}
        else if(dir == "we") {     --x;}
        else if(dir == "nw") {--y; --x;}
        //set player action
    }
    else if(result == 2) {
    }
    else if(result == 1) {
        ++level;
        info.levelUp();
        this->init_Level();
    }
    else {
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
    out << floor.info;
    return out;
};