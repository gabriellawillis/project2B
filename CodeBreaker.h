#pragma once
#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

struct BTNode {
	/*Binary tree node structure has a data element that will the the letter
	and 2 pointers; one to the left subtree and one to the right subtree*/
	char data;
	BTNode* left, * right;

	BTNode(BTNode* leftChild, BTNode* rightChild, char letter) {
		//Left and right child pointers will default to null
		data = letter;
		left = NULL;
		right = NULL;
	}
};

class CodeBreaker {
	/*CodeBreaker class will build the binary tree, map the morse code tree path,
	decode a morse code string, and encoded an english string*/
public:
	CodeBreaker();
	//Creates an empty binary tree
	void build(ifstream& textfile);
	//Builds the binary tree and morseMap from the morse code textfile
	string decode(string code);
	//Decodes a morse code string to an english string
	string encode(string word);
	//Encodes an english string to a morse code string
	char findLetter(string morse, BTNode* current);
	/*Follows the path in the morse binary tree using the to find the 
	morse characters to find the letter represented by the characters*/

private:
	BTNode* root;
	//The original root used to build the binary tree
	map<char, string> morseMap;
	//The morse map used to encode the english strings

	void buildBT(char alpha, string element, BTNode* newRoot);
	//Builds the binary tree from the morse code textfile
};

#endif 