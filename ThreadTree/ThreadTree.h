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
	//���������������Լ���ط���
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
			_CreateThreadTree(root->_left, arr, size, ++index); //�˴�indexֻ��Ϊǰ��++������++��+1������
			_CreateThreadTree(root->_right, arr, size, ++index);
		}
	}

//���������������Լ���ط���
	void _InThreadTree(ThreadTreeNode<T>*& root, ThreadTreeNode<T>*& prev)
	{//������������������
		ThreadTreeNode<T>* cur = root;
		if (cur)
		{
			_InThreadTree(cur->_left, prev);
			if (cur->_left == NULL)
			{
				cur->_leftTag = THREAD; //������Ϊ�գ��ͽ���������ΪTHREAD
				cur->_left = prev;
			}
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD; //������Ϊ�գ������ұ��ΪTHREAD
				prev->_right = cur;
			}
			prev = cur;
			_InThreadTree(cur->_right, prev);  //�ݹ�����Һ���
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
	{//������������������
		ThreadTreeNode<T>* cur = root;
		while (cur)
		{
			while (cur && cur->_leftTag != THREAD)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			while (cur && cur->_rightTag == THREAD)
			{ //������������������if���У�������ѭ����������Ҫ��while
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
	}	
	void _PostOrderInThreadTree(ThreadTreeNode<T>* root)
	{
		ThreadTreeNode<T>* cur = root;
		//�ҵ�����ڵ�
		while (cur->_leftTag == LINK || cur->_rightTag == LINK)
		{
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag == LINK)
				cur = cur->_right;
		}
		cout << cur->_data << " ";

		//������ڵ㿪ʼ�������
		ThreadTreeNode<T>* parent = NULL;
		while ((parent = In_Parent(cur)) != NULL)
		{//��cur�ĸ��ڵ���Һ���Ϊcur��˵���ұ��Ѿ��������������ٱ���
			if (parent->_right == cur || parent->_rightTag == THREAD || parent->_right == NULL)
			{
				cur = parent;
			}
			else
			{  //����ѷ����꣬�����ұ�
				cur = parent->_right;
				//�ҵ��������������
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
	{//������������һ���ڵ�
		ThreadTreeNode<T>* cur = root;
		while (cur && cur->_leftTag != THREAD)  //����ߵ��������Ľڵ�
			cur = cur->_left;
		return cur;
	}
	ThreadTreeNode<T>* _In_Last(ThreadTreeNode<T>* root)
	{//�������������һ���ڵ�
		ThreadTreeNode<T>* cur = root;
		//�����ʵ�����������1.������Ϊ�� 2.�ҽڵ�Ϊ����
		while (cur && cur->_right && cur->_rightTag != THREAD)
		{
			cur = cur->_right;
		}
		return cur;
	}
	ThreadTreeNode<T>* _In_Next(ThreadTreeNode<T>* node)
	{	//�ҽڵ�Ϊ����
		if (node && node->_rightTag == THREAD)
			return node->_right;
		else if (node->_right)//�ҽڵ������
		{
			ThreadTreeNode<T>* next = node->_right;
			while (next->_leftTag != THREAD)
			{
				next = next->_left;
			}
			return next;
		}
		else  //�Һ���Ϊ�գ����һ����
		{
			return node->_right;
		}
	}
	ThreadTreeNode<T>* _In_Pori(ThreadTreeNode<T>* node)
	{
		if (node && node->_leftTag == THREAD)  //��ڵ�Ϊ����
		{
			return node->_left;
		}
		else//��ڵ������
		{
			//�Ե�ǰ���������Ϊ�����������һ���ڵ�
			ThreadTreeNode<T>* leftLast = _In_Last(node->_left);
			//�����������һ���ڵ����������node��ȣ����ҵ�
			if (leftLast && leftLast->_right == node)
				return leftLast;
		}
	}
	ThreadTreeNode<T>* _In_Find(const T& key)
	{//����һ���ڵ�
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
		//���
		ThreadTreeNode<T>* cur = node;
		while (cur->_leftTag != THREAD)
		{
			cur = cur->_left;
		}
		cur = cur->_left;
		if (cur&& (cur->_left == node || cur->_right == node)) //�ж�������дŪ����
			return cur;

		//�ұ�
		cur = node;
		while (cur->_right &&cur->_rightTag != THREAD)  //�ж�������дŪ����
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