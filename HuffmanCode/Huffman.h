#pragma once

#include <iostream>
#include "Heap.h"
using namespace std;

template<typename T>
struct HuffmanTreeNode
{ //哈夫曼树节点
	typedef HuffmanTreeNode<T> TreeNode;
	T 		    _weight;
	TreeNode	*_left;
	TreeNode	*_right;
	
	HuffmanTreeNode(const T& w,TreeNode *left = NULL, TreeNode *right = NULL)
			: _weight(w)
			, _left(left)
			, _right(right)
	{}
};

template<typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	/*HuffmanTree(const T* arr, size_t size)
	{
		_root = _CreateHuffmanTree(arr,size);
	}
	*/

	HuffmanTree(const T* arr,size_t size, const T filter=T())
	{ //提供过滤功能的构造函数
		_root = _CreateHuffmanTree(arr,size,filter);
	}
	
	Node* Top()
	{ //获得树顶元素
		return _root;
	}

	void Print()
	{
		_preOrderTrance(_root);	
		cout<<endl;
	}	
	
protected:
	Node* _CreateHuffmanTree(const T* arr, size_t size, const T filter)
	{
		struct Compare
		{ //模板参数，用于提供比较
			bool operator ()(Node* left, Node*right)const
			{
				return left->_weight < right->_weight;
			}
		};
		
		if(size == 0)
		{
			return NULL;
		}

		heap<Node*,Compare> Minheap;
		for(size_t i = 0; i < size; ++i)
		{
			if(arr[i] != filter)
			{
				Node *node = new Node(arr[i]);
				Minheap.Push(node);
			}
		}
		
		while( Minheap.Size() > 1)
		{
		/*建立哈夫曼树的过程，首先取堆的最小元素，再取次小元素（并且在堆中要删掉他们）；以这两个元素的权值和为父节点建立一颗树，将父节点加入堆中，构成新堆；反复上述过程直到堆中只剩一个元素为止，这个时候这个元素就是根节点（堆中的元素是哈夫曼树节点指针，方便树节点的连结）*/
			Node *left = Minheap.Top();
			Minheap.Pop();
		#ifdef _GEBUG_
			cout<<"left val:"<<left->_weight<<endl;
		#endif
			Node *right = Minheap.Top();	
			Minheap.Pop();
		#ifdef _GEBUG_
			cout<<"right val:"<<right->_weight<<endl;
		#endif
			Node *parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			Minheap.Push(parent);	
		}	
		
		return Minheap.Top();
	}

#ifdef _GEBUG_
	void _preOrderTrance(Node *root)
	{
		if(root)
		{
			cout<<root->_weight<<" ";
			_preOrderTrance(root->_left);
			_preOrderTrance(root->_right);
		}
	}
#endif

private:
	Node	*_root;
};


void TestHuffmanTree()
{
	int arr[]={2,4,5,7};
	HuffmanTree<int> Ht(arr,4);
	Ht.Print();
}
