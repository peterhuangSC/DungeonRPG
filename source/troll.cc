#include <string>
#include "troll.h"

using namespace std;

//additional attributes: const string trollHeroID = "Drow", healthGainRate = 5

//default stats: health 120, attack 25, defense 15
Troll::Troll(int health, int attack, int defense) :
	Player(health, attack, defense, "Troll"), 
	healthGainRate{ 5 } {}

Troll::~Troll() {}

void Troll::endTurnEffect() {
	if (curHealth < maxHealth) {		
		this->curAction += " Special Ability: PC regenerated " 
			+ to_string(min(healthGainRate, maxHealth - curHealth));
		this->curAction += " health points.";
		// now change curHealth, since the above uses the original values
		this->curHealth = min(this->curHealth + healthGainRate, this->maxHealth);
	}	
}
