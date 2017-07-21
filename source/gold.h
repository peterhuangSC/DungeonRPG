#ifndef __GOLD_H__
#define __GOLD_H__

#include "item.h"

class Gold : public Item {
protected:
	int amount;
	int quantity;
	bool guarded;
public:
	Gold(int gValue, int gQuantity, bool gGuarded);
	~Gold();

	void consume(Character* player) override;

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
