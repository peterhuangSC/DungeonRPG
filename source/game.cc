#include "game.h"

using namespace std;

extern bool playing;
static int dim_x = 79;
static int dim_y = 25;

//Generators
static PlayerGenerator CG;
static LadderGenerator LG;
static PotionGenerator PG;
static GoldGenerator   GG;
static EnemyGenerator  EG;

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


void Floor::init(shared_ptr<Object> player, ifstream &layout){
    int dimy = ground.size();
    int dimx = ground[0].size();
    string line;
    //Place all object types
    for(int y = 0; y < dimy; ++y){
        getline(layout, line);
        for(int x = 0; x < dimx; ++x){
            char c = line[x];
            int ic = c - '0';
            if(c == '@') ground[y][x].setonCell(player);
            if(c == '\\') ground[y][x].setonCell(LG.spawnLadder(ground[y][x].getRoom()));
            else if('0' <= c && c <= '5') ground[y][x].setonCell(PG.spawnPotion(ic));
            else if('6' <= c && c <= '9') ground[y][x].setonCell(GG.spawnGold(ic));
            else if('A' <= c && c <= 'Z') ground[y][x].setonCell(EG.spawnEnemy(c));
        }
    }
    //Replace dragons with the one linked to its dragon hoard
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].getType() == 'D'){
                int size = ground[y][x].Observers.size();
                for(int k = 0; k < size; ++k){
                    if(ground[y][x].Observers[k]->onCell && ground[y][x].Observers[k]->onCell->isGuarded()){
                        ground[y][x].setonCell(ground[y][x].Observers[k]->onCell->getAssocObject());
                    }
                }
            }
        }
    }
};


void Floor::init(shared_ptr<Object> player){

    //Place the Player
    int r = 1 + (rand() % 5);
    rooms[r].removeFree()->setonCell(player);
    int noLadder = r; //Ladder & Player can't start in same room 

    //Place a ladder
     r = 1 + (rand() % 5);
    if(r == noLadder) r = 1 + (++r % 5);
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
    //Put associated objects beside the guarded objects
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].onCell && ground[y][x].onCell->isGuarded()){
                Cell &newCell = randMove(ground[y][x]);
                if(&ground[y][x] != &newCell){
                    newCell.setonCell(ground[y][x].onCell->getAssocObject());
                }
            }
        }
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
            if(cell.getType() == '.'|| cell.getType() == '+'){
                if(ground[ y ][x-1].getType() == '.' || ground[ y ][x-1].getType() == '+') cell.Observers.push_back(&ground[ y ][x-1]);
                if(ground[y-1][ x ].getType() == '.' || ground[y-1][ x ].getType() == '+') cell.Observers.push_back(&ground[y-1][ x ]);
                if(ground[ y ][x+1].getType() == '.' || ground[ y ][x+1].getType() == '+') cell.Observers.push_back(&ground[ y ][x+1]);
                if(ground[y+1][ x ].getType() == '.' || ground[y+1][ x ].getType() == '+') cell.Observers.push_back(&ground[y+1][ x ]);
                if(ground[y-1][x-1].getType() == '.' || ground[y-1][x-1].getType() == '+') cell.Observers.push_back(&ground[y-1][x-1]);
                if(ground[y+1][x-1].getType() == '.' || ground[y+1][x-1].getType() == '+') cell.Observers.push_back(&ground[y+1][x-1]);
                if(ground[y-1][x+1].getType() == '.' || ground[y-1][x+1].getType() == '+') cell.Observers.push_back(&ground[y-1][x+1]);
                if(ground[y+1][x+1].getType() == '.' || ground[y+1][x+1].getType() == '+') cell.Observers.push_back(&ground[y+1][x+1]);
            }
        }
    }
};

    //Performs actions at end of enemy turn
void Floor::endTurn(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            bool attacked = false;
            //Enemies attack players
            if(ground[y][x].onCell && ground[y][x].onCell->getHostility()){
                // Attack the character if near
                int size = ground[y][x].Observers.size();
                for(int o = 0; o < size; ++o){
                    if(ground[y][x].Observers[o]->getType() == '@' && !ground[y][x].onCell->turnCompleted()){
                        attacked = true;
                        if(ground[y][x].onCell->attackPlayer(ground[y][x].Observers[o]->onCell)) return;
                    }
                }
            }
            //Guarded Objects tell their guard to attack player
            if(ground[y][x].onCell && ground[y][x].onCell->isGuarded()){
                // Tell my guard to attack the character if near
                int size = ground[y][x].Observers.size();
                for(int o = 0; o < size; ++o){
                    if(ground[y][x].Observers[o]->getType() == '@' && !ground[y][x].onCell->getAssocObject()->turnCompleted()){
                        attacked = true;
                        if(ground[y][x].onCell->getAssocObject()->attackPlayer(ground[y][x].Observers[o]->onCell)) return;
                    }
                }
            }
            //Not hostile or there was no player, so we will move randomly
            if(ground[y][x].onCell&& ground[y][x].onCell->canMove()){
                if(!attacked){
                    Cell &newCell = randMove(ground[y][x]);
                    if(&ground[y][x] != &newCell && !ground[y][x].onCell->turnCompleted()){
                        newCell.setonCell(ground[y][x].onCell);
                        ground[y][x].onCell.reset();
                    }
                }
            }
        }
    }
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].onCell){
                ground[y][x].onCell->newTurn();
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
    if(type ==  '.' || type ==  '+' || type ==  '#' || type == 'G'){
             if(dir == "no") {curr->onCell->setAction("PC moves North.");}
        else if(dir == "ne") {curr->onCell->setAction("PC moves North-East.");}
        else if(dir == "ea") {curr->onCell->setAction("PC moves East.");}
        else if(dir == "se") {curr->onCell->setAction("PC moves South-East.");}
        else if(dir == "so") {curr->onCell->setAction("PC moves South.");}
        else if(dir == "sw") {curr->onCell->setAction("PC moves South-West.");}
        else if(dir == "we") {curr->onCell->setAction("PC moves West.");}
        else if(dir == "nw") {curr->onCell->setAction("PC moves North-West.");}

        //If gold on Cell, 
        if(type == 'G') curr->onCell->addGoldItem(cell->onCell);
        //Unguarded, do nothing, you succsessfully picked it up
        //Guarded
        shared_ptr<Object> wasHeld = curr->onCell->getAssocObject();
        curr->onCell->resetAssocObject();
        if(type == 'G' && cell->onCell->isGuarded()){
            curr->onCell->setAssocObject(cell->onCell);
        }
        cell->setonCell(curr->onCell);
        cell->notifyAll();
        curr->onCell.reset();
        curr->setonCell(wasHeld);
        return 2;
    }
    //If Level Up
    else if (type ==  '\\'){
        curr->onCell = curr->onCell->getAssocObject();
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


    //clears this level at the end of the game
void Floor::clearLevel(){
    int dimy = ground.size();
    int dimx = ground[0].size();
    for(int y = 0; y < dimy; ++y){
        for(int x = 0; x < dimx; ++x){
            if(ground[y][x].onCell){
                ground[y][x].onCell->resetAssocObject();
                ground[y][x].onCell.reset();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////

//Info Class// stores Maps information
Info::Info(int dimx, shared_ptr<Object> player): dimx{dimx}, level{0}, player{player} {};

void Info::levelUp(){++level;};

ostream &operator<<(ostream &out, const Info info){
    int size = 22 + info.player->getHeroType().length() + to_string(info.player->getGold()).length();
    string line(info.dimx - size,' ');
    out << "Race: " << info.player->getHeroType() << "  Gold: " << info.player->getGold();
    out << line << "Floor: " << info.level + 1 << endl;
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
        if(random) Maps[level].init(player);
        else Maps[level].init(player, layout);

        player->setAction("Player Enters Level " + to_string(level+1));;
        this->get();
    }
};

    //End the turn
void Map::endTurn(){
    if(player->getHealth() <= 0){
        cout << *this;
        playing = false;
        int score = player->getGold();
        if(player->getHeroType() == "Shade") score *= 1.5;
        cout << "\n\n\n\n         GAME OVER, YOU HAVE DIED!\n" << endl; 
        cout <<         "             YOUR SCORE WAS: " << score << "\n\n\n" << endl;
        return;
    }
    if(!frozen) Maps[level].endTurn();
    if(player->getHealth() <= 0){
        cout << *this;
        playing = false;
        int score = player->getGold();
        if(player->getHeroType() == "Shade") score *= 1.5;
        cout << "\n\n\n\n         GAME OVER, YOU HAVE DIED!\n" << endl; 
        cout <<         "             YOUR SCORE WAS: " << score << "\n\n\n" << endl;
        return;
    }
    player->endTurnEffect();
}

    //Create all floors of map
Map::Map(string race, bool random, ifstream &layout): 
dimx{dim_x}, dimy{dim_y}, level{0}, frozen{false},
random{random}, layout{layout}, 
player{CG.spawnPlayer(race[0])}, info(dim_x, player) {
    Maps.assign(5,Floor(dimx,dimy));
    ifstream file ("default.txt");
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

    //Invalid message to player
void Map::setPlayerAction(string action){
    player->setAction(action);
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
         if(result == 2) {
             if(dir == "no") {--y;    ;}
        else if(dir == "ne") {--y; ++x;}
        else if(dir == "ea") {     ++x;}
        else if(dir == "se") {++y; ++x;}
        else if(dir == "so") {++y;     }
        else if(dir == "sw") {++y; --x;}
        else if(dir == "we") {     --x;}
        else if(dir == "nw") {--y; --x;}
    }
    else if(result == 1) {
        ++level;
        info.levelUp();
        this->init_Level();
        player->levelUp();
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

    //EndGame Process
void Map::endGame(){
    CG.reset();
    LG.reset();
    GG.reset();
    PG.reset();
    EG.reset();
    for(int i = 0; i < 5; ++i){
        Maps[i].clearLevel();
    }
};

//Outputs current floor of Map
ostream &operator<<(ostream &out, const Map floor){
    string spacing(28, '\n');
    out << spacing;
    out << "|-----------------------------------------------------------------------------|" << endl;
    out << "|----------------------------CHAMBER CRAWLER 3000-----------------------------|" << endl;
    out << "|----------------By: Shane Mazur, Peter Huang & Jason Cheung -----------------|" << endl;
    for(int y = 0; y < dim_y; ++y){
        for(int x = 0; x < dim_x; ++x){
            out << floor.Cellstr(y,x);
        }
        out << endl;
    }
    out << floor.info;
    out << "Command: ";
    return out;
};



