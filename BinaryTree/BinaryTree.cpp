#define _CRT_SECURE_NO_WARNINGS
#include "BinaryTree.h"

int main()
{
	char *preorder = "123456";
	char *inorder = "324165";
	char *postorder = "342651";

	BinaryTree<char> BT1("");
	BT1.IP_BackBinrayTree(postorder, inorder);
	BT1.PreOrder();
	BT1.InOder();
	BT1.PostOrder();

	BinaryTree<char> T("123##4##56");
	BinaryTree<char> BT("");
	BT.PI_BackBinaryTree(preorder, inorder);
	BT.PreOrder();
	BT.InOder();
	BT.PostOrder();

	BinaryTree<char> T2(T);
	BinaryTree<char> T3("123");
	T3 = T;
	T.PreOrder();
	T2.PreOrder();
	T3.PreOrder();

	T.PreOrder();
	T.InOder();
	T.PostOrder();
	T.LevelOrder();

	T.DPreOrder();
	T.DInOder();
	T.DPostOrder();
	T.size();
	T.Deep();
	
	return 0;
}
