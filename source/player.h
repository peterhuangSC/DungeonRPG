#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <memory>
#include <map>
#include "character.h"
#include "gold.h"
//#include "enemy.h"

class Enemy;

class Player : public Character {

protected:
	int curLevel;
	int gold;
	std::string heroType;
	
	//std::map <std::string, bool> potions;

public:
	Player(int health = 125, int attack = 25, int defense = 25,
		std::string myHeroType = "Shade");
	~Player();

	int getLevel() override;
	void setLevel(int newLevel);
	std::string getHeroType() override;

	int getGold() override;

	void levelUp() override;
	void addGold(int myGold) override;
	bool addGoldItem(std::shared_ptr<Object> myGold) override;

	virtual std::shared_ptr<Object> attackEnemy(std::shared_ptr<Object> enemy) override;
	void notifyObservers();
};

#endif
