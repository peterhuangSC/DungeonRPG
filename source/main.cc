#include <iostream>
#include <sstream>
#include <string>
#include "game.h"
using namespace std;

static int dimx = 79;
static int dimy = 25;
/////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]){

    //Check that at most one file is specified
    if(argc > 2){
        cerr << "Only one file... please" << endl;
        return 1;
    }
/////////////////////////////////////////////////////////////////

    //Create a game
    bool playing = true;
    while(playing){
        //Create a map of dimensions dimx*dimy
        //Use the default file if none specified
        
        Map map(dimx, dimy, "default.txt");
/////////////////////////////////////////////////////////////////

        //Command Initiliaztions
        string line;
        string race;
        string command;
        string direction;
        char quit;

        //Player must choose race
        cout << "Choose a Race, one of:  s, d, v, g, t" << endl;
        if(!getline(cin,line)) return 0;
        istringstream line_in{line};
        line_in >> race;

        //Which race did they choose?
        if(race == "q") {
            cout << "Quitting Game..." << endl;
            return 0;
        }
        else if(race == "s"){
            cout << "You are a Shade!" << endl;
            //intitialize player to Shade 
        }
        else if(race == "d"){
            cout << "You are a Drow!" << endl;
            //intitialize player to Drow
        }
        else if(race == "v"){
            cout << "You are a Vampire!" << endl;
            //intitialize player to Vampire
        }
        else if(race == "g"){
            cout << "You are a Goblin!" << endl;
            //intitialize player to Goblin
        }
        else if(race == "t"){
            cout << "You are a Troll!" << endl;
            //intitialize player to Troll
        }
        else{
            cout << "Invalid Race, defaulting to Shade" << endl;
            //Default to Shade
            //intitialize player to Shade
        }
/////////////////////////////////////////////////////////////////

        //Start the game, read commands, one line at a time
        while(getline(cin,line)) {
            istringstream line_in{line};
            line_in >> command;
            //Quit the game
            if(command == "q") {
            cout << "Quitting Game..." << endl;
            return 0;
            }
            //Restart the game
            else if(command == "r") {
            cout << "Restarting Game..." << endl;
            break;
            }
            //Freeze enemies
            else if(command == "f"){
                //map->freeze();
            }
            //Let's make a move
            else if(command == "no"); //move player north
            else if(command == "ne"); //move player north-east
            else if(command == "ea"); //move player east
            else if(command == "se"); //move player south-east
            else if(command == "so"); //move player south
            else if(command == "sw"); //move player south-west
            else if(command == "we"); //move player west
            else if(command == "nw"); //move player north-west

            //Let's use a potion
            else if(command == "u"){
                line_in >> direction;
                     if(direction == "no"); //use potion north
                else if(direction == "ne"); //use potion north-east
                else if(direction == "ea"); //use potion east
                else if(direction == "se"); //use potion south-east
                else if(direction == "so"); //use potion south
                else if(direction == "sw"); //use potion south-west
                else if(direction == "we"); //use potion west
                else if(direction == "nw"); //use potion north-west
                else cout << "Invalid Direction" << endl;
            }

            //Let's smash some skulls
            else if(command == "a"){
                line_in >> direction;
                     if(direction == "no"); //attack enemy north
                else if(direction == "ne"); //attack enemy north-east
                else if(direction == "ea"); //attack enemy east
                else if(direction == "se"); //attack enemy south-east
                else if(direction == "so"); //attack enemy south
                else if(direction == "sw"); //attack enemy south-west
                else if(direction == "we"); //attack enemy west
                else if(direction == "nw"); //attack enemy north-west
                else cout << "Invalid Direction" << endl;
            }

            //Not a valid command
            else cout << "Invalid Command" << endl;
            cout << map;
        }

        //Endgame Process
        //EOF ends the game
        if(cin.eof()) playing = false;
        //Restart the game
        else if(command == "r"); //Do nothing, game will restart
        //Otherwise, check if they want to continue
        else{
            cout << "Quit the game?(y/n)" << endl;
            cin >> quit;
            if(quit == 'y') playing = false;
            else if(quit == 'n') playing = true;
            else {
                cout << "Invalid Answer: " << quit << "... Ending game" << endl;
                playing = false;
            }
        }

    }
}