#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include <memory>
#include "item.h"

class Potion : public Item {
protected:
	std::shared_ptr<Object> player;
	std::string potionID;
	std::string potionName;
	int healthEffect;
	int attackEffect;
	int defenseEffect;
public:
	Potion(std::shared_ptr<Object> pPlayer, std::string potName = "No Effect Potion", 
	std::string id = "NEFF", int hEff = 0, int aEff = 0, int dEff = 0);
	~Potion();

	//accessors and mutators
	char getType() override;
	int getHealthEffect() override;
	int getAttackEffect() override;
	int getDefenseEffect() override;

	//---------------------------helper-----------------------------//
	std::string getAttachedHeroName(std::shared_ptr<Object> myObj);
};

#endif
