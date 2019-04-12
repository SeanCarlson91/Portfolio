#pragma once
//Demonstration program for the Tree template class.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "BinTree.h"
#include "BinTree.cpp"
using namespace std;

int main()
{
	//build the dialogue tree to 3 levels. I'm going with the famous scene from Pulp Fiction.
	BinTree <string> tree("What Does Marsellus Wallace look like?");
	TreeNode<string>*  root = tree.getRoot();


	root->setLeft("What?");
	root->setRight("What?");
	root->getLeft()->setLeft("What country you from?");
	root->getLeft()->setRight("What ain't no country I ever heard of. They speak english in what?");
	root->getRight()->setLeft("What country you from?");
	root->getRight()->setRight("ENGLISH MOTHAFUCKA DO YOU SPEAK IT!?");//I didn't write the script so don't blame me for the F-bomb if it bothers you.
	
	cout << "    "<<root->getData() << endl;
	cout << "  "<<root->getLeft()->getData()<<"   "<< root->getRight()->getData() << endl;
	cout << root->getLeft()->getLeft()->getData()<<" ";
	cout << root->getLeft()->getRight()->getData() << " ";
	cout << root->getRight()->getLeft()->getData() << " ";
	cout << root->getRight()->getRight()->getData() << " ";
	cout << endl;
	return 0;
}