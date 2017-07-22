#include <iostream>
#include <sstream>
#include <string>
#include "game.h"
using namespace std;

static int dimx = 79;
static int dimy = 25;
static bool playing = true;
/////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]){

    //Check that at most one file is specified
    if(argc > 2){
        cerr << "Only one file... please" << endl;
        return 1;
    }
/////////////////////////////////////////////////////////////////

    //Begin a game
    playing = true;
    while(playing){
    cout << "At any time you may quit by typing: q" << endl;
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
        //Create a map of dimensions dimx*dimy
        //Use the default file if none specified
        //Sets the race of the character
        Map map(dimx, dimy, "default.txt", race);
        cout << map;
/////////////////////////////////////////////////////////////////
        //Print valid comands
        //cout << "Valid Commands are:" << endl;
        //cout << "\t" << "Just did a tab" << endl;


        //Start the game, read commands, one line at a time
		while (map.getLevel() != 5 && getline(cin, line)) {
			istringstream line_in{ line };
			line_in >> command;
			//Quit the game
			if (command == "q") {
				cout << "Quitting Game..." << endl;
				return 0;
			}
			//Restart the game
			else if (command == "r" || map.getLevel() == 5) {
				cout << "Restarting Game..." << endl;
				break;
			}
			//Freeze enemies
			else if (command == "f") {
				//map.freeze();
			}
			//Let's make a move
			else if (command == "no" || command == "ne" || command == "ea" || command == "se"
				|| command == "so" || command == "sw" || command == "we" || command == "nw") {
				map.move(command);
				/*#peter: you might need indiv cases so you can output
				 .. Player has moved North! .. south, southwest, etc.. */
			}

            //Let's use a potion
            else if(command == "u"){
                line_in >> command;
                    if(command == "no" || command == "ne" || command == "ea" || command == "se"
                    || command == "so" || command == "sw" || command == "we" || command == "nw");
                else cout << "Invalid Direction" << endl;
            }

            //Let's smash some skulls
            else if(command == "a"){
                line_in >> direction;
                if(command == "no" || command == "ne" || command == "ea" || command == "se"
                || command == "so" || command == "sw" || command == "we" || command == "nw");
                else cout << "Invalid Direction" << endl;
            }

            //Not a valid command
            else cout << "Invalid Command" << endl;
			
			//#peter: dont need endl here as map ostream endl's
			if (map.getLevel() != 5) cout << map;// << endl; 
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
            getline(cin,command);//Throw away rest of line
            if(quit == 'y') playing = false;
            else if(quit == 'n') playing = true;
            else {
                cout << "Invalid Answer: " << quit << "... Ending game" << endl;
                playing = false;
            }
        }
    }
}