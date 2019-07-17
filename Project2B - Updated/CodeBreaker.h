#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

struct BTNode {
	char data;
	BTNode *left, *right;

	BTNode(BTNode* leftChild, BTNode* rightChild, char letter) {
		data = letter;
		left = NULL;
		right = NULL;
	}
};

class CodeBreaker {
public:
	CodeBreaker();
	void build(ifstream &textfile);
	string decode(string code);
	string encode(string word);
	char findLetter(string morse, BTNode *current);

private:
	BTNode* root;
	map<char, string> morseMap;

	void buildBT(char alpha, string element, BTNode *newRoot);
};

#endif