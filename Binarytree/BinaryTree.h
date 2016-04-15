#pragma once
#include <iostream>
#include<queue>
#include<stack>
using namespace std;

//树
template<class T>
struct TreeNode
{
	T	_value;
	TreeNode<T>*		child;
	TreeNode<T>*		brother;	
};

//二叉树
template<class T>
struct BinTreeNode
{
	T					_value;
	BinTreeNode<T>*		left;
	BinTreeNode<T>*		right;
	
	BinTreeNode(char& val) :_value(val), left(NULL), right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree(char* str)
	{
		_Create(root, str);
	}
	BinaryTree(BinaryTree<T>& tree)
	{
		_CopyBinaryTree(root,tree.root);
	}
	BinaryTree& operator=(BinaryTree<T>& tree)
	{
		if (&tree != this)
		{
			_Destroy(root);
			_CopyBinaryTree(root,tree.root);
		}
		return *this;
	}
	~BinaryTree()
	{
		_Destroy(root);
		root = NULL;
	}
	
	//递归实现遍历
	void PreOrder()
	{
		_PreOrder(root);
		cout << endl;
	}
	
	void InOder()
	{
		_InOrder(root);
		cout << endl;
	}
	
	void PostOrder()
	{
		_PostOrder(root);
		cout << endl;
	}
	
	void LevelOrder()
	{
		_LevelOrder(root);
		cout << endl;
	}
	
	void size()
	{
		cout << BinTreeSize(root) << endl;
	}
	
	void Deep()
	{
		cout << BinTreeDeep(root) << endl;
	}
	
	void PI_BackBinaryTree(char*& str1, char* str2)
	{  //还原二叉树
		int len = strlen(str1);
		_PI_BackBinaryTree(root, str1, str2,len);
	}
	
	void IP_BackBinrayTree(char*& str1, char* str2)
	{  //还原二叉树
		int len = strlen(str1);
		str1 = str1 + len - 1;  //后序，所以 str1 指向它的一个元素
		_IP_BackBinaryTree(root, str1, str2, len);
	}
	//非递归实现遍历
	void DPreOrder()
	{
		_DPreOrder(root);
		cout << endl;
	}
	
	void DInOder()
	{
		_DInOrder(root);
		cout << endl;
	}
	
	void DPostOrder()
	{
		_DPostOrder(root);
		cout << endl;
	}

protected:
//递归
	void _Create(BinTreeNode<T>*& root, char*& str)
	{//构建二叉树
		if (*str != '#' && *str != '\0')
		{
			root = new BinTreeNode<T>(*str);
			_Create(root->left, ++str);
			if (*str == '\0')
			{
				return;
			}
			_Create(root->right, ++str);
		}
	}

	void _CopyBinaryTree(BinTreeNode<T>*& t, BinTreeNode<T>* r)
	{//拷贝构造，赋值语句
		if (r)
		{
			t = new BinTreeNode<T>(r->_value);
			_CopyBinaryTree(t->left, r->left);
			_CopyBinaryTree(t->right, r->right);
		}
	}

	void _PreOrder(BinTreeNode<T>* root)
	{
		if (root != NULL)
		{
			 cout << root->_value << " ";
			_PreOrder(root->left);
			_PreOrder(root->right);
		}
	}

	void _Destroy(BinTreeNode<T>*& t) 
	{//删除节点  //引用传递，否则root易成为野指针
		if (t)
		{
			_Destroy(t->left);
			_Destroy(t->right);
			delete t;
			t = NULL;
		}
	}

	//void _Destroy(BinTreeNode<T>* t)
	//{//删除节点//释放后，root是随机值（野指针）
	//	if (t == NULL)
	//	{
	//		return;
	//	}
	//	_Destroy(t->left);
	//	_Destroy(t->right);
	//	delete t;
	//	t = NULL;
	//}
	
	void _InOrder(BinTreeNode<T>* root)
	{
		if (root != NULL)
		{	
			_InOrder(root->left);
			cout << root->_value << " ";
			_InOrder(root->right);
		}
	}
	
	void _PostOrder(BinTreeNode<T>* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->left);
			_PostOrder(root->right);
			cout << root->_value << " ";
		}
	}
	
	int BinTreeSize(BinTreeNode<T>* t)
	{
		if (t == NULL)
			return 0;
		else if (t->left == NULL && t->right == NULL)
			return 1;
		return 1 + BinTreeSize(t->left) + BinTreeSize(t->right);
	}
	
	int BinTreeDeep(BinTreeNode<T>* t)
	{
		if (t == NULL)
		{
			return 0;
		}
		int Left = 1 + BinTreeDeep(t->left);
		int Right = 1 + BinTreeDeep(t->right);
		return Left > Right ? Left : Right;
	}

	void _PI_BackBinaryTree(BinTreeNode<T>*& t, char*& str1, char* str2,int n)
	{//先序和中序还原二叉树
		if (n == 0)
		{
			return;
		}
		char *treenode = str2;
		int leftlen = 0;
		while (*treenode != '\0' && *treenode != *str1)
			treenode++;
		leftlen = treenode - str2;  //用来表示根节点左边有多少个节点
		if (*str1 != '\0')
		{
			t = new BinTreeNode<T>(*str1);
		}
		//左子树的数目 leftlen
		_PI_BackBinaryTree(t->left, ++str1, str2, leftlen);  //左子树的还原
		//除左子树，根，即为右子树 即： n - 1 - leftlen
		_PI_BackBinaryTree(t->right, str1, str2 + leftlen + 1, n - leftlen - 1); //右子树的还原
	}
	
	void _IP_BackBinaryTree(BinTreeNode<T>*& t, char*& str1, char* str2, int n)
	{//中序和后序还原二叉树
		if (n == 0)
		{
			return;
		}
		int leftlen = 0;  //
		char* treenode = str2;
		while (*treenode != *str1)
			treenode++;
		leftlen = treenode - str2;  //左子树节点个数 右子树个数 n-leftlen-1（出去根节点）
		if (*str1 != '\0')
		{
			t = new BinTreeNode<T>(*str1);
		}
		_IP_BackBinaryTree(t->right, --str1, str2 + leftlen + 1, n - leftlen - 1);
		_IP_BackBinaryTree(t->left, str1, str2, leftlen);
	}
	//非递归
	void _LevelOrder(BinTreeNode<T>* root)
	{
		queue<BinTreeNode<T>*> Q;
		if (root)
			Q.push(root);
		while (!Q.empty())
		{
			BinTreeNode<T>* front = Q.front();
			cout << front->_value<<" ";
			Q.pop();
			if (front->left)
				Q.push(front->left);
			if (front->right)
				Q.push(front->right);
		}
	}
	
	void _DPreOrder(BinTreeNode<T>* root)
	{
		stack<BinTreeNode<T>*> S;
		BinTreeNode<T>* cur = NULL;
		if (root)
			S.push(root);
		while (!S.empty())
		{
			cur = S.top();
			cout << cur->_value << " ";
			S.pop();
			if (cur->right)  //先将右子树压到栈底，否则无法访问右子树
				S.push(cur->right);
			if (cur->left)
				S.push(cur->left);
		}
	}
	
	void _DInOrder(BinTreeNode<T>* t)
	{
		BinTreeNode<T>* cur = NULL;
		stack<BinTreeNode<T>*> S;
		if (t != NULL)
			S.push(t);
		while (!S.empty())
		{
			while (t->left != NULL)
			{
				S.push(t->left);
				t = t->left;
			}
			cur = S.top();
			S.pop();
			cout << cur->_value<<" ";
			if (cur->right != NULL)
			{
				S.push(cur->right);
				t = cur->right;   //将右子树当作一颗新树来构建
			}
		}
	}
	
	void _DPostOrder(BinTreeNode<T>* t)
	{
		stack<BinTreeNode<T>*> S;
		BinTreeNode<T>* cur = t;
		BinTreeNode<T>* visitedNode = NULL; //标记已经被访问的节点，用于标记右边的节点被访问过
		while (cur || !S.empty())
		{
			while (cur)
			{
				S.push(cur);
				cur = cur->left;
			}
			t = S.top();
			if (t->right == NULL || t->right == visitedNode)//右孩子为空或被访问过则输出 
			{
				cout << t->_value << " ";
				S.pop();
				visitedNode = t;  //标记该节点被访问过
			}
			else
			{
				cur = t->right; //将右子树当作一颗新树
			}
		}
	}

private:
	BinTreeNode<T>*	root;
};