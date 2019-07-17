#include "CodeBreaker.h"
using namespace std;


CodeBreaker::CodeBreaker() {
	root = new BTNode(NULL, NULL, NULL);
}

void CodeBreaker::build(ifstream &textfile) {

	char letter;
	string temp;
	string morse;

	//build BSTree and map
	for (int i = 0; i < 26; i++) {
		textfile >> temp;
		letter = temp[0];
		morse = temp.substr(1);

		buildBT(letter, morse, root);
		morseMap[letter] = morse;
	}
}

void CodeBreaker::buildBT(char alpha, string element, BTNode *newRoot) {
	if (element.length() < 1) {
		return; 
	}

	if (element.length() == 1) {
		if (element == ".") {
			if (!newRoot->left) {
				newRoot->left = new BTNode(NULL, NULL, alpha);
			}
			newRoot->left->data = alpha;
		}

		else if (element == "_") {
			if (!newRoot->right) {
				newRoot->right = new BTNode(NULL, NULL, alpha);
			}
			newRoot->right->data = alpha;
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

char CodeBreaker::findLetter(string morse, BTNode *current) {

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

string CodeBreaker::decode(string code) {
	string decodedPhrase = "";
	string morse;

	stringstream codedPhrase(code);

	while (codedPhrase >> morse) {
		decodedPhrase += findLetter(morse, root);
	}

	return decodedPhrase;
}

string CodeBreaker::encode(string word) {
	string encodedPhrase = "";
	for (int i = 0; i < word.size(); i++) {
		encodedPhrase += (morseMap[word[i]] + " ");
	}

	return encodedPhrase;
}
