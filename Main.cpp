#include "BTNode.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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

	if (morse.size() == 0) {
		return current->data;
	}

	else if (morse.at(0) == '.') {
		return findLetter(morse.substr(1), current->left);
	}
	else {
		return findLetter(morse.substr(1), current->right);
	}
};

string decode(string code, BTNode *root) {
	string decodedPhrase = "";
	string morse;

	stringstream codedPhrase(code);

	while (codedPhrase >> morse) {
		decodedPhrase += findLetter(morse, root);
	}

	return decodedPhrase;
}

string encode(string word, map<char, string> myMap) {
	string encodedPhrase = "";
	for (int i = 0; i < word.size(); i++) {
		encodedPhrase += (myMap[word[i]] + " ");
	}

	return encodedPhrase;
}

void main()
{
	ifstream iStream;
	iStream.open("input.txt");

	BTNode *root = new BTNode(NULL, NULL, NULL);
	map<char, string> morseMap;
	char letter;
	string temp;
	string morse = "";

	//build BSTree and map
	for (int i = 0; i < 26; i++) {
		iStream >> temp;
		letter = temp[0];
		morse = temp.substr(1);

		buildBT(letter, morse, root);
		morseMap[letter] = morse;
	}

	iStream.close();

	cout << decode(".... . _.__", root) << endl;

	cout << encode("hey", morseMap) << endl;

	system("pause");
}