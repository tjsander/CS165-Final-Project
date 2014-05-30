/****************************************************************
* Author: Travis Sanders
* Date Created: 03/13/14
* Last Modification Date: 03/16/14
* Lab/Project#: FINAL PROJECT
* Filename: final_fantasy.h
*
* Overview: Simple RPG objects
*
*****************************************************************/

#include <vector>
#include <string>

class Creature 				// #24 Class declaration
{ 
private:
	int strength; 			// How much damage we can inflict 
	int hitpoints; 			// How much damage we can sustain
	int defense;			// How much damage we can nullify
	//int intelligence;		// How much magic damage we can inflict
	//int mdef;				// How much magic damage we can nullify
	std::string name;		// The name of the creature
public: 
	Creature();							// #32 Default constructor
	Creature(int newStrength, int newHit, int newDef);
	~Creature();						// #32 Destructor
	Creature(const Creature &other);	// #32 Copy constructor
	void setStrength(int x);
	void setHitpoints(int x);
	void setDefense(int x);
	void setName(std::string x);
	std::string getName();
	int getDefense();
	int getHitpoints();
	int getStrength();
	int attacksFor();				//Creature deals damage.
	void takeDamage(int damage);	//Creature receives damage.
	//void takeMagicDamage();
	//bool alive = true;
};

class Player : public Creature{		// #36 Inheritance
private:
	std::vector<std::string> items;	// #31 Vector
public:
	Player();
	void level_up();
	//Player(Player &other);
	int attacksFor();

	Player operator++()				// #33 Overoloaded operator
	{
		std::cout << getName() << " LEVELED UP! STR+5, DEF+5, HP* 1.2" << std::endl;
		setStrength(getStrength() + 5);
		setDefense(getDefense() + 5);
		setHitpoints(getHitpoints() * 1.2);
		return *this;
	}
};

class Monster : public Creature{
public:
	Monster(std::string name);
	int attacksFor();
};

/*	Starts a fight between a player and monster.	*/
void fight(Player pc, Monster mob);

/*	END OF FILE	*/