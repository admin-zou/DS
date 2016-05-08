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



namespace HASH_KV_Vocabulary  //字典
{
	enum Status
	{
		EXIST,
		EMPTY,
		DELETE		
	};

	template<class K,class V>
	struct KVNode
	{
		K _key;
		V _val;
		
		KVNode(const K &key = K(), const V &val = V()) :
			_key(key),
			_val(val)
		{}
	};


	class HashFuncer
	{
	public:
		size_t operator() (const string &s)
		{
			size_t pos = 0;
			int len = s.size();
			for (int i = 0; i < len;++i)
			{
				pos = pos * 131 + (unsigned char)s[i];
			}
			return pos&(0x7FFFFFFF);
		}
	};


	template<class K, class V,class HashFunc=HashFuncer>
	class HashTable
	{
		typedef KVNode<K, V> Node;
	public:
		HashTable(size_t sz):
			_table(new Node[sz]),
			_status(new Status[sz]), 
			_size(0),
			_capacity(sz)
		{
			memset(_status, 1, sizeof(Status)*sz);
		}

		~HashTable()
		{
			if (this->_status)
			{
				delete[] this->_status;
				delete[] this->_table;
			}
			_size = 0;
			_capacity = 0;
		}

		bool Insert(const K & key,const V & val)
		{
			_checkcapacity();
			//1.一次探测法(负载因子可控制在0.7左右)
			/*int index = HashPos(key);
			while (_status[index] == EXIST)
			{
				if (_table[index]._key == key)
				{
					return false;
				}
				++index;
				if (index == _capacity )
				{
					index = 0;
				}				
			}*/
			
			//2.二次探测法(负载因子必须小点，0.5左右吧)
			size_t index = HashPos0(key);
			size_t pos0 = index;
			size_t i = 1;
			while (_status[index] == EXIST)
			{
				++i;
				index = HashPosi(pos0, i);
			}

			_table[index]._key = key;
			_table[index]._val = val;
			_status[index] = EXIST;
			++_size;
			return true;
		}
		
		bool Erase(const K &key)
		{
			int index = Find(key);
			if (index != -1)
			{
				--_size;
				_status[index] == DELETE;
				return true;
			}
			return false;
		}

		int Find(const K &key)
		{
			int pos = -1;
			for (int i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST && _table[i]._key == kv)
				{
					pos = i;
					break;
				}
			}
			return pos;
		}

		void PrintHash()
		{
			for (size_t i = 0; i < _capacity; ++i)
			{
				cout << i<<": ";
				if (_status[i] == EXIST)
				{
					//cout << _table[i]._key.c_str() << _table[i]._val.c_str();
					printf("[%s -- %s]", _table[i]._key.c_str(), _table[i]._val.c_str());
				}
				cout << endl;
			}
		}
	protected:
		size_t HashPos(const K &key)
		{//一次探测
			//return kv->_key / _capacity;
			/*HashFuncer h;
			return h(key) % _capacity;*/
			return HashFuncer()(key) % _capacity;
		}

		size_t HashPos0(const K&key)
		{//二次探测
			return HashFuncer()(key) % _capacity;
		}
		size_t HashPosi(size_t pos0,size_t i)
		{//二次探测
			size_t pos = pos0;
			for (size_t index = 1; index < i; ++index)
			{
				pos += 2 * i - 1;
			}
			return pos;
		}

		void _checkcapacity()
		{
			if (_size * 10 >= _capacity * 7)
			{
				HashTable<K, V, HashFunc> tmp(2 * _capacity);
				for (size_t i = 0; i < _capacity; ++i)
				{
					if (_status[i] == EXIST)
					{
						size_t pos = tmp.HashPos(_table[i]._key);
						while (tmp._status[pos] == EXIST)
						{
							++pos;
							if (pos == tmp._capacity)
							{
								pos = 0;
							}
						}
						tmp._table[pos] = _table[i];
						tmp._status[pos] = EXIST;
					}
				}
				Swap(tmp);
			}
		}

		void Swap(HashTable<K, V, HashFunc>& tmp)
		{
			swap(_table, tmp._table);
			swap(_status,tmp._status);
			swap(_capacity, tmp._capacity);
		}

	private:
		Node    *_table;
		Status  *_status;
		size_t  _size;
		size_t  _capacity;
	};

	void Test()
	{
		HashTable<string, string> KV(10);
		KV.Insert("petter","张老师");
		KV.Insert("Adam", "欧姆");
		KV.Insert("Lisa", "李莎");
		KV.Insert("Bart", "巴尔");
		KV.Insert("Jack", "杰克");
		KV.Insert("Jhon", "约翰");
		KV.Insert("Mack", "迈克尔");
		KV.Insert("Tom", "汤姆猫");
		KV.PrintHash();
	}
}



namespace HASH_OPEN //开散列(哈希桶)，哈希表
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
static const unsigned long HashArray[HashSize] = 
	{ 
	53ul, 97ul, 193ul, 389ul, 769ul,1543ul, 3079ul, 6151ul,
	12289ul, 24593ul,49157ul, 98317ul, 196613ul, 393241ul,786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul,25165843ul,50331653ul,
	100663319ul, 201326611ul, 402653189ul,805306457ul,1610612741ul, 3221225473ul, 
	4294967291ul 
	};

template<class K>
struct HashFuncer
{
	size_t operator() (const char* str)
	{
		size_t pos = 0;
		size_t seed = 131; //31 131 1313 13131 131313
		while (*str != '\0')
		{
			pos = pos*seed + (unsigned char)*str++;
		}
		return (pos & 0x7FFFFFFF);
	}
};

template<class K,class T,class HashFunc=HashFuncer<K> >
class HashTable
{
	typedef HashTableNode<K, T> Node;
public:
	HashTable()
	{
		_size = 0;
		//_table.reserve(size);
	}

	HashTable(HashTable<K, T> &Ht)
	{
		size_t vSize = Ht._table.size();
		_table.resize(vSize);
		for (size_t i = 0; i < vSize; ++i)
		{
			Node *cur = Ht._table[i];
			while (cur)
			{
				Node *pnode = new Node(cur->_key, cur->_val);
				pnode->_next = _table[i];
				_table[i] = pnode;
				cur = cur->_next;
			}
		}
	}

	bool Add(const K &key, const T &val)
	{
		_checkCapacity();
		int pos = HashFuc(key, _table.size());
		//size_t pos = HashFunc()(key);
		Node *tmp = _table[pos];
		while (tmp)
		{
			if (val == tmp->_val)
				return false;
			tmp = tmp->_next;
		}
		//Node *cur = new HashTableNode<K, T>(key, val);
		Node *cur = new Node(key, val);
		cur->_next = _table[pos];
		_table[pos] = cur;
		++_size;
		return true;
	}

	void Print()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			Node *tmp = _table[i];
			printf("[Table%d]:",i);
			while (tmp)
			{
				printf("[%d ,%0.2f]->",tmp->_key,tmp->_val);
				tmp = tmp->_next;
			}
			printf("NULL\n");
		}
	}

	Node *find(const K &key, const T &val)
	{
		size_t index = HashFuc(key, _table.size());
		Node *cur = _table[index];
		while (cur)
		{
			if (cur->_val == val)
			{
				break;
			}
			cur = cur->_next;
		}
		return cur;
	}

	bool Remove(const K &key, const T &val)
	{
		size_t index = HashFuc(key, _table.size());
		Node *cur = _table[index];
		Node *prev = NULL;
		if (cur == NULL)
		{//空
			return true;
		}

		while (cur)
		{
			if (cur->_val == val)
			{
				break;
			}
			prev = cur;
			cur = cur->_next;
		}

		if (cur == NULL)
		{//不存在
			return true;
		}

		if (prev == NULL)
		{//头部
			_table[index] = cur->_next;
		}
		else if (cur)
		{//其他情况
			prev->_next = cur->_next;
		}

		delete cur;
		--_size;
		
		return true;
	}

	~HashTable()
	{
		_size = 0;
	}

protected:
	
	void _checkCapacity()
	{
		if (_size == _table.size())
		{
			size_t capacity = GetCapacity(_table.size());  //获取下一个比当前size大的素数
			vector<Node*> table;
			table.reserve(capacity); //定容量
			table.assign(capacity, 0);//初始化

			//将原来的链上的数据转移的新链
			for (size_t i = 0; i < _table.size(); i++)
			{
				Node *cur = _table[i];
				if (cur)
				{
					while (cur)
					{
						Node *tmp = cur;
						cur = cur->_next;
						int pos = HashFuc(tmp->_key, capacity);
						tmp->_next = table[pos];
						table[pos] = tmp;
					}
				}
			}
			swap(_table, table);
		}
	}

	size_t GetCapacity(size_t size) //获取容量
	{
		int pos = 0;
		while (size >= HashArray[pos])
		{
			pos++;
			if (size == HashSize)
			{
				return HashArray[HashSize - 1];
			}
		}
		return HashArray[pos];
	}

	size_t HashFuc(K key,size_t capacity)
	{
		return key%capacity;
	}

private:
	vector<Node*>  _table;
	size_t		  _size; //有效key值
};


void test3()
{
	HashTable<int, double> ht;
	//ht.Add(1, 1.1);
	//ht.Add(2, 2.2);
	/*
	for (int i = 0; i < 58; i++)
	{
		int num = rand();
		ht.Add(num, num);
	}
	*/
	ht.Add(1, 2);
	ht.Add(1, 3);
	ht.Add(1, 4);
	ht.Add(1, 5);
	ht.Print();
	cout<<ht.find(1,2)->_val<<endl;
	ht.Remove(1, 2);
	ht.Print();
	HashTable<int, double> ht2 = ht;
	ht2.Print();
}

}
