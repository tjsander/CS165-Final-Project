/****************************************************************
* Author: Travis Sanders
* Date Created: 03/13/14
* Last Modification Date: 03/16/14
* Lab/Project#: FINAL PROJECT
* Filename: travis_math.cpp
*
* Overview: Most project requirements fulfilled in this file.
*
*****************************************************************/

#include <iostream>
#include <stack>
#include "travis_math.h"
#include <string>
#include <sstream>
#include <vector>
#include <math.h> 
#include <limits.h>

using std::cout;
using std::cin;
using std::endl;

void print_binary(int x)				// #1 Binary
{
	//cout << x << " in binary notation is:\t";		
	std::stack<int> q;					// #35 STL!
	if (x == 0) q.push(0);				// #7 Conditional; #8 bitwise.
	while (x > 0) {						// #9 Loop.
		q.push(x % 2);
		x = x / 2;
	}
	while (!q.empty()) {
		cout << q.top();				// #4 Simple output.
		q.pop();
	}
	//cout << endl;
}

void print_twoscomp8(int x)					// #2 Two's complement; #16 Pass by value
{
	if (x > SCHAR_MAX || x < SCHAR_MIN) {	// #3 Macro; #11 Also avoids logic errors / overflows.
		cout << "Sorry! That's not possible in 8 bits." << endl;
		return;
	}
	//cout << x << " in twos complement is:\t";
	int complement[8];
	if (x > 0) {			// Positve
		complement[0] = 0;
		int it = 7;
		while (it > 0) {
			complement[it] = x % 2;
			x = x / 2;
			it--;
		}
	} else if (x < 0) {		// Negative

		x = x * -1;
		int it = 7;
		while (it > 0) {
			complement[it] = 1 - x % 2;
			x = x / 2;
			it--;
		}
		//	Add 1.
		it = 7;
		while (complement[it] == 1) {
			complement[it] = 0;
			it--;
		}
		complement[it] = 1;
		complement[0] = 1;

	} else if (x == 0) {	// Zero
		for (int i=0; i<8; i++) {
			complement[i] = 0;
		}
	}

	int i = 666;
	for (int i = 0; i < 8; i++) {
		if (i == 4) cout << " ";			// #15 OK to reuse variable name i in new scope.
		cout << complement[i];
	}
	if (i != 666) {
		cout << "WARNING, I SHOULD NEVER SEE THIS." << endl;
	}
	//cout << endl;							// #11 Don't forget a semicolon: syntax error.
}

namespace sandetra{							// #28 Namespace #29 Header #30 Makefile
	long seed =210980654321;				// This seed seems to work reasonably well (some get stuck).
	int rand_int(int min, int max) 			// #10 Random number generator (my own!)
	{		
		long random = (seed / 1000) % 1000000;		//Middle square method
		int returnme = (random %( max - min )) + min;
		seed = (random*random);	
		return returnme;
	}

	/* Converts lowercase characters to uppercase characters */
	std::string capslock(std::string s) 
	{
		std::string r;
		for (int i=0; i<s.length(); i++) 
		{
			r += toupper(s[i]);
		}
		return r;
	}
} 

void swap_stuff(int &one, int &two) {		// #16 Pass by reference.
	//implementation in header				// #37 Polymorphism
}

/*	#11 #12 Runtime Error prevention / Bug reduction	*/
int get_int()								// #13 Defined function
{
	std::stringstream ss;					// #14 Also functional decomposition
	std::string input;						// #18 String variable

	std::cout << "Please enter an integer: ";
	std::getline(std::cin, input);			// #5 Simple input
	
	//std::cout << "Input was: " << input << std::endl;
	ss << input;
	int return_me;
	if (ss >> return_me) {					// #6 Type casting from stringstream to int.
		return return_me;
	} else {
		std::cout << "FAILURE. That's an invalid input." << std::endl;
		return get_int();					// #19 Recursion	#20 2d array is in battleships.cpp
	}
}

void print_binary()
{
	print_binary(get_int());				// #17 Overloading functions.
}

/*	Takes a multi-dimensional array as pointer and returns a pointer
	to a reversed array.	*/
int* invert_array(int *input, int size)			// #25 Pointer to array
{
	int *output;
	output = new int[size];						// #21 Dynamically declared array
	for (int i=size-1; i > -1; i--) {
		output[i] = input[size-i];
	}
	return output;
}

void print_array(int *input, int size)
{
	for (int i=0; i<size; i++) {
		cout << input[i] << " ";
	}
	cout << endl;
}

bool binary_quiz() 
{
	int answer = rand() % 129;
	cout << "BINARY QUIZ: What is the integer value of unsigned ";
	print_binary(answer);
	cout << "?" << endl;
	if (get_int() == answer) {
		cout << "CORRECT!" << endl;
		return true;
	} else {
		cout << "Sorry, that's incorrect. The number was " << answer << endl;
		return false;
	}	
}

bool twoscomp_quiz() 
{
	int answer = 32 - rand() % 65;
	cout << "TWOSCOMP QUIZ: What is the integer value of signed ";
	print_twoscomp8(answer);
	cout << "?" << endl;
	if (get_int() == answer) {
		cout << "CORRECT!" << endl;
		return true;
	} else {
		cout << "Sorry, that's incorrect. The number was " << answer << endl;
		return false;
	}
}

char get_char() 
{
	std::stringstream ss;
	std::string input;
	//std::cout << "Please enter a character: ";
	std::getline(std::cin, input);
	//std::cout << "Input was: " << input << std::endl;
	ss << input;
	char return_me;
	if (ss >> return_me) {
		//std::cout << return_me << std::endl;
		return return_me;
	} else {
		std::cout << "FAILURE. That's an invalid input." << std::endl;
		return get_char();
	}
}

std::string get_word() 
{
	std::stringstream ss;
	std::string input;
	//std::cout << "Please enter a character: ";
	std::getline(std::cin, input);
	//std::cout << "Input was: " << input << std::endl;
	ss << input;
	std::string return_me;
	if (ss >> return_me) {
		//std::cout << return_me << std::endl;
		return return_me;
	} else {
		std::cout << "FAILURE. That's an invalid input." << std::endl;
		return get_word();
	}
}

// #22 #23 #26 #27 #34 #38 #39 :: final.cpp
// #24 #31 #32 #33 #36 :: final_fantasy.h

/*	END OF FILE #40	*/