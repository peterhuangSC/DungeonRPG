#include <string>
#include "troll.h"

using namespace std;

//additional attributes: const string trollHeroID = "Drow", healthGainRate = 5

//default stats: health 120, attack 25, defense 15
Troll::Troll(int health = 120, int attack = 25, int defense = 15) :
	Player(health, attack, defense, trollHeroID) {}

Troll::~Troll() {}

