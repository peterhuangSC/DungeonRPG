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
	Potion(std::shared_ptr<Object> myObj, std::string potName, std::string id, 
		int hEff, int aEff, int dEff);
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
