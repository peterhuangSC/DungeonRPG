#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <map>
#include "character.h"
//#include "enemy.h"

class Enemy;

class Player : public Character {

protected:
	int curLevel;
	int gold;
	std::string heroType;
	std::map <std::string, bool> potions;

public:
	Player(int health, int attack, int defense, std::string myHeroType);
	~Player();

	int getLevel();
	void setLevel(int newLevel);
	std::string getHeroType() override;

	int getGold();

	void levelUp();
	void addGold(int myGold) override;

	virtual bool attackEnemy(Character* enemy);
	void move(std::string direction); //implement coordinates?
	void notifyObservers();
};

#endif