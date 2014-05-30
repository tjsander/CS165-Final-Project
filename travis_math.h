/****************************************************************
* Author: Travis Sanders
* Date Created: 03/13/14
* Last Modification Date: 03/16/14
* Lab/Project#: FINAL PROJECT
* Filename: travis_math.h
*
* Overview: Contains binary math functions, idiot-proof "get" functions
*			a homebrew random number gen, swap template, and capslock function.
*
*****************************************************************/

/*	Header file, requirement #29	*/
#include <string>
/*	Asks the user for an int and then prints the number in binary.	*/
void print_binary();

/*	Prints a binary representation of given int using a fancy STL stack.	*/
void print_binary(int x);

/*	Prints the two's complement of a given int.	
	I was going to change this to use vectors, but I think a
	static array works well for a number with known bits.	*/
void print_twoscomp8(int x);

/*	Returns true if user passes a quiz.	*/
bool binary_quiz();
/*	Returns true if user passes a quiz.	*/
bool twoscomp_quiz();

/*	I'm reusing this function from an assignment because 
	I have yet to discover a more elegant way of idiot-proofing UI, 
	thereby reducing bugs at runtime. */		
int get_int();
std::string get_word();
char get_char();

/*	#37 Polymorphic swap function.	*/
template <typename T>
void swap_stuff(T &one, T &two) {
	T three;
	three = one;
	one = two;
	two = three;
}

namespace sandetra{
/*	In the second week of class I thought one of the assignments was to
	code my own random number generator.	*/
	int rand_int(int min, int max);

	/* Returns captialized version of string. */
	std::string capslock(std::string s);
}

/*	END OF FILE	*/