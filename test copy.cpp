#include <iostream>

class Creature {
public:
	int getDamage() {
		return damage;
	}

	Creature() {
		damage = 10;
	}
private:
	int damage;
};

Creature* returnCreaturePtr()
{
	Creature* creaturePointer = new Creature();
	return creaturePointer;
}

int main() {
	Creature c;
	c = returnCreaturePtr();
	c.getDamage();

	return 0;
	
}