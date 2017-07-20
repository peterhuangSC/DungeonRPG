#include <string>
#include "shade.h"

//additional attributes: const string shadeHeroID = "Shade"

Shade::Shade(int health = 125, int attack = 25, int defense = 25) :
	Player(health, attack, defense, shadeHeroID) {}

Shade::~Shade() {}


