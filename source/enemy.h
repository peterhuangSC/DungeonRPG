#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <string>
#include <map>
#include "character.h"
//#include "player.h"

class Player;

class Enemy : public Character {
	
protected:
	int enemyLevel;
	int goldDrop;
	std::string enemyType;

	bool isMovable;
	bool isHostile;
	
public:
	Enemy(int health = 140, int attack = 20, int defense = 20,
		std::string myEnemyType = "Human", int goldDrop = 2, char mapSymbol = 'H');
	~Enemy();

	int getLevel();
	void setLevel(int newLevel);
	std::string getEnemyType() override;

	void levelUp();

	virtual bool attackPlayer(Character* player);
	void severTies();
	void dropGold(); //may return Item instead of void in the future
	void notifyObservers();
};

#endif