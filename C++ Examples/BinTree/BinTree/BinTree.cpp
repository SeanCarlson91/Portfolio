#pragma once

#include "BinTree.h"

template<class T>
T TreeNode<T>::getData() {
	return data;
}
template<class T>
TreeNode<T> *TreeNode<T>::getRight() {
	return rightLink;
}
template<class T>
TreeNode<T> *TreeNode<T>::getLeft() {
	return leftLink;
}
template<class T>
void TreeNode<T>::setRight(T item) {
	rightLink = new TreeNode<T>(item, NULL, NULL);
}
template<class T>
void TreeNode<T>::setLeft(T item) {
	leftLink = new TreeNode<T>(item, NULL, NULL);
}
template<class T>
TreeNode<T> *BinTree<T>::getRoot() {
	return root;
}
template<class T>
BinTree<T>::BinTree(T data) {
	root = new TreeNode<T>(data, NULL, NULL);
}

template<class T>
void BinTree<T>::deleteSubtree(TreeNode<T>*& subTreeRoot)
{
	if (subTreeRoot != NULL)
	{
		deleteSubtree(subTreeRoot->leftLink);

		deleteSubtree(subTreeRoot->rightLink);

		//subTreeRoot now points to a one node tree.
		delete subTreeRoot;
		subTreeRoot = NULL;
	}
}

template<class T>
BinTree<T>::~BinTree()
{
	deleteSubtree(root);
}
