#include <string>
#include "drow.h"

//additional attributes: const string drowHeroID = "Drow", potionEffectRate = 1.5
//note: when attaching potions, check to make sure effects are 1.5x

//default stats: health 150, attack 25, defense 15
Drow::Drow(int health = 150, int attack = 25, int defense = 15) :
	Player(health, attack, defense, drowHeroID) {}

Drow::~Drow() {}


