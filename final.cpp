/****************************************************************
* Author: Travis Sanders
* Date Created: 03/13/14
* Last Modification Date: 03/16/14
* Lab/Project#: FINAL PROJECT
* Filename: final.cpp
*
* Overview: Simple RPG using final_fantasy.h, travis_math.h and battleships.h
*
*	NOTE: MOST PROJECT REQUIREMENTS FOUND IN travis_math.cpp
*****************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include "travis_math.h"
#include "battleships.h"
#include "final_fantasy.h"

using std::cout;
using std::cin;
using std::endl;

class Node {
public:
	Node();
	Node(char name);
	void set_north(Node *x);
	void set_south(Node *x);
	void set_east(Node *x);
	void set_west(Node *x);
/* Similar to a search function. Moves user to a new node. */
	Node move();
	char get_name();
	void print();
	// Returns the number of possible paths.
	int paths();
private:
	char room;
	Node *north;
	Node *south;
	Node *east;
	Node *west;
};
char get_direction();
char get_grade();
void maze(Node start);
void game1();
void game2();

struct Spell {						// #23 Struct
	int damage;
	int elemental; 	// 0=null 1 =fire, 2=earth, 3=water, 4=air
};

int main(int argc, char *argv[]) 	// #22 Command-line arg (used for file io)
{
	srand(time(NULL));
	if (argv[1]) {					// Plan is to use this to read / encode character sheets.
		cout << "Input " << argv[1] << " accepted!!" << endl;	// Not enough time to finish.
		try {						// #38 Exceptions
			std::ifstream ifs;		// #34 File IO
			ifs.open(argv[1]);
			cout << "Attempting to open " << argv[1] << endl;
			
			std::string forgetme;
			ifs >> forgetme;
			if (forgetme != "76616c6964617465") {	// Validation code
				ifs.close();
				throw forgetme;
			}
			while (ifs >> forgetme) {
				cout << forgetme << " ";
			}
			cout << endl << "Closing file" << argv[1] << endl;
			ifs.close();
		}
		catch (...) {
			cout << "Sorry, that file was not acceptable." << std::endl;
			cout << "Continuing with program." << endl;
		}
	} else {
		cout << "No file input from command line........" << endl;
	}
	// for (int i = 0; i < 30; i++) {
	// 	print_binary(i);
	// }

	// cout << "The binary representation of INT_MAX: " << endl;
	// print_binary(INT_MAX);

	// cout << "The values of all 8-bit twos complement numbers: " << endl;
	// for (int i = SCHAR_MIN; i < SCHAR_MAX; i++) {
	// 	print_twoscomp8(i);
	// }

	// cout << "How many random numbers should I generate?" << endl;
	// int how_many;
	// how_many = get_int();
	// for (int i=0; i<how_many; i++) {
	// 	cout << sandetra::rand_int(0,1000) << " ";
	// }
	// cout << endl;

	// int i = 9;
	// int j = 10;
	// cout << "i= " << i << " and j=" << j << endl;
	// swap_stuff(i,j);
	// cout << "i= " << i << " and j=" << j << endl;

	// double k = 9.6;
	// double l = 10.4;
	// cout << "k= " << k << " and l=" << l << endl;
	// swap_stuff(k,l);
	// cout << "k= " << k << " and l=" << l << endl;

	cout << endl << "WELCOME TO THE FINAL... FANTASY" << endl << endl;

	Player h = Player();

	cout << endl << "Your journey begins..................." << endl;
	Monster m = Monster("Gremlin");
	fight(h,m);
	//h.level_up();
	++h;
	cout << h.getName() << " continues along the journey..." << endl;

	game1();	//First maze

	Monster w = Monster("Wizard");
	w.setStrength(25);
	Monster *wizardclone;					// #27 Pointer to object.
	wizardclone = &w;
	wizardclone->setName("WizardCLONE");
	fight(h,*wizardclone);

	Spell fire;
	fire.damage = 10;
	fire.elemental = 1;

	cout << "The defeated wizard is casting a huge fireball..." << endl;
	cout << h.getName() << " attempts to control wizard's spell using a pointer..." << endl;
	Spell *attempt;
	attempt = &fire;						// #26 Pointer to struct
	cout << "Your new spell is able to do " << attempt->damage << " damage!" << endl;
	cout << "You cast the spell back at the Wizard....." << endl;
	cout << "IT'S SUPER EFFECTIVE. The Wizard is now SUPER DEAD." << endl;

	game2();	//Second maze

	cout << "'Your pointers are mighty indeed,' says a voice from beyond the grave." << endl;
	cout << "'But can you sink my BATTLESHIPS?!'" << endl;
	reset_board();
	battleship_game();
	cin.ignore(10000, '\n');
	cout << "Thank you for playing!" << endl;
	cout << "Wasn't that AWESOME?" << endl;
	cout << "What grade would you give this?:";	
	get_grade();	// #39
	++h;
	cout << "NICE. Thank you for playing." << endl;
	return 0;
}

/*	Gets a direction char from user. */
char get_direction() 
{
	char input = get_char();
	if (input == 'E' || input == 'e') return 'E';
	else if (input == 'N' || input == 'n') return 'N'; 
	else if (input == 'S' || input == 's') return 'S'; 
	else if (input == 'W' || input == 'w') return 'W'; 
	else {
		std::cout << "Sorry, that's not a valid direction." << std::endl;
		return get_direction();
	}
}

Node::Node()
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	room = 'X';
}

Node::Node(char name) 
{
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	room = name;
}

void Node::set_north(Node *x) 			// MORE POINTERS TO OBJECTS!
{			
	north = x;
	if (x->south == NULL) {
		x->set_south(this);
	}
}

void Node::set_south(Node *x) 
{
	south = x;
	if (x->north == NULL) {
		x->set_north(this);
	}
}

void Node::set_east(Node *x) 
{
	east = x;
	if (x->west == NULL) {
		x->set_west(this);
	}
}

void Node::set_west(Node *x) 
{
	west = x;
	if (x->east == NULL) {
		x->set_east(this);
	}
}

/* Similar to a search function. Moves user to a new node. */
Node Node::move()
{
	print();
	char input = get_direction();
	if (input == 'N' && north != NULL) {
		return *north;
	} else if (input == 'S' && south != NULL) {
		return *south;
	} else if (input == 'E' && east != NULL) {
		return *east;
	} else if (input == 'W' && west != NULL) {
		return *west;
	} else {
		cout << "Sorry, you can't walk through walls like Kitty Pryde." << endl;
		return move();
	}
}

char Node::get_name()
{
	return room;
}

void Node::print()
{
	cout << "You are in room " << room 
		<< " of a maze of twisty little passages, all alike." << endl;
	if (paths() == 1) {
		cout << "You have reached a dead end. Only one direction to go: ";
	} else {
		cout << "You can go";
	}
	int p = paths();
	if (north != NULL) {
		cout << " north";
		if (p > 1) cout << " or";
	}
	if (south != NULL) {
		cout << " south";
		if (east != NULL || west != NULL) cout << " or";
	}
	if (east != NULL) {
		cout << " east";
		if (west != NULL) cout << " or";
	}
	if (west != NULL) {
		cout << " west";
	}
	cout << "." << endl;
}

// Returns the number of possible paths.
int Node::paths()
{
	int count = 0;
	if (north != NULL) {
		count++;
	}
	if (south != NULL) {
		count++;
	}
	if (east != NULL) {
		count++;
	}
	if (west != NULL) {
		count++;
	}
	return count;
}

void maze(Node start, Node end)
{
	Node n = start;
	while (n.get_name() != end.get_name()) {
		n = n.move();
	}
	//cout << "Congratulations! You made it to the end!" << endl;
}

void game1()
{
	Node a = Node('A');
	Node b = Node('B');
	Node c = Node('C');
	Node d = Node('D');
	Node e = Node('E');
	Node f = Node('F');
	Node g = Node('G');
	Node h = Node('H');
	Node i = Node('I');
	Node j = Node('J');
	Node k = Node('K');
	Node l = Node('L');
	a.set_south(&e);
	a.set_east(&b);
	e.set_south(&i);
	i.set_east(&j);
	b.set_south(&f);
	f.set_east(&g);
	g.set_north(&c);
	c.set_east(&d);
	g.set_south(&k);
	g.set_east(&h);
	h.set_south(&l);
	maze(a,g);
}

void game2()
{
	Node a = Node('A');
	Node b = Node('B');
	Node c = Node('C');
	Node d = Node('D');
	Node e = Node('E');
	Node f = Node('F');
	Node g = Node('G');
	Node h = Node('H');
	Node i = Node('I');
	Node j = Node('J');
	Node k = Node('K');
	Node l = Node('L');
	a.set_south(&e);
	a.set_east(&b);
	e.set_south(&i);
	i.set_east(&j);
	b.set_south(&f);
	f.set_east(&g);
	g.set_north(&c);
	c.set_east(&d);
	g.set_south(&k);
	g.set_east(&h);
	h.set_south(&l);
	maze(g,l);
}

char get_grade() 
{
	char input = get_char();
	if (input == 'A' || input == 'a') return 'A';
	else {
		std::cout << "Sorry, that's not a valid grade." << std::endl;
		return get_grade();
	}
}

/*	END OF FILE	*/