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
	avlTree.Search(90);
	std::cout << avlTree.SearchComparisonSteps << std::endl;
	avlTree.cleartree();
	avlTree.cleartree();
	std::cin.get();
	return 0;
}