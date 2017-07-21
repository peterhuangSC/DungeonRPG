#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include <memory>
#include <vector>
#include "item.h"

class Potion : public Item {
protected:
	std::string potionID;
	std::string potionName;
	int healthEffect;
	int attackEffect;
	int defenseEffect;

	std::shared_ptr<Potion> nextPotion;
public:
	Potion(std::shared_ptr<Potion> nextPotion, std::string potName = "No Effect Potion",
		std::string id = "NEFF", int hEff = 0, int aEff = 0, int dEff = 0);
	~Potion();

	//accessors and mutators
	char getType() override;
	int getHealthEffect();
	int getAttackEffect();
	int getDefenseEffect();

	void setAttackEffect(int value);
	void setDefenseEffect(int value);

	std::string getPotionName();
	void setNextPotion(std::shared_ptr<Potion> myPotion);

	virtual std::vector<int> potionBuffers();

	//---------------------------helper-----------------------------//
	//std::string getAttachedHeroName(std::shared_ptr<Object> myObj);
};

#endif
