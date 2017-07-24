#include <iostream>
#include <sstream>
#include <string>
#include "game.h"
using namespace std;

bool playing = true;
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
        
        if(!getline(cin,race)) return 0;

        //Which race did they choose?
        if(race == "q") {
            cout << "Quitting Game..." << endl;
            return 0;
        }
    //Create a map//
        //Sets the race of the character

        //Use the default file if none specified, random gen
        //if(argc == 1) 
        Map map("default.txt", race);
        //Otherwise use the one specified
        //else Map map(argv[2], race);
        cout << map;

/////////////////////////////////////////////////////////////////
    //Print valid comands//
        //cout << "Valid Commands are:" << endl;
        //cout << "\t" << "Just did a tab" << endl;

    //Start the game, read commands, one line at a time//
		while (playing && getline(cin, line)) {
			istringstream line_in{ line };
			line_in >> command;

			//Quit the game
			if (command == "q") {
				cout << "Quitting Game..." << endl;
				return 0;
			}
			//Restart the game
			else if (command == "r") {
				cout << "Restarting Game..." << endl;
				break;
			}
			//Freeze enemies
			else if (command == "f") {
				map.freeze();
			}
			//Let's make a move
			else if (command == "no" || command == "ne" || command == "ea" || command == "se"
				  || command == "so" || command == "sw" || command == "we" || command == "nw")
				{map.move(command);}
            //Let's use a potion
            else if(command == "u"){
                line_in >> command;
                    if(command == "no" || command == "ne" || command == "ea" || command == "se"
                    || command == "so" || command == "sw" || command == "we" || command == "nw")
                    {map.potion(command);}
                else cout << "Invalid Direction" << endl;
            }
            //Let's smash some skulls
            else if(command == "a"){
                line_in >> direction;
                if(command == "no" || command == "ne" || command == "ea" || command == "se"
                || command == "so" || command == "sw" || command == "we" || command == "nw")
                {map.attack(command);}
                else cout << "Invalid Direction" << endl;
            }
            //Not a valid command
            else cout << "Invalid Command" << endl;
			if(playing) cout << map; 
        }

    //Endgame Process//
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