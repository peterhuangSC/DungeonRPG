#ifndef __GOLD_H__
#define __GOLD_H__

#include <memory>
#include "item.h"

class Gold : public Item {
protected:
	int amount;
	int quantity;
	bool guarded;
public:
	Gold(int gValue = 1, int gQuantity = 1, bool gGuarded = false);
	~Gold();
	
	char getItemType() override;

	int getValue() override;
	void setValue(int newValue);

	int getQuantity() override;
	void setQuantity(int newQty);

	bool isGuarded() override;
	void setGuarded() override;
	void setUnguarded() override;

	void notify(std::shared_ptr<Object> player) override;
};

#endif
