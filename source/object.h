#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <memory>
#include <vector>

class Object {
	//no private fields needed so far
protected:
	std::shared_ptr<Object> potionBuffs;
	bool hadTurn;

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

	virtual int getValue();
	virtual int getQuantity();

	virtual int getLevel();
	virtual void levelUp();
	virtual int getGold();
	virtual void addGold(int myGold);
	virtual bool addGoldItem(std::shared_ptr<Object> myGold); //returns true if pick up success

	virtual void notify(std::shared_ptr<Object> who);
	//virtual bool consumeGold(std::shared_ptr<Object> myObj);
	virtual void consumeLadder(std::shared_ptr<Object> player);

	virtual bool isGuarded();
	virtual void setGuarded();
	virtual void setUnguarded();

	virtual std::string getAction();
	virtual void setAction(std::string newAction);
	virtual void appendAction(std::string appAction);

	virtual void severTies();

	virtual bool canMove();

	virtual void consumePotion(std::shared_ptr<Object> myPotion);

	virtual std::string getPotionName();
	virtual int getHealthEffect();

	virtual int getAttackEffect();
	virtual int getDefenseEffect();

	virtual void setAttackEffect(int value);
	virtual void setDefenseEffect(int value);

	virtual void setNextPotion(std::shared_ptr<Object> myPotion);

	virtual std::vector<int> potionBuffers();

	virtual void setKnown();

	virtual void endTurnEffect();

	//returns a shared pointer:
	//1: the enemy passed in if it is still alive
	//2: the gold dropped by a human or merchant, if enemy is slain
	//2b: in other cases enemy slain will return a reset shared pointer (nullptr)
	virtual std::shared_ptr<Object> attackEnemy(std::shared_ptr<Object> enemy);
	virtual bool receiveDmg(int dmg);

	virtual void pickPocket();

	virtual bool attackPlayer(std::shared_ptr<Object> player);

	virtual void resetStatic();

	void newTurn();
	bool turnCompleted();
};

#endif
