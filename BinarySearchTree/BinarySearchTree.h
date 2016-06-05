#pragma once

#include <iostream>
using namespace std;

template<class K,class V>
struct BSTNode
{
	K	_key;
	V	_val;

	BSTNode<K, V>	*_left;
	BSTNode<K, V>	*_right;
	
	BSTNode(const K &key, const V &val)
		: _key(key)
		, _val(val)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K,class V>
class BinarySearchTree
{
	typedef BSTNode<K, V> Node;
public:
	BinarySearchTree() 
		:_root(NULL)
	{}

	~BinarySearchTree()
	{}

	BinarySearchTree(BinarySearchTree& Bt)
	{
		_root = _copyBinaryTree(Bt._root,_root);
	}

	BinarySearchTree& operator=(BinarySearchTree& Bt)
	{
		if (&Bt != this)
		{
			BinarySearchTree<K, V> tmp(Bt);
			swap(_root, tmp._root);
		}

		return *this;
	}

	Node* Find(const K &key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		return NULL;
	}

	bool Insert(const K &key,const V &val)
	{
		//1. 空树
		if (_root == NULL)
		{
			_root = new Node(key, val);
			return true;
		}

		//2.非空情况
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			parent = cur;
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
			
		if (key > parent->_key)
		{
			parent->_right = new Node(key, val);
		}
		else
		{
			parent->_left = new Node(key, val);
		}

		return true;
	}

	bool Remove(const K &key)
	{
		if (_root == NULL)
		{
			return false;
		}

		Node* parent = _root;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key == key)
			{
				break;
			}
			parent = cur;
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}

		if (cur == NULL)
		{ //
			return false;
		}
		else
		{ // 
			Node* del = cur;
			if (cur->_left == NULL || cur->_right == NULL)
			{	
				//cur->_left == NULL && cur->_right == NULL 的情况会考虑到的
				if (parent->_left == cur)
				{
					if (cur->_left == NULL)
						parent->_left = cur->_right;
					else
						parent->_left = cur->_left;
				}
				else if (parent->_right == cur)
				{
					if (cur->_left == NULL)
						parent->_right = cur->_right;
					else
						parent->_right = cur->_left;
				}
				else
				{ //parent == cur
					if (cur->_left)
					{
						_root = cur->_left;
					}
					else
					{
						_root = cur->_right;
					}
				}
			}
			else
			{
				//cur->_left和cur->_right都不为空
				Node * leftofR = cur->_right;  //右节点的最左节点
				while (leftofR->_left)
				{
					parent = leftofR;
					leftofR = leftofR->_left;
				}

				if (parent->_left != leftofR)
				{ //没有左节点
					//位于右边
					if (parent->_right == leftofR)
						parent->_right = leftofR->_right;
					else 
						cur->_right = leftofR->_right;  //位于左边
				}
				else
				{
					parent->_left = leftofR->_right;
				}
				swap(cur->_key, leftofR->_key);
				swap(cur->_val, leftofR->_val);
				del = leftofR;				
			}
			//删除节点
			delete del;
			return true;
		}
	}

	bool Insert_R(const K &key, const V &val)
	{ //递归插入
		return _Insert_R(_root, key, val);
	}

	bool Remove_R(const K &key)
	{
		return _Remove_R(_root,key);
	}
	
	void Print()
	{
		_InOrderTrace(_root);
		cout << endl;
	}

protected:
	Node* _copyBinaryTree(const Node* Copy, Node* root)
	{
		if (Copy == NULL)
		{
			return NULL;
		}
		if (Copy)
		{
			root = new Node(Copy->_key, Copy->_val);
			if (Copy->_left)
			{
				root->_left = _copyBinaryTree(Copy->_left, root->_left);
			}
			if (Copy->_right)
			{
				root->_right = _copyBinaryTree(Copy->_right, root->_right);
			}			
		}
		return root;
	}

	void _InOrderTrace(Node* root)
	{
		if (NULL == root)
		{
			return ;
		}

		_InOrderTrace(root->_left);
		cout << root->_key << " ";
		_InOrderTrace(root->_right);
	}

	bool _Insert_R(Node*& root, const K& key, const V& val)
	{
		//插入点
		if (root == NULL)
		{
			root = new Node(key, val);
			return true;
		}

		if (key == root->_key)
		{
			return false;
		}
		else if (key < root->_key)
		{
			return _Insert_R(root->_left, key, val);
		}
		else
		{
			return _Insert_R(root->_right, key, val);
		}
	}

	bool _Remove_R(Node*& root, const K key)
	{
		if (root == NULL)
		{
			return false;
		}

		if (key < root->_key)
		{
			return _Remove_R(root->_left,key);
		}
		else if (key > root->_key)
		{
			return _Remove_R(root->_right, key);
		}
		else
		{ 
			// key = root->key
			Node* del = root;
			if (root->_left == NULL || root->_right == NULL)
			{
				if (root->_left == NULL && root->_right == NULL)
				{
					root = NULL;
				}
				else if (root->_left == NULL)
				{
					root = root->_right;
				}
				else
				{ //root->_right == NULL
					root = root->_left;
				}
				return true;
			}
			else
			{
				Node* LeftofR = root->_right;
				Node* parent = NULL;
				while (LeftofR->_left)
				{
					parent = LeftofR;
					LeftofR = LeftofR->_left;
				}
				//没有左节点
				if (parent == NULL)
				{
					if (LeftofR = root->_left)
					{
						root = root->_left;
					}
					else
					{
						root = root->_right;
					}
				}
				else
				{
					if (parent->_left == LeftofR)
					{
						parent->_left = LeftofR->_right;
					}
					else
					{
						parent->_right = LeftofR->_right;
					}
					swap(root->_key, LeftofR->_key);
					swap(root->_val, LeftofR->_val);
					del = LeftofR;
				}
			}
			delete del;
			return true;
		}
	}

protected:
	Node	*_root;
};

void TestBinaryTree()
{
	BinarySearchTree<int, int> Bt;
	Bt.Insert(5, 1);
	Bt.Insert(6, 1);
	Bt.Insert(3, 1);
	Bt.Insert(7, 1);
	Bt.Insert(2, 1);
	Bt.Insert(1, 1);
	Bt.Insert(8, 1);
	Bt.Insert(4, 1);
	Bt.Insert(9, 1);
	Bt.Print();
	BinarySearchTree<int, int>Bt1(Bt);
	Bt1.Print();
	Bt.Remove(6);
	Bt.Remove(5);
	Bt.Remove(3);
	Bt.Remove(2);
	Bt.Remove(1);
	Bt.Remove(8);
	Bt.Remove(7);
	Bt.Remove(9);
	Bt.Remove(4);
	Bt.Print();
	Bt.Insert_R(5, 1);
	Bt.Insert_R(6, 1);
	Bt.Insert_R(3, 1);
	Bt.Insert_R(7, 1);
	Bt.Insert_R(2, 1);
	Bt.Insert_R(1, 1);
	Bt.Insert_R(8, 1);
	Bt.Insert_R(4, 1);
	Bt.Insert_R(9, 1);
	Bt.Print();
	Bt.Remove_R(6);
	Bt.Remove_R(5);
	Bt.Remove_R(3);
	Bt.Remove_R(2);
	Bt.Remove_R(1);
	Bt.Remove_R(8);
	Bt.Remove_R(7);
	Bt.Remove_R(9);
	Bt.Remove_R(4);
	Bt.Print();
}

