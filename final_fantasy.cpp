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

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "travis_math.h"
#include "final_fantasy.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

//DEFAULT CREATURE CLASS
Creature::Creature() 			// #32 Default constructor.
{
	this->strength = 15;
	this->hitpoints = 30;
	this->defense = 5;
	//this->intelligence = 15;
	//this->mdef = 5;
	name = "NULL";
}

/* Defining my own copy constructor and then inheriting from it
was causing huge problems until I added 'const'. */
Creature::Creature(const Creature &other)	// #32 Copy constructor
{
	cout << "Copy magic has been invoked!" << endl;
	this->strength = other.strength;
	this->hitpoints = other.hitpoints;
	this->defense = other.defense;
	this->name = other.name;
}

Creature::~Creature() { }		// #32 Destructor

Creature::Creature(int newStrength, int newHit, int newDef) 
{
	strength = newStrength;
	hitpoints = newHit;
	defense = newDef;
	name = "Creature";
}

void Creature::setStrength(int x) 
{
	strength = x;
}

void Creature::setHitpoints(int x) 
{
	hitpoints = x;
}

void Creature::setDefense(int x) 
{
	defense = x;
}

void Creature::setName(string x)
{
	name = x;
}

std::string Creature::getName()
{
	return name;
}

int Creature::getDefense()
{
	return defense;
}
	
int Creature::getHitpoints()
{
	return hitpoints;
}

int Creature::getStrength()
{
	return strength;
}

int Creature::attacksFor()
{
	int damage;
	cout << name << " of strength " << strength << " does ";
	damage = (rand() % strength) + 1;
	cout << damage << " damage!" << endl;
	return damage;
}

void Creature::takeDamage(int damage)
{
	cout << name << "'s defense is " << defense << ". ";

	if (damage < defense) {
		cout << name << "'s defense is too strong! Damage nullified." << endl;
		return;
	}

	hitpoints = hitpoints - damage + defense;
	cout << name << " takes " << damage - defense << " damage. HP now at " << hitpoints << endl; 
	if (hitpoints <= 0) {
		cout << name << " has fallen!" << endl;
		//toggle_alive();
	}
}

// void Creature::takeMagicDamage() 
// {
// }

//PLAYER

Player::Player() : Creature()
{
	std::string input;
	cout << "New player character created. What is your name?" << endl;
	input = get_word();
	cout << "Your name has been entered as " << input << endl;
	setName(input);
	items.push_back("potion");
	items.push_back("potion");
	items.push_back("potion");
}

// Unnecessary, now that ++ operator has been overloaded.
void Player::level_up() 
{
	cout << getName() << " LEVELED UP! STR+5, DEF+5, HP* 1.2" << endl;
	setStrength(getStrength() + 5);
	setDefense(getDefense() + 5);
	setHitpoints(getHitpoints() * 1.2);
}

int Player::attacksFor()
{
	cout << getName() << " prepares to attack............" << endl;
	if (binary_quiz()) {
		int returnme = Creature::attacksFor() * 2;
		cout << "BINARY ATTACK. DAMAGE DOUBLES TO " << returnme << " DAMAGE!" << endl;
		return returnme;
	} else return Creature::attacksFor();
}

//Monster
Monster::Monster(std::string name) : Creature()
{
	setName(name);
}

int Monster::attacksFor() 
{
	if (rand() % 20 == 5) {
		int returnme = Creature::attacksFor() + 10;
		cout << "LUCKY SHOT: SUCKERPUNCH. DAMAGE INCREASES BY 10 FOR ";
		cout << returnme << " DAMAGE!" << endl;
		return returnme;
	} else return Creature::attacksFor();
}

void fight(Player p, Monster mob) 
{
	cout << "A WILD " << sandetra::capslock(mob.getName()) << " APPEAERS!" << endl;
	while (mob.getHitpoints() > 0 && p.getHitpoints() > 0) {
		mob.takeDamage(p.attacksFor());
		if (mob.getHitpoints() <= 0) {
			cout << mob.getName() << " has been defeated!" << endl;
			cout << p.getName() << " uses a potion to return to full health." << endl;
			p.setHitpoints(30);
			return;
		} else {
			if (rand() % 3 == 2) {
				cout << "You have a chance to parry the attack!" << endl;
				if (twoscomp_quiz()) {
					cout << "ATTACK SUCCESSFULLY PARRIED!" << endl;
				} else p.takeDamage(mob.attacksFor());
			} else {
				p.takeDamage(mob.attacksFor());
			}
			if (p.getHitpoints() <= 0) {
				cout << p.getName() << " has fallen! OH NO!!!!" << endl;	//Game over not implemented.
				cout << p.getName() << " uses a potion!" << endl;
				p.setHitpoints(15);
				return;
			}
		}
	}
}

/*	END OF FILE	*/