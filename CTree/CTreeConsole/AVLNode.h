#ifndef AVLNode_H_
#define AVLNode_H_
struct AVLNode
{
	int Value;
	int BalanceFactor;
	AVLNode * LeftNode;
	AVLNode * RightNode;

};
#endif // !AVLNode_H_