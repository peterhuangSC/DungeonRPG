#include "PlayerGenerator.h"

using namespace std;

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

shared_ptr<Player> PlayerGenerator::spawnPlayer(char type) {
	switch (type) {
	case 's' : //shade
		return make_shared<Shade>();
	case 'd': //drow
		return make_shared<Drow>();
	case 'v': //vampire
		return make_shared<Vampire>();
	case 't': //troll
		return make_shared<Troll>();
	case 'g': //goblin
		return make_shared<Goblin>();
	default: 
		//ERROR no such class exists but whatever here's a Shade dude
		return make_shared<Shade>();
	}
}

void PlayerGenerator::reset() {}
