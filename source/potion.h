#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include <memory>
#include <vector>
#include "item.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Potion : public Item {
protected:
	std::string potionID;
	std::string potionName;
	int healthEffect;
	int attackEffect;
	int defenseEffect;

	std::shared_ptr<Object> nextPotion;
public:
	Potion(std::shared_ptr<Potion> nextPotion, std::string potName = "No Effect Potion",
		std::string id = "NEFF", int hEff = 0, int aEff = 0, int dEff = 0);
	~Potion();

	//accessors and mutators
	char getType() override;
	int getHealthEffect() override;
	int getAttackEffect() override;
	int getDefenseEffect() override;

	void setAttackEffect(int value) override;
	void setDefenseEffect(int value) override;

	std::string getPotionName() override;
	void setNextPotion(std::shared_ptr<Object> myPotion) override;

	virtual std::vector<int> potionBuffers() override;

	virtual void notify(std::shared_ptr<Object> player) override;

	//---------------------------helper-----------------------------//
	//std::string getAttachedHeroName(std::shared_ptr<Object> myObj);
};

#endif
