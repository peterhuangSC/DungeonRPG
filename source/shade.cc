#include <string>
#include "shade.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */
//additional attributes: const string shadeHeroID = "Shade"

Shade::Shade(int health, int attack, int defense) :
	Player(health, attack, defense, "Shade") {}

Shade::~Shade() {}


