#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <string>
#include "object.h"

class Character : public Object {

protected:
	int curHealth;
	int maxHealth; //require curHealth < maxHealth

	int attack;
	int defense;

public:
	Character(int health, int attack, int defense, char myType);
	~Character();

	//virtual bool attack(Character* c) = 0;
	bool receiveDmg(int dmg);

	//accessors and mutators
	int getHealth();
	virtual void setHealth(int newHealth);

	int getAttack();
	void setAttack(int newAttack);

	int getDefense();
	void setDefense(int newDefense);

	virtual std::string getHeroType() = 0;
	virtual std::string getEnemyType() = 0;
};

#endif