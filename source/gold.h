#ifndef __GOLD_H__
#define __GOLD_H__

#include "item.h"

class Gold : public Item {
protected:
	int amount;
	int quantity;
	bool guarded;
public:
	Gold(int gValue = 1, int gQuantity = 1, bool gGuarded = false);
	~Gold();

	//fix implement@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	bool consumeGold(std::shared_ptr<Object> spPlayer) override;

	char getItemType() override;

	int getValue();
	void setValue(int newValue);

	int getQuantity();
	void setQuantity(int newQty);

	bool isGuarded();
	void setGuarded();
	void setUnguarded();
};

#endif
