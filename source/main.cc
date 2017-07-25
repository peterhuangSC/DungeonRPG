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
/////////////////////////////////////////////////////////////////

        //Command Initiliaztions
        string line;
        string race;
        string command;
        string direction;
        char quit;

        //Intro
        string spacing(28,'\n');
        cout << spacing;
        cout << "***************************************************************" << endl;
        cout << "***************************************************************" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "*****           WELCOME TO CHAMBER CRAWLER 3000           *****" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "*****     By: Shane Mazur, Peter Huang & Jason Cheung     *****" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "***************************************************************" << endl;
        cout << "***************************************************************" << endl;
        cout << "***************************************************************" << endl;
        cout << "***** Game Commands (Type and press enter)                *****" << endl;
        cout << "*****  - q: Quits the game at any time                    *****" << endl;
        cout << "*****  - r: Restarts the game                             *****" << endl;
        cout << "*****  - f: Freezes the enemies                           *****" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "***** Player Commands (Type and press enter)              *****" << endl;
        cout << "*****  - <direction>  : Moves in that direction           *****" << endl;
        cout << "*****  - u <direction>: Uses a potion(P) in direction     *****" << endl;
        cout << "*****  - a <direction>: Attack in a direction             *****" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "*****  Directions: no, ea, so, we, ne, se, sw, nw         *****" << endl;
        cout << "*****  Note: Pressing enter repeats your last turn        *****" << endl;
        cout << "*****                                                     *****" << endl;
        cout << "***** Choose a Race: s(shade), d(drow), v(vampire),       *****" << endl;
        cout << "*****                   g(goblin), t(troll)               *****" << endl;
        cout << "***************************************************************" << endl;
        cout << "***************************************************************" << endl;
        cout << "Race: ";
        
        if(!getline(cin,race)) return 0;

        //Which race did they choose?
        if(race == "q") {
            cout << "Quitting Game..." << endl;
            return 0;
        }
    //Create a map with the chosen character//
        //Use the default file if none specified, random gen
        bool random = true;
        string file;
        //Otherwise use the one specified
        if(argc == 2) {
            random = false;
            file = argv[1];
        }
        ifstream layout(file);
        Map Game(race, random, layout);
        cout << Game;

/////////////////////////////////////////////////////////////////

    //Start the game, read commands, one line at a time//
		while (playing && getline(cin, line)) {
			istringstream line_in{ line };
			line_in >> command;

			//Quit the game
			if (command == "q") {
                Game.endGame();
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
				Game.freeze();
			}
			//Let's make a move
			else if (command == "no" || command == "ne" || command == "ea" || command == "se"
				  || command == "so" || command == "sw" || command == "we" || command == "nw")
				{Game.move(command);}
            //Let's use a potion
            else if(command == "u"){
                line_in >> direction;
                    if(direction == "no" || direction == "ne" || direction == "ea" || direction == "se"
                    || direction == "so" || direction == "sw" || direction == "we" || direction == "nw")
                    {Game.potion(direction);}
                    else Game.setPlayerAction("Invalid Direction");
            }
            //Let's smash some skulls
            else if(command == "a"){
                line_in >> direction;
                if(direction == "no" || direction == "ne" || direction == "ea" || direction == "se"
                || direction == "so" || direction == "sw" || direction == "we" || direction == "nw")
                {Game.attack(direction);}
                else Game.setPlayerAction("Invalid Direction");
            }
            //Not a valid command
            else Game.setPlayerAction("Invalid Command");
			if(playing) cout << Game; 
        }

    //Endgame Process//
        //EOF ends the game
        if(cin.eof()) playing = false;
        //Restart the game
        else if(command == "r") Game.endGame(); //Do nothing, game will restart
        //Otherwise, check if they want to continue
        else{
            Game.endGame();
            cout << "Quit the game?(y/n)" << endl;
            cin >> quit;
            getline(cin,command);//Throw away rest of line
            if(quit == 'y') {
                playing = false;
                cout << "Quitting Game..." << endl;
            }                
            else if(quit == 'n') playing = true;
            else {
                cout << "Invalid Answer: " << quit << "... Ending game" << endl;
                playing = false;
            }
        }
    }
}



