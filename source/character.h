#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <string>
#include <memory>
#include <algorithm>
#include "object.h"
#include "potion.h"

/* This project was developed by:
   Peter Huang [zh3huang] and Shane Mazur [smazur]*/

class Character : public Object {

protected:
	int curHealth;
	int maxHealth; //require curHealth < maxHealth

	int attack;
	int defense;

//	std::shared_ptr<Object> potionBuffs;
	std::string curAction;

public:
	Character(int health, int attack, int defense, char myType);
	~Character();

	//virtual bool attack(Character* c) = 0;
	virtual bool receiveDmg(int dmg) override;

	//accessors and mutators
	int getHealth() override;
	virtual void setHealth(int newHealth) override;

	int getAttack() override;
	void setAttack(int newAttack);

	int getDefense() override;
	void setDefense(int newDefense);

	std::shared_ptr<Object> getPotionBuffs();

	virtual void consumePotion(std::shared_ptr<Object> myPotion);

	std::string getAction() override;
	void setAction(std::string newAction) override;
	void appendAction(std::string appAction) override;
};

#endif
