#pragma once
//Demonstration program for the Tree template class.

#include <iostream>
#include <string>
#include "BinTree.h"
#include "BinTree.cpp"
using namespace std;

int main()
{
	//build the tree to 3 levels.
	BinTree <string> tree("Level 0");
	TreeNode<string>*  root = tree.getRoot();


	root->setLeft("Level 1 Left ");
	root->setRight("Level 1 Right");
	root->getLeft()->setLeft("Level 2 Left");
	root->getLeft()->setRight("Level 2 Right");
	root->getRight()->setLeft("Level 3 Left");
	root->getRight()->setRight("Level 3 Right");

	//Output
	cout << "                           "<<root->getData() << endl;
	cout << "            "<<root->getLeft()->getData()<<"            "<< root->getRight()->getData() << endl;
	cout <<"      "<< root->getLeft()->getLeft()->getData()<<" ";
	cout <<"                        "<< root->getLeft()->getRight()->getData() << " " << endl;
	cout << root->getRight()->getLeft()->getData() << " ";
	cout <<"                                   "<< root->getRight()->getRight()->getData() << " ";
	cout << endl;


	return 0;
}