#include "game.h"

using namespace std;

extern bool playing;
static int dim_x = 79;
static int dim_y = 25;
static PlayerGenerator PG;

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

    //Finds player on this floor
int Floor::get(char var){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].getType() == '@') {
                if(var == 'y') return y;
                if(var == 'x') return x;
            }
        }
    }
};

void Floor::init(shared_ptr<Object> player){
    //Generators
    LadderGenerator LG;
    PotionGenerator PG;
    GoldGenerator   GG;
    EnemyGenerator  EG;
    
    //Place the Player
    int r = 1 + (rand() % 5);
    rooms[r].removeFree()->setonCell(player);
    int noLadder = r; //Ladder & Player can't start in same room 

    //Place a ladder
     r = 1 + (rand() % 5);
    if(r == noLadder) r = ++r % 5;
    rooms[r].removeFree()->setonCell(LG.spawnLadder(r));

    //Place the potions
    for(int i = 0; i < 10; ++i){
        r = 1 + (rand() % 5);
        rooms[r].removeFree()->setonCell(PG.spawnPotion());
    }
    //Place the gold
    for(int i = 0; i < 10; ++i){
        r = 1 + (rand() % 5);
        rooms[r].removeFree()->setonCell(GG.spawnGold());
    }
    //Place the enemies
    for(int i = 0; i < 20; ++i){
        r = 1 + (rand() % 5);
        rooms[r].removeFree()->setonCell(EG.spawnEnemy());
    }
};

void Floor::attachObs(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            Cell &cell = ground[y][x];
            if(cell.getType() == '.'){
                if(ground[ y ][x-1].getType() == '.') cell.Observers.push_back(&ground[ y ][x-1]);
                if(ground[y-1][ x ].getType() == '.') cell.Observers.push_back(&ground[y-1][ x ]);
                if(ground[ y ][x+1].getType() == '.') cell.Observers.push_back(&ground[ y ][x+1]);
                if(ground[y+1][ x ].getType() == '.') cell.Observers.push_back(&ground[y+1][ x ]);
                if(ground[y-1][x-1].getType() == '.') cell.Observers.push_back(&ground[y-1][x-1]);
                if(ground[y+1][x-1].getType() == '.') cell.Observers.push_back(&ground[y+1][x-1]);
                if(ground[y-1][x+1].getType() == '.') cell.Observers.push_back(&ground[y-1][x+1]);
                if(ground[y+1][x+1].getType() == '.') cell.Observers.push_back(&ground[y+1][x+1]);
            }
        }
    }
}

    //Performs actions at end of enemy turn
void Floor::endTurn(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].onCell && ground[y][x].onCell->canMove()){
                bool attacked = false;
                // Attack the character if near
                int size = ground[y][x].Observers.size();
                for(int o = 0; o < size; ++o){
                    if(ground[y][x].Observers[o]->getType() == '@'){
                        attacked = true;
                        if(ground[y][x].onCell->attackPlayer(ground[y][x].Observers[o]->onCell)) return;
                    }
                }
                //No player, we will move randomly
                if(!attacked){
                    Cell &newCell = randMove(ground[y][x]);
                    if(&ground[y][x] != &newCell){
                        newCell.setonCell(ground[y][x].onCell);
                        ground[y][x].onCell.reset();
                    }
                }
            }
        }
    }
};

    //Movement
int Floor::move(string dir, int y, int x){
    Cell *curr = &ground[y][x];
    Cell *cell = curr;
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
    if(type ==  '.' || type ==  '+' || type ==  '#' || (type == 'G' && !cell->onCell->isGuarded())){
             if(dir == "no") {curr->onCell->setAction("PC moves North.");}
        else if(dir == "ne") {curr->onCell->setAction("PC moves North-East.");}
        else if(dir == "ea") {curr->onCell->setAction("PC moves East.");}
        else if(dir == "se") {curr->onCell->setAction("PC moves South-East.");}
        else if(dir == "so") {curr->onCell->setAction("PC moves South.");}
        else if(dir == "sw") {curr->onCell->setAction("PC moves South-West.");}
        else if(dir == "we") {curr->onCell->setAction("PC moves West.");}
        else if(dir == "nw") {curr->onCell->setAction("PC moves North-West.");}

        //If gold on Cell, and unguarded
        if(type == 'G') curr->onCell->addGoldItem(cell->onCell);
        cell->setonCell(curr->onCell);
        cell->notifyAll();
        curr->onCell.reset();
        return 3;
    }
    //If gold on Cell, but guarded
    else if(type ==  'G' && cell->onCell->isGuarded()){
        curr->onCell->setAction("Something is in your way.");
        curr->onCell->addGoldItem(cell->onCell);
        return 2;
    }
    //If Level Up
    else if (type ==  '\\'){
        curr->onCell;
        return 1;
    }
    //Something in the way
    else{
        curr->onCell->setAction("Something is in your way.");
        return 0;
    }
};

    //Consume a Potion
void Floor::potion(string dir, int y, int x){
    Cell *curr = &ground[y][x];
    Cell *cell = curr;
         if(dir == "no") cell = &ground[y-1][ x ];
    else if(dir == "ne") cell = &ground[y-1][x+1];
    else if(dir == "ea") cell = &ground[ y ][x+1];
    else if(dir == "se") cell = &ground[y+1][x+1];
    else if(dir == "so") cell = &ground[y+1][ x ];
    else if(dir == "sw") cell = &ground[y+1][x-1];
    else if(dir == "we") cell = &ground[ y ][x-1];
    else if(dir == "nw") cell = &ground[y-1][x-1];

    if(cell->getType() == 'P'){
        curr->onCell->setAction("");
        curr->onCell->consumePotion(cell->onCell);
        cell->onCell.reset();
    }
    else{
        curr->onCell->setAction("Thats not a potion!");
    }
}
    //Attack an enemy
void Floor::attack(string dir, int y, int x){
    Cell *curr = &ground[y][x];
    Cell *cell = curr;
         if(dir == "no") cell = &ground[y-1][ x ];
    else if(dir == "ne") cell = &ground[y-1][x+1];
    else if(dir == "ea") cell = &ground[ y ][x+1];
    else if(dir == "se") cell = &ground[y+1][x+1];
    else if(dir == "so") cell = &ground[y+1][ x ];
    else if(dir == "sw") cell = &ground[y+1][x-1];
    else if(dir == "we") cell = &ground[ y ][x-1];
    else if(dir == "nw") cell = &ground[y-1][x-1];

    if(cell->onCell && cell->onCell->getEnemyType() != "Object"){
        curr->onCell->setAction("");
        cell->onCell = curr->onCell->attackEnemy(cell->onCell);
    }
    else{
        curr->onCell->setAction("Thats not a enemy!");
    }
}


//Takes in current cell, returns random free adjacent cell
Cell &Floor::randMove(Cell &cell){
    int tries = 100;
    int r;
    while(tries--){
        r = rand() % cell.Observers.size();
        if(cell.Observers[r]->getType() == '.') return *cell.Observers[r];
    }
    return cell;
};

/////////////////////////////////////////////////////////////////

//Info Class// stores Maps information
Info::Info(int dimx, shared_ptr<Object> player): dimx{dimx}, level{0}, player{player} {};

void Info::levelUp(){++level;};

ostream &operator<<(ostream &out, const Info info){
    int size = 22 + info.player->getHeroType().length() + to_string(info.player->getGold()).length();
    string line(info.dimx - size,' ');
    cout << "Race: " << info.player->getHeroType() << "  Gold: " << info.player->getGold();
    cout << line << "Floor: " << info.level + 1 << endl;
    out << "HP : " << info.player->getHealth() << endl;
    out << "Atk: " << info.player->getAttack() << endl;
    out << "Def: " << info.player->getDefense() << endl;
    istringstream saction{info.player->getAction()};
    string action = "";
    string word;
    int line_size = 0;
    while(saction >> word){
        action += word + " ";
        line_size += word.length() +1;
        if(line_size >= info.dimx - 15){
            action += "\n        ";
            line_size = 0;
        }
    }   
	out << "Action: " << action << endl;
    return out;
};
/////////////////////////////////////////////////////////////////

//Map class// Stores an instance of the game

    //Find the position of player
void Map::get(){
    y = Maps[level].get('y');
    x = Maps[level].get('x');
};

    //The char in this cell on the current floor
char Map::Cellstr(int y, int x) const{
    return Maps[level].Cellstr(y,x);
};

    //Initialize the current Level
void Map::init_Level(){
    if(level == 5){
        playing = false;
        cout << "\n\n\n\n         CONGRATS, YOU WON THE GAME!\n" << endl; 
        cout <<         "             YOUR SCORE WAS: " << player->getGold() << "\n\n\n" << endl;
    }
    else {
        Maps[level].init(player);
        player->setAction("Player Enters Level " + to_string(level+1));;
        this->get();     
    }
};

    //End the turn
void Map::endTurn(){
    if(player->getHealth() <= 0){
        cout << *this;
        playing = false;
        cout << "\n\n\n\n         GAME OVER, YOU HAVE DIED!\n" << endl; 
        cout <<         "             YOUR SCORE WAS: " << player->getGold() << "\n\n\n" << endl;
        return;
    }
    if(!frozen) Maps[level].endTurn();
    if(player->getHealth() <= 0){
        cout << *this;
        playing = false;
        cout << "\n\n\n\n         GAME OVER, YOU HAVE DIED!\n" << endl; 
        cout <<         "             YOUR SCORE WAS: " << player->getGold() << "\n\n\n" << endl;
        return;
    }
    player->endTurnEffect();
}

    //Create all floors of map
Map::Map(string filename, string race): 
dimx{dim_x}, dimy{dim_y}, level{0}, frozen{false}, 
player{PG.spawnPlayer(race[0])}, info(dim_x, player) {
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
        }
    }
    for(int i = 0; i < 5; ++i){ 
        Maps[i].attachObs();
    }
    this->init_Level();
};

    //Freeze
    void Map::freeze(){
        frozen = !frozen;
        if(frozen) player->setAction("Game frozen. All enemies won't move");
        if(!frozen) player->setAction("Game unfrozen. All enemies can move");
        };

    //Movement
void Map::move(string dir){
    int result = Maps[level].move(dir, y, x);
         if(result == 3) {
             if(dir == "no") {--y;    ;}
        else if(dir == "ne") {--y; ++x;}
        else if(dir == "ea") {     ++x;}
        else if(dir == "se") {++y; ++x;}
        else if(dir == "so") {++y;     }
        else if(dir == "sw") {++y; --x;}
        else if(dir == "we") {     --x;}
        else if(dir == "nw") {--y; --x;}
    }
    else if(result == 2) {
    }
    else if(result == 1) {
        ++level;
        info.levelUp();
        this->init_Level();
        player->levelUp();
    }
    else {  

    }
    if(result != 1) endTurn();
};

    //Potions
    void Map::potion(string dir){   
        Maps[level].potion(dir, y, x);
        endTurn();
    };

    //Attacking
    void Map::attack(string dir){
        Maps[level].attack(dir, y, x);
        endTurn();
    };

//Outputs current floor of Map
ostream &operator<<(ostream &out, const Map floor){
    string spacing(28, '\n');
    cout << spacing;
    for(int y = 0; y < dim_y; ++y){
        for(int x = 0; x < dim_x; ++x){
            out << floor.Cellstr(y,x);
        }
        out << endl;
    }
    out << floor.info;
    return out;
};



