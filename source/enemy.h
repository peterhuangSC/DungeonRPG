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
	Enemy(int health, int attack, int defense, 
		std::string myEnemyType, int goldDrop);
	~Enemy();

	int getLevel();
	void setLevel(int newLevel);
	std::string getEnemyType();

	void levelUp();

	virtual bool attackPlayer(Character* player);
	void severTies();
	void randMove();
	void dropGold(); //may return Item instead of void in the future
	void notifyObservers();
};

#endif