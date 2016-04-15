#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

enum ThreadTag{ LINK, THREAD };

template<class T>
struct ThreadTreeNode
{
	T					_data;
	ThreadTreeNode<T>*	_left;
	ThreadTreeNode<T>*	_right;
	ThreadTag			_leftTag;
	ThreadTag			_rightTag;

	ThreadTreeNode(const T& data) :_data(data), _left(NULL), _right(NULL),
		_leftTag(LINK), _rightTag(LINK)
	{}
};

template<class T>
class ThreadTree
{
public:
	ThreadTree(const T* array, int size)
	{
		int index = 0;
		_CreateThreadTree(_root, array, size, index);
	}

public:
	//中序线索二叉树以及相关方法
	void InThreadTree()
	{
		ThreadTreeNode<T>* prev = NULL;
		_InThreadTree(_root, prev);
	}
	void PreOrderInThreadTree()
	{
		_PreOrderInThreadTree(_root);
		cout << endl;
	}
	void InOrderInThreadTree()
	{
		_InOrderInThreadTree(_root);
		cout << endl;
	}
	void PostOrderInThreadTree()
	{
		_PostOrderInThreadTree(_root);
		cout << endl;
	}
	T In_First()
	{
		return (_root == NULL) ? 0 : _In_First(_root)->_data;
	}
	T In_Last()
	{
		return (_root == NULL) ? 0 : _In_Last(_root)->_data;
	}
	ThreadTreeNode<T>* In_Next(ThreadTreeNode<T>* node)
	{
		return _In_Next(node);
	}
	ThreadTreeNode<T>* In_Pori(ThreadTreeNode<T>* node)
	{
		return _In_Pori(node);
	}
	ThreadTreeNode<T>* In_Find(const T& key)
	{
		return _In_Find(key);
	}
	ThreadTreeNode<T>* In_Parent(ThreadTreeNode<T>* node)
	{
		return _In_Parent(node);
	}

protected:
	void _CreateThreadTree(ThreadTreeNode<T>*& root, const T* arr, int size, int& index)
	{
		if (index < size && arr[index] != '#')
		{
			root = new ThreadTreeNode<T>(arr[index]);
			_CreateThreadTree(root->_left, arr, size, ++index); //此处index只能为前置++，后置++或+1都不行
			_CreateThreadTree(root->_right, arr, size, ++index);
		}
	}

//中序线索二叉树以及相关方法
	void _InThreadTree(ThreadTreeNode<T>*& root, ThreadTreeNode<T>*& prev)
	{//创建中序线索二叉树
		ThreadTreeNode<T>* cur = root;
		if (cur)
		{
			_InThreadTree(cur->_left, prev);
			if (cur->_left == NULL)
			{
				cur->_leftTag = THREAD; //左子树为空，就将其置左标记为THREAD
				cur->_left = prev;
			}
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD; //右子树为空，则其右标记为THREAD
				prev->_right = cur;
			}
			prev = cur;
			_InThreadTree(cur->_right, prev);  //递归调用右函数
		}
	}
	void _PreOrderInThreadTree(ThreadTreeNode<T>* root)
	{
		ThreadTreeNode<T>* cur = root;
		while (cur)
		{
			cout << cur->_data << " ";
			if (cur->_leftTag != THREAD)
			{
				cur = cur->_left;
			}
			else
			{
				while (cur->_rightTag == THREAD)
				{
					cur = cur->_right;
				}
				cur = cur->_right;
			}
		}
	}
	void _InOrderInThreadTree(ThreadTreeNode<T>* root)
	{//遍历中序线索二叉树
		ThreadTreeNode<T>* cur = root;
		while (cur)
		{
			while (cur && cur->_leftTag != THREAD)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			while (cur && cur->_rightTag == THREAD)
			{ //若是连续右线索，用if不行，可能死循环，所以需要用while
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
	}	
	void _PostOrderInThreadTree(ThreadTreeNode<T>* root)
	{
		ThreadTreeNode<T>* cur = root;
		//找到最左节点
		while (cur->_leftTag == LINK || cur->_rightTag == LINK)
		{
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag == LINK)
				cur = cur->_right;
		}
		cout << cur->_data << " ";

		//以最左节点开始后序遍历
		ThreadTreeNode<T>* parent = NULL;
		while ((parent = In_Parent(cur)) != NULL)
		{//若cur的父节点的右孩子为cur，说明右边已经遍历过，不用再遍历
			if (parent->_right == cur || parent->_rightTag == THREAD || parent->_right == NULL)
			{
				cur = parent;
			}
			else
			{  //左边已访问完，访问右边
				cur = parent->_right;
				//找到该子树的最左端
				while (cur->_leftTag == LINK || cur->_rightTag == LINK )
				{
					if (cur->_leftTag == LINK)
						cur = cur->_left;
					else if (cur->_rightTag == LINK)
						cur = cur->_right;
				}
			}
			cout << cur->_data << " ";
		}
	}
	
	ThreadTreeNode<T>* _In_First(ThreadTreeNode<T>* root)
	{//中序线索树第一个节点
		ThreadTreeNode<T>* cur = root;
		while (cur && cur->_leftTag != THREAD)  //最左边的有线索的节点
			cur = cur->_left;
		return cur;
	}
	ThreadTreeNode<T>* _In_Last(ThreadTreeNode<T>* root)
	{//中序线索树最后一个节点
		ThreadTreeNode<T>* cur = root;
		//最后访问的在右子树：1.右子树为空 2.右节点为线索
		while (cur && cur->_right && cur->_rightTag != THREAD)
		{
			cur = cur->_right;
		}
		return cur;
	}
	ThreadTreeNode<T>* _In_Next(ThreadTreeNode<T>* node)
	{	//右节点为线索
		if (node && node->_rightTag == THREAD)
			return node->_right;
		else if (node->_right)//右节点非线索
		{
			ThreadTreeNode<T>* next = node->_right;
			while (next->_leftTag != THREAD)
			{
				next = next->_left;
			}
			return next;
		}
		else  //右孩子为空（最后一个）
		{
			return node->_right;
		}
	}
	ThreadTreeNode<T>* _In_Pori(ThreadTreeNode<T>* node)
	{
		if (node && node->_leftTag == THREAD)  //左节点为线索
		{
			return node->_left;
		}
		else//左节点非线索
		{
			//以当前结点左子树为根，查找最后一个节点
			ThreadTreeNode<T>* leftLast = _In_Last(node->_left);
			//若左子树最后一个节点的右子树与node相等，则找到
			if (leftLast && leftLast->_right == node)
				return leftLast;
		}
	}
	ThreadTreeNode<T>* _In_Find(const T& key)
	{//查找一个节点
		ThreadTreeNode<T>* cur = _root;
		while (cur)
		{
			if (cur->_data == key)
			{
				return cur;
			}

			if (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else if (cur->_leftTag == THREAD)
			{
				cur = cur->_right;
				cur = cur->_right;
			}
		}
	}
	ThreadTreeNode<T>* _In_Parent(ThreadTreeNode<T>* node)
	{
		//左边
		ThreadTreeNode<T>* cur = node;
		while (cur->_leftTag != THREAD)
		{
			cur = cur->_left;
		}
		cur = cur->_left;
		if (cur&& (cur->_left == node || cur->_right == node)) //判断条件别写弄错了
			return cur;

		//右边
		cur = node;
		while (cur->_right &&cur->_rightTag != THREAD)  //判断条件别写弄错了
		{
			cur = cur->_right;
		}
		cur = cur->_right;
		if (cur && (cur->_left == node || cur->_right == node))
		{
			return cur;
		}

		return NULL;
	}

private:
	ThreadTreeNode<T>* _root;
};


void test2()
{
	//int array[15] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array[15] = { 1, 2, 3, '#', '#', 4, 5, '#', '#', '#', 6, 7 };

	ThreadTree<int> tree2(array, 12);
	tree2.InThreadTree();
	tree2.PreOrderInThreadTree();
	tree2.InOrderInThreadTree();
	tree2.PostOrderInThreadTree();
	cout << tree2.In_Find(1) << endl;
	cout << tree2.In_Parent(tree2.In_Find(2)) << endl;
	cout << tree2.In_First() << endl;
	cout << tree2.In_Last() << endl;
	cout << tree2.In_Next(tree2.In_Find(2)) << endl;
	cout << tree2.In_Find(4);
	cout << tree2.In_Find(1) << endl;
	cout << tree2.In_Find(5) << endl;
	cout << tree2.In_Find(2) << endl;
	cout << tree2.In_Find(2) << endl;
}