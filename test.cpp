
#include <iostream>
#include <math.h>  

using std::cout;
using std::cin;
using std::endl;

void print_square(int **input, int size);

//int size = 20;


/*	Takes an int array of some length, returns a square 2d array**.	
	Compiles, but causes bus error 10 at runtime when called.
	DO NOT USE.		*/
void square_array(int *input, int size) 
{
	int length = sqrt(size);
	int **output;
	*output = new int[length];
	for (int i=0; i<length; i++) {
		output[i] = new int[length];
	}
	int it = 0;
	for (int i=0; i<length; i++) {
		cout << "Length is " << length << endl;
		for (int j=0; j<length; j++) {
			cout << "Hello!";
			output[i][j] = input[it];
			it++;
		}
	}
}



void print_square(int **input, int size)
{
	int length = sqrt(size);
	for (int i=0; i<length; i++) {
		for (int j=0; j<length; j++) {
			cout << input[i][j];
		}
		cout << endl;
	}
}

int main() 
{
	int test[10];
	for (int i=0; i<10; i++) {
		test[i] = i;
	}
	int test3[3][3];
	for (int i=0;i<3;i++) {
		for (int j=0; j<3; j++) {
			test3[i][j]=i*j;
		}
	}
	//print_square(*test3, 3);
	print_array(test, 10);
	int *test2;
	cout << "Test 2=" << test2 << endl;
	test2 = test;
	cout << "Test 2=" << test2 << endl;
	print_array(test2, 10);

	test2 = invert_array(test, 10);

	print_array(test, 10);
	print_array(test2, 10);
	delete[] test2; //is this necessary?

	return 0;
}