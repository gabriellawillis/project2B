#include "CodeBreaker.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

void main()
{
	ifstream iStream("input.txt");

	CodeBreaker myCodeBreaker;

	myCodeBreaker.build(iStream);

	cout << myCodeBreaker.decode(".... . ._.. ._.. ___") << endl;

	cout << myCodeBreaker.encode("hello") << endl;

	system("pause");

}