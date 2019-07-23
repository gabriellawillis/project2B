#include "CodeBreaker.h"
using namespace std;


CodeBreaker::CodeBreaker() {
	/*Contruct empty binary tree*/
	root = new BTNode(NULL, NULL, NULL);
}

void CodeBreaker::build(ifstream& textfile) {

	//Create placeholder and iterative values
	char letter;
	string temp;
	string morse;

	//build BSTree and map by iterating through the number of letters in the alphabet
	for (int i = 0; i < 26; i++) {
		textfile >> temp;
		letter = temp[0];
		morse = temp.substr(1);

		//Build the binary tree and the morseMap for each letter
		buildBT(letter, morse, root);
		//morseMap will allow for easy recall when encoding the phrase
		morseMap[letter] = morse;
	}
}

void CodeBreaker::buildBT(char alpha, string element, BTNode* newRoot) {
	/*Logic used to populate binary tree*/

	if (element.length() < 1) {
		//If the length is 0 then we have already found the location where the current letter will go
		return;
	}

	if (element.length() == 1) {
		/*when the length of the morse path is 1, this tells us that the node will
		be placed at the location found*/
		//The "." tells the program to go left in the tree
		if (element == ".") {
			if (!newRoot->left) {
				//If the left child is empty, create a new node with the current letter
				newRoot->left = new BTNode(NULL, NULL, alpha);
			}
			//If the left child is not empty set the data equal to the current letter
			newRoot->left->data = alpha;
		}

		else if (element == "_") {
			//The "_" tells the program to go right in the tree
			if (!newRoot->right) {
				//If the right child is empty, create a new node with the current letter
				newRoot->right = new BTNode(NULL, NULL, alpha);
			}
			//If the right child is not empty set the data equal to the current letter
			newRoot->right->data = alpha;
		}

		return;
	}

	for (int j = 0; j < element.length(); j++) {
		if (element[j] == '.') {
			//The "." tells the program to go right in the tree
			if (!newRoot->left) {
				//If there is no current left child, create a new empty node
				newRoot->left = new BTNode(NULL, NULL, NULL);
			}
			//Call the function recursively with newfound left child
			buildBT(alpha, element.substr(j + 1), newRoot->left);
		}
		else if (element[j] == '_') {
			if (!newRoot->right) {
				//If there is no current right child, create a new empty node
				newRoot->right = new BTNode(NULL, NULL, NULL);
			}
			//Call the function recursively with newfound right child
			buildBT(alpha, element.substr(j + 1), newRoot->right);
		}

		return;
	}
}

char CodeBreaker::findLetter(string morse, BTNode* current) {
	/*Iterates through morse string recursively and follows the path in the
	already built morse binary tree to find the letter represented in the morse code*/
	if (morse.size() == 0) {
		//When the morse string length is zero we have found the letter in the tree
		return current->data;
	}

	else if (morse.at(0) == '.') {
		/*If the morse string has "." as the first character follow the left
		subtree by calling the findLetter function recursively with morse string sans the first
		character and the left child node*/
		return findLetter(morse.substr(1), current->left);
	}
	else {
		/*If the morse string has "_" as the first character follow the rightt
		subtree by calling the findLetter function recursively with morse string sans the first
		character and the right child node*/
		return findLetter(morse.substr(1), current->right);
	}
};

string CodeBreaker::decode(string code) {
	/*This function will take a morse code string and find the enlish equivalent*/
	//Create a decodedPhrase to add letters to
	string decodedPhrase = "";
	//Create a morse string to read symbols from
	string morse;
	//Read in the code to a string stream
	stringstream codedPhrase(code);


	while (codedPhrase >> morse) {
		/*While there is still morse code left to be read, contrinue to decode*/
		//Uses the findLetter function to add a letter to the decodedPhrase
		decodedPhrase += findLetter(morse, root);
	}

	//Return the full decoded phrase
	return decodedPhrase;
}

string CodeBreaker::encode(string word) {
	/*Returns the english word encoded in morse code*/
	//Create empty string for encodedPhrase to add symbols to
	string encodedPhrase = "";
	for (int i = 0; i < word.size(); i++) {
		//Use morse map to add each letter in morse code form to the encodedPhrase string
		encodedPhrase += (morseMap[word[i]] + " ");
	}

	//Return entire encodedPhrase
	return encodedPhrase;
}