#include "AVLTree.h"
int main()
{
	AVLTree avlTree{};
	avlTree.addnode(50);
	avlTree.addnode(25);
	avlTree.addnode(75);
	avlTree.addnode(10);
	avlTree.addnode(35);
	avlTree.addnode(40);
	avlTree.inorder();
	avlTree.cleartree();
	avlTree.cleartree();
	return 0;
}