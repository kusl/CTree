#ifndef AVLTree_H_
#define AVLTree_H_
#include <iostream>
#include "AVLNode.h"
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif 
#endif
class AVLTree
{
public:
	AVLTree()
	{
		root = NULL;
	}
	~AVLTree()
	{
		cleartree();
	}
	int SearchComparisonSteps = 0;
	void addnode(int item)
	{
		// This procedure should add an item to the tree.  If the tree is unbalanced a rotation should occur.
		IsBalanceFactorChanging = true;
		RecursiveAddItem(root, item);
	}

	bool deletenode(int item)
	{
		// This procedure should delete the item from the tree.  It will return true if found and false if not found.
		//  The tree should be balanced after the deletion.  This may take many rotations.
		IsBalanceFactorChanging = true;
		RecursiveDelete(root, item);
	}

	void cleartree()
	{
		//  This procedure should give all the memory back and set root to NULL.
		RecursiveClear(root);
		root = NULL;
	}

	void inorder()
	{
		// This procedure should print the data in the tree in order.
		RecursiveInOrder(root);
	}

	void showtree()
	{
		// This procedure should display a graphical version of the tree.

	}

	bool Search(int item)
	{
		AVLNode * trav = root;
		SearchComparisonSteps = 0;
		while (true)
		{
			if (trav != NULL)
			{
				if (item == trav->Value)
				{
					// found! 
					return true;
				}
				else if (item > trav->Value)
				{
					SearchComparisonSteps++;
					trav = trav->RightNode;
				}
				else if (item < trav->Value)
				{
					SearchComparisonSteps++;
					trav = trav->LeftNode;
				}
			}
			else
			{
				return false;
			}
		}
	}

private:
	AVLNode * root;
	enum Rotation { SingleLeft, SingleRight, DoubleLeft, DoubleRight };
	bool IsBalanceFactorChanging;
	void Rotate(Rotation rotation, AVLNode *& trav)
	{
		AVLNode * temporary;
		if (rotation == SingleLeft)
		{
			temporary = trav->LeftNode;
			trav->LeftNode = temporary->RightNode;
			temporary->RightNode = trav;
			trav->BalanceFactor = 0;
			trav = temporary;
			temporary->BalanceFactor = 0;
		}
		else if (rotation == SingleRight)
		{
			temporary = trav->RightNode;
			trav->RightNode = temporary->LeftNode;
			trav->BalanceFactor = 0;
			temporary->LeftNode = trav;
			trav = temporary;
			temporary->BalanceFactor = 0;
		}
		else if (rotation == DoubleLeft)
		{
			temporary = trav->LeftNode;
			trav->LeftNode = temporary->RightNode->RightNode;
			temporary->RightNode->RightNode = trav;
			trav = temporary->RightNode;
			temporary->RightNode = trav->LeftNode;
			trav->LeftNode = temporary;
			if (trav->BalanceFactor > 0)
			{
				trav->LeftNode->BalanceFactor = -1;
				trav->RightNode->BalanceFactor = 0;
			}
			else if (trav->BalanceFactor < 0)
			{
				trav->RightNode->BalanceFactor = 1;
				trav->LeftNode->BalanceFactor = 0;
			}
			else
			{
				trav->RightNode->BalanceFactor = 0;
				trav->LeftNode->BalanceFactor = 0;
			}
			trav->BalanceFactor = 0;
		}
		else if (rotation == DoubleRight)
		{
			temporary = trav->RightNode;
			trav->RightNode = temporary->LeftNode->LeftNode;
			temporary->LeftNode->LeftNode = trav;
			trav = temporary->LeftNode;
			temporary->LeftNode = trav->RightNode;
			trav->RightNode = temporary;
			if (trav->BalanceFactor > 0)
			{
				trav->RightNode->BalanceFactor = -1;
				trav->LeftNode->BalanceFactor = 0;
			}
			else if (trav->BalanceFactor < 0)
			{
				trav->LeftNode->BalanceFactor = 1;
				trav->RightNode->BalanceFactor = 0;
			}
			else
			{
				trav->RightNode->BalanceFactor = 0;
				trav->LeftNode->BalanceFactor = 0;
			}
			trav->BalanceFactor = 0;
		}
		//delete temporary;
	}
	void RecursiveAddItem(AVLNode *& trav, int item)
	{
		if (trav == NULL)
		{
			// we are adding a new root
			trav = new AVLNode;
			trav->Value = item;
			trav->BalanceFactor = 0;
			trav->LeftNode = NULL;
			trav->RightNode = NULL;
		}
		else if (item < trav->Value)
		{
			// we're going left 
			RecursiveAddItem(trav->LeftNode, item);
			if (IsBalanceFactorChanging)
			{
				trav->BalanceFactor -= 1;
				if (trav->BalanceFactor == -2)
				{
					std::cout << "We'll have to rotate here" << std::endl;
					if (trav->LeftNode->BalanceFactor > 0)
					{
						std::cout << "We'll have to double rotate here" << std::endl;
						Rotate(DoubleLeft, trav);
					}
					else if (trav->LeftNode->BalanceFactor < 0)
					{
						std::cout << "We'll have to single rotate here" << std::endl;
						Rotate(SingleLeft, trav);
					}
				}
				else if (trav->BalanceFactor == 0)
				{
					IsBalanceFactorChanging = false;
				}
			}
		}
		else
		{
			// we're going right 
			RecursiveAddItem(trav->RightNode, item);
			if (IsBalanceFactorChanging)
			{
				trav->BalanceFactor += 1;
				if (trav->BalanceFactor == 2)
				{
					std::cout << "We'll have to rotate here" << std::endl;
					if (trav->RightNode->BalanceFactor > 0)
					{
						std::cout << "We'll have to double rotate here" << std::endl;
						Rotate(DoubleRight, trav);
					}
					else if (trav->RightNode->BalanceFactor < 0)
					{
						std::cout << "We'll have to single rotate here" << std::endl;
						Rotate(SingleRight, trav);
					}
				}
				else if (trav->BalanceFactor == 0)
				{
					IsBalanceFactorChanging = false;
				}
			}
		}
	}
	void RecursiveClear(AVLNode * trav)
	{
		if (trav != NULL)
		{
			if (trav->LeftNode != NULL)
			{
				RecursiveClear(trav->LeftNode);
			}
			if (trav->RightNode != NULL)
			{
				RecursiveClear(trav->RightNode);
			}
			delete trav;
		}
	}
	void RecursiveInOrder(AVLNode * trav)
	{
		if (trav != NULL)
		{
			if (trav->LeftNode != NULL)
			{
				RecursiveInOrder(trav->LeftNode);
			}
			std::cout << trav->Value << std::endl;
			if (trav->RightNode != NULL)
			{
				RecursiveInOrder(trav->RightNode);
			}
		}
	}
	void RecursiveDelete(AVLNode * trav, int item)
	{

	}
};
#endif // !Tree_H_