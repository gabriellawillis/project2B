#include "CodeBreaker.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

void main()
{
	//Open the morse code file to be used to create the morse binary tree
	ifstream iStream;
	iStream.open("morse.txt");
	//Output an error message to user if file open issue occurs
	if (!iStream) {
		cout << "Unable to open file morse.txt";
		exit(1);
	}

	//Create a new CodeBreaker object
	CodeBreaker myCodeBreaker;

	//Construct the CodBreaker object with the morse file we read
	myCodeBreaker.build(iStream);
	//Decode will change a morse string into english
	cout << myCodeBreaker.decode(".... . ._.. ._.. ___") << endl;
	//Encode will change an english string into morse code
	cout << myCodeBreaker.encode("hello") << endl;

	system("pause");

}