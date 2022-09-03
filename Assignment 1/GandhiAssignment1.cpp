#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	
	int count = 1;
	
	cout << "Welcome to the sample C++ program\n";
	
	// show all command line arguments
	for (int i = 0; i < argc; i++)
			cout << "argv[" << i << "] = " << argv[i] << endl;
	
	// if no argument was given. prompt the user
	if (argc == 1) {
		cout << "Enter number to repeat: ";
		cin >> count;
	} else {
		count = atoi(argv[1]);
	}
	
	// show line a few times
	for (int i = 0; i < count; i++)
		cout << "C++ is fun !\n";
}
