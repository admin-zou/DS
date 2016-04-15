#pragma once
#include <iostream>
#include <vector> //vector不能包含在命名空间内，用于开散列
#include <assert.h>
using namespace std;

namespace HASH_CLOSE //闭散列
{

enum Status{EMPTY,EXIST,DELETE};

template<class T>
class Hashtable
{//考虑负荷因子
public:
	Hashtable(size_t capacity) :_capacity(capacity), _size(0)
	{
		_table = new T[capacity];
		_status = new Status[capacity];
		memset(_table, T(), _capacity*sizeof(T));
		memset(_status, EMPTY, _capacity*sizeof(T));
	}
	~Hashtable()
	{
		delete[] _table;
		delete[] _status;
	}
public:
	bool Full()
	{
		return _size > _capacity;
	}
	bool IsSmall() //考虑负荷因子 0.8
	{
		return ((double)_size / (double)_capacity) >= 0.8;
	}
	bool InCapacity(void)
	{
		size_t capacity = 2 * _capacity;
		T* table = new T[capacity];
		Status * status = new Status[capacity];
		assert(table);
		assert(status);
		memset(table, T(), capacity*sizeof(T));
		memset(status, EMPTY, capacity*sizeof(T));
		for (size_t i = 0; i < _capacity; i++)
		{
			if (_status[i] == EXIST)
			{
				T tmp = _table[i];
				int pos = HashFunc1(tmp%capacity, capacity, status);
				//int pos = HashFunc2(i, capacity, status);
				table[pos] = tmp;
				status[pos] = EXIST;
			}
		}
		delete _table;
		delete _status;
		_table = table;
		_status = status;
		_capacity = capacity;
		return true;
	}
	
	bool Insert(T data)//判断负荷因子需要扩容，相应位置要对应到扩容后的相应位置
	{
		if (Full())
		{
			return false;
		}
		if (IsSmall())  // 容量太小
		{
			InCapacity();//扩容并增加
		}
		int pos = data % _capacity;
		pos = HashFunc1(pos,_capacity,_status);  //一次探测
		//pos = HashFunc2(pos, _capacity,_status);	  //二次探测
		_table[pos] = data;
		_status[pos] = EXIST;
		_size++;
		return true;
	}
	void Print(void)
	{
		for (size_t i = 0; i < _capacity; i++)
		{
			cout << "pos:" << i << " data:" << _table[i] << " status:" << _status[i] << endl;
		}
	}
	int Find(T data)
	{
		int pos = data%_capacity;
		int count = 0;
		while (_table[pos] != data && count<_size)
		{
			++pos;
			++count;
			if (pos == _capacity)
			{
				pos = 0;
			}
		}
		if (_table[pos] == data)
		{
			return pos;
		}
		return -1;
	}
	bool Remove(int data)
	{
		int pos = Find(data);
		if (pos)
		{
			_status[pos] = DELETE;
			return true;
		}
		return false;
	}
	size_t HashFunc1(int pos,int capacity,Status*& status)//一次探测
	{
		while (status[pos] == EXIST)
		{
			pos++;
			if (pos == capacity)
			{
				pos = 0;
			}
		}
		return pos;
	}
	size_t HashFunc2(int pos, int capacity,Status*& status)//二次探测,查找的时候也要按照公式
	{
		int i = 1;
		int _pos = pos;
		while (status[_pos] == EXIST) // && i < (_capacity - 1) / 2
		{
			_pos = (pos + i*i) % capacity;
			i++;
		}
		return _pos;
	}
private:
	T*		_table; //
	Status* _status; //标志该位置是否已存放数据
	size_t  _size;
	size_t  _capacity;
};

void test1()
{//58 68 9 14 36 25  
	Hashtable<int> myht(10);
	myht.Insert(58);
	myht.Insert(68);
	myht.Insert(9);
	myht.Insert(14);
	myht.Insert(7);
	myht.Insert(6);
	myht.Insert(36);
	myht.Insert(25);
	myht.Insert(3);
	myht.Insert(33);
	myht.Insert(31);
	myht.Insert(1);
	myht.Print();
}
void test2()
{
	Hashtable<int> myht(10);
	myht.Insert(58);
	myht.Insert(68);
	myht.Insert(9);
	myht.Insert(38);
	myht.Insert(36);
	myht.Insert(25);
	myht.Print();
}

}

namespace HASH_OPEN //闭散列，哈希表
{

template<class K,class T>
struct HashTableNode
{
	K _key;
	T _val;
	HashTableNode<K, T>* _next;
	HashTableNode(K key, T val) :_key(key), _val(val), _next(NULL)
	{}
};

const int HashSize = 28;
static const unsigned long HashArray[HashSize] = {15ul,25ul,53ul,97ul,193ul};



template<class K,class T>
class HashTable
{
public:
	typedef HashTableNode<K, T>* Node;
public:
	HashTable(int size=5)
	{
		_table.reserve(size);
	}

public:
	bool Add(K key, T val)
	{
		checkCapacity();
		int pos = HashFuc(key, _table.size());
		Node tmp = _table[pos];
		while (tmp)
		{
			if (val == tmp->_val)
				return false;
			tmp = tmp->_next;
		}
		Node cur = new HashTableNode<K, T>(key, val);
		cur->_next = _table[pos];
		_table[pos] = cur;
		++_size;
		return true;
	}
	void Print()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			Node tmp = _table[i];
			printf("[Table%d]:",i);
			while (tmp)
			{
				printf("[k:%d ,v:%0.2f]--",tmp->_key,tmp->_val);
				tmp = tmp->_next;
			}
			printf("NULL\n");
		}
	}

	K find(K& key)
	{
		for (int i = 0; i < _table.size(); i++)
		{
			if (NULL != _table[i] && _table[i]->_key == key)
				return i;
		}
		return NULL;
	}
protected:
	void checkCapacity()
	{
		if ((double)_size / (double)_table.size() < 0.8)
		{
			return;
		}
		size_t capacity = GetCapacity(_table.size());
		vector<Node> table;
		table.reserve(capacity); //定容量
		table.assign(capacity,0);//初始化
		
		//将原来的链上的数据转移的新链
		for (size_t i = 0; i < _table.size(); i++)
		{
			Node cur = _table[i];
			if (cur)
			{
				int pos = HashFuc(cur->_key, capacity);
				while (cur)
				{
					Node tmp = cur;
					cur = cur->_next;
					tmp->_next = table[pos];
					tmp = table[pos];
				}
			}
		}
		swap(_table, table);	
	}
	size_t GetCapacity(size_t size) //获取容量
	{
		int pos = 0;
		while (size >= HashArray[pos])
			pos++;
		return HashArray[pos];
	}
	size_t HashFuc(K key,size_t capacity)
	{
		return key%capacity;
	}
private:
	vector<Node>  _table;
	size_t		  _size; //有效key值
};



void test3()
{
	HashTable<int, double> ht;
	//ht.Add(1, 1.1);
	//ht.Add(2, 2.2);
	for (int i = 0; i < 100; i++)
	{
		int num = rand();
		ht.Add(num, num);
	}
	ht.Print();
}


}