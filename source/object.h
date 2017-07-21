#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <memory>

class Object {
	//no private fields needed so far
protected:
	char type;
	void setType(char newType);
public: 
	Object(char typeSymbol);
	~Object();

	virtual char getType();

	virtual std::string getHeroType();
	virtual std::string getEnemyType();

	virtual int getHealth();
	virtual void setHealth(int newHealth);
	virtual int getAttack();
	virtual int getDefense();

	virtual int getLevel();
	virtual void levelUp();
	virtual int getGold();
	virtual void addGold(int myGold);

	virtual void notify(std::shared_ptr<Object> who);
	virtual bool consumeGold(std::shared_ptr<Object> myObj);
	virtual void consumeLadder(std::shared_ptr<Object> player);

	virtual bool isGuarded();
	virtual void setGuarded();
	virtual void setUnguarded();

	virtual std::string getAction();
	virtual void setAction(std::string newAction);
};

#endif