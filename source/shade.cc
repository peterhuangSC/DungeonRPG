#include <string>
#include "shade.h"

//additional attributes: const string shadeHeroID = "Shade"

Shade::Shade(int health, int attack, int defense) :
	Player(health, attack, defense, shadeHeroID) {}

Shade::~Shade() {}


