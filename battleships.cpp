/************************************
*
* BATTLESHIP(S)
* Travis J. Sanders
* 2014.02.09
* 
*************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <limits.h>
#include "battleships.h"

using namespace std;

int board[10][10];					// #20 Tons of 2d array work here.
int remaining_targets = 17;

bool game_over = false;

void place_ship(int size);
void place_random_ship(int size);
void computer_ships();
void player_ships();
void attack();
void hit(int x, int y);
bool is_valid(int size, int x, int y, int horizvert);
bool check_win();
void print_game();
void print_game_secret();
int numb(string s);

/* Converts letter inputs into numbers. */
int numb(string s) 
{
	if (s == "A") return 0;
	if (s == "B") return 1;
	if (s == "C") return 2;
	if (s == "D") return 3;
	if (s == "E") return 4;
	if (s == "F") return 5;
	if (s == "G") return 6;
	if (s == "H") return 7;
	if (s == "I") return 8;
	if (s == "J") return 9;
	else return -1;
}

/* Converts lowercase characters to uppercase characters */
string capslock(string s) 
{
	string r;
	for (int i=0; i<s.length(); i++) 
	{
		r += toupper(s[i]);
	}
	return r;
}

/* Resets the global game board. Easier than localizing the array to the game. */
void reset_board() 
{
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			board[i][j] = 0;
		}
	}
	remaining_targets=17;
}

/* Allows player to place a ship. (Currently unused functionality.) */
void place_ship(int size) 
{
	string xstring;
	int y;
	int x;
	int horizvert;
	do {
		cout << "Place your ship [" << size << "]" << endl;
		cout << "Please enter a column letter: ";
		cin >> xstring;
		x = numb(xstring);
		cout << "Please enter a row number: ";
		cin >> y;
		cout << "Placing... " << x << "-" << y << endl;
		cout << "Enter 0 for horizontal or 1 for vertical: ";
		cin >> horizvert;
	} while (!is_valid(size, x, y, horizvert));

	if (horizvert == 0) {
		for (int i=x; i<x+size; i++) {
			board[i][y] = 1;
		}
	} else if (horizvert == 1) {
		for (int i=y; i<y+size; i++) {
			board[x][i] = 1;
		}
	}
	print_game_secret();
}

/* Places a ship in a random spot. */
void place_random_ship(int size) 
{
	int y;
	int x;
	int horizvert;
	do {
		x = rand() % 10;
		y = rand() % 10;
		horizvert = rand() % 2;
	} while (!is_valid(size, x, y, horizvert));
	if (horizvert == 0) {
		for (int i=x; i<x+size; i++) {
			board[i][y] = 1;
		}
	} else if (horizvert == 1) {
		for (int i=y; i<y+size; i++) {
			board[x][i] = 1;
		}
	}
	//cout << "Ship " << size << " placed at " << x << "-"<< y 
	//<< " (" << horizvert << ")" << endl;
	//print_game_secret();
}

/* Randomly arranges the board. */
void computer_ships() 
{
	place_random_ship(5);
	place_random_ship(4);
	place_random_ship(3);
	place_random_ship(3);
	place_random_ship(2);
}

/* Checks to see if a ship placement is legal. */
bool is_valid(int size, int x, int y, int horizvert) 
{
	if (horizvert == 0) {
		//cout << "Sorry, that appears to be out of bounds." << endl;
		if (x+size > 9) {
			//cout << "Sorry, that appears to be out of bounds." << endl;
			return false;
		}
		for (int i=y; i<x+size; i++) {
			if (board[i][y] == 1) {
				//cout << "Sorry, you cannot place a ship on a ship." << endl;
				return false;
			}
		}
	} else if (horizvert == 1) {
		if (y+size > 9) {
			//cout << "Sorry, that appears to be out of bounds." << endl;
			return false;
		}
		for (int i=y; i<y+size; i++) {
			if (board[x][i] == 1) {
				//cout << "Sorry, you cannot place a ship on a ship." << endl;
				return false;
			}
		}
	}
	return true;
}

/* Checks to see if win conditions have been met. */
bool check_win() 
{
	for (int y=0; y<10; y++) {
		for (int x=0; x<10; x++) {
			if (board[y][x]==1) return false;
		}
	}
	return true;
}

/* Prints the game board with hidden information hidden. */
void print_game() 
{
	cout << "  A B C D E F G H I J" << endl;
	for (int y=0; y<10; y++) {
		cout << y;
		for (int x=0; x<10; x++) {
			int check = board[x][y];
			if (check == 2) {
				cout << " X";
			}
			if (check == 3) {
				cout << " O";
			}
			if (check==0 || check==1) {
				cout << " .";
			}
		}
		cout << endl;
	}
	cout << endl;
}

/* Prints the game with all information revealed. (Debug) */
void print_game_secret() 
{
	cout << "  A B C D E F G H I J" << endl;
	for (int y=0; y<10; y++) {
		cout << y;
		for (int x=0; x<10; x++) {
			int check = board[x][y];
			if (check == 2) {
				cout << " X";
			}
			if (check == 3) {
				cout << " O";
			}
			if (check == 0) {
				cout << " .";
			}
			if (check == 1) {
				cout << " B";
			}
		}
		cout << endl;
	}
	cout << endl;
}

/* Player turn. */
void attack() 
{
	string x;
	int y;
	int xint;
	bool again = false;
	do {
		cout << "Please enter a column letter: ";
		cin >> x;
		x = capslock(x);
		xint = numb(x);
	} while (xint < 0 || xint > 9);

	cout << "Please enter a row number: ";
	cin >> y;
	while (!cin || y < 0 || y > 9) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please enter a row number: ";
		cin >> y;
	}

	cout << "Attacking " << x << "-" << y << endl;
	if (board[xint][y] == 1) {
		cout << "HIT!!!!!! YOU GET ANOTHER TURN!" << endl;
		board[xint][y] = 2;
		hit(xint, y);
		print_game();
		if (check_win()) {
			cout << "WIN WIN WIN! YOU SUNK MY BATTLESHIPS!" << endl;
			game_over = true;
		} else attack();
	} else {
		cout << endl << "MISS! You lose a turn.";
		cout << "The enemy still lives...." << endl;
		board[xint][y] = 3;
		print_game();
	}
}

/* To make the game easier: Announces how many targets are surrounding the hit. */
void hit(int x, int y) 
{
	int count=0;
	for (int i=x-1; i<x+2; i++) {
		for (int j=y-1; j<y+2; j++) {
			if (board[i][j] == 1) {
				count++;
			}
		}
	}
	remaining_targets--;
	cout << "The shockwave from the explosion reveals " << count << endl
	<< "unexploaded ship segments in the adjacent squares." << endl
	<< "There are " << remaining_targets << " targets remaining." << endl << endl;
}

/* Allows a player to set the position of ships. Currently unused in 1P game. */
void player_ships() 
{
	place_ship(5);
	place_ship(4);
	place_ship(3);
	place_ship(3);
	place_ship(2);
}

/* Starts a new game of BATTLESHIPS */
void battleship_game() 
{
	srand(time(NULL));
	cout << endl << endl << "******BATTLESHIPS******" << endl << endl;
	computer_ships();
	//print_game_secret();
	print_game();
	int turns = 25;
	while (turns > 0 && !game_over) {
		attack();
		turns--;
		cout << "You have " << turns << " turns remaining!" << endl;
	}
	print_game_secret();
}