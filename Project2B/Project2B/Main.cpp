//Project 2

#include "BTNode.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

void buildBT(char alpha, string element, BTNode *newRoot) {
	if (element.length() < 1) {
		return; //throw an error
	}

	if (element.length() == 1) {
		if (element == ".") {
			if (!newRoot->left) {
				newRoot->left = new BTNode(NULL, NULL, alpha);
			}
			newRoot->left->setData(alpha);
		}

		else if (element == "_") {
			if (!newRoot->right) {
				newRoot->right = new BTNode(NULL, NULL, alpha);
			}
			newRoot->right->setData(alpha);
		}

		return;
	}

	for (int j = 0; j < element.length(); j++) {
		if (element[j] == '.') {
			if (!newRoot->left) {
				newRoot->left = new BTNode(NULL, NULL, NULL);
			}
			buildBT(alpha, element.substr(j + 1), newRoot->left);
		}
		else if (element[j] == '_') {
			if (!newRoot->right) {
				newRoot->right = new BTNode(NULL, NULL, NULL);
			}
			buildBT(alpha, element.substr(j + 1), newRoot->right);
		}

		return;
	}
}

char findLetter(string morse, BTNode *current) {
	cout << "Morse is: " << morse << " at size " << morse.size() << endl;


	if (morse.size() == 0) {
		char l = current->data;
		cout << l << endl;
		return l;
	}

	else if (morse.at(0) == '.') {
		return findLetter(morse.substr(1), current->left);
	}
	else { // (morse[0] == '_') {
		return findLetter(morse.substr(1), current->right);
	}
};


////decode function
string decode(string code, BTNode *root) {
	string decodedPhrase = " ";
	string morse;

	stringstream codedPhrase(code); 

	while (codedPhrase >> morse) {
		char l = findLetter(morse, root);
		cout << "l is: " << l << endl;
		decodedPhrase += l;
	}
	
	return decodedPhrase;
}

void Print(BTNode* x)
{
	if (!x) return;

	Print(x->left);

	cout << x->data << endl;

	Print(x->right);
}

void main()
{
	ifstream iStream;
	iStream.open("input.txt");

	string temp;

	BTNode *root = new BTNode(NULL, NULL, NULL);
	map<char, string> morseMap;
	char letter;
	string morse = "";

	//build BSTree and map
	for (int i = 0; i < 26; i++) {
		iStream >> temp;
		letter = temp[0];
		morse = temp.substr(1);

		buildBT(letter, morse, root);
		//cout << "\nAdded " << letter << " " << morse << " to tree." << endl;
		morseMap[letter] = morse;
		//cout << "Added " << letter << " " << morseMap[letter] << " to map." << endl;
	}

	//system("pause");

	//Print(root);

	//system("pause");

  	string result = decode(".... . _.__", root); //hey

	cout << result << endl;

	system("pause");

}