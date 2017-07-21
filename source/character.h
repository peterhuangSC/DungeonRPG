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
	int getHealth() override;
	void setHealth(int newHealth) override;

	int getAttack() override;
	void setAttack(int newAttack);

	int getDefense() override;
	void setDefense(int newDefense);

};

#endif