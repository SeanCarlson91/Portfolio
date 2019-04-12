#pragma once
#include<cstdlib>
template<class T>
class BinTree; //forward declaration

template<class T>
class TreeNode
{
public:
	TreeNode(T theData, TreeNode<T>* left, TreeNode<T>* right)
		: data(theData), leftLink(left), rightLink(right) {}

	friend class BinTree<T>;
	TreeNode<T> *getRight();
	TreeNode<T> *getLeft();
	T getData();
	void setLeft(T item);
	void setRight(T item);
private:
	T data;
	TreeNode<T> *leftLink;
	TreeNode<T> *rightLink;
};


template<class T>
class BinTree
{
public:
	BinTree() : root(NULL) {}
	BinTree(T data);
	virtual ~BinTree();
	TreeNode<T> *getRoot();
	
	
private:
	void deleteSubtree(TreeNode<T>*& subTreeRoot);
	TreeNode<T> *root;
};
