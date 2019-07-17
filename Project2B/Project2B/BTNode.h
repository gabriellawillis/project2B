//Project2

#ifndef BTNODE_H
#define BTNODE_H

#include <string>

class BTNode
{
public:
	BTNode(BTNode* leftChild, BTNode* rightChild, char data);

	char getLetter();
	char getData();
	void setData(char);

	BTNode *left, *right;

	char data;

private:

};

#endif // !BTNODE_H