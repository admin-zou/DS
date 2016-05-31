#pragma once
#include <iostream>
#include <vector>
using namespace std;


template<class T>
class Small
{ //比较类，提供函数对象
public:
	bool operator() (const T &l, const T &r)
	{
		return l < r;
	}
};

template<class T>
class Big
{
public:
	bool operator() (const T &l,const T &r)
	{
		return l > r;
	}
};


template<class T,class Com = Small<T> >
class heap
{
public:
	heap():_size(0)
	{}
	
	heap(const T *a, int size)
	{
		if(a == NULL || size == 0)
		{
			cout<<"array is null"<<endl;
			return ;
		}
		_size = size;
		for(int i = 0; i < size; ++i)
		{
			_arr.push_back(a[i]);
		}
		//建堆过程
		int root = (_size-2)/2;
		while(root >= 0)
		{
			_Adjustdown(root);
			--root;
		}
	}

	heap(vector<T> a)
	{
		swap(_arr,a);
		_size=_arr.size();
		int root = (_size-2)/2;
		while(root >= 0)
		{
			_Adjustdown(root);
			--root;
		}
	}
	
	bool Empty()
	{
		return _size == 0;
	}

	//Append方法和Remove方法配对使用，因为他们不会将数组中的删掉，而是保留
	void Append(const T& x)
	{
		//_arr.push_back(x); 这样有bug
		if(_arr.size() <= _size)
		{	//空的时候会崩溃，
			_arr.push_back(x);
		}
		else
		{
			_arr[_size] = x;
		}
		++_size;
	
		_Adjustup(_size-1);
	}

	void Remove()
	{ // 并没有删掉元素，只是将它放到了vector的[_size-1]位置而已
		if(_size == 0)
		{
			return ;
		}
		swap(_arr[0],_arr[_size-1]);
		--_size;
		_Adjustdown(0);		
	}

	//提供了Push和Pop两种方法，他们会删掉vector中的元素
	bool Push(T x)
	{
		_arr.push_back(x);
		++_size;
		_Adjustup(_size-1);
		return true;
	}

	//注意使用，pop方法会删掉堆中的元素	，最好和push方法配对使用
	void Pop()
	{
		if(!Empty())
		{
			_arr[0] = _arr[_size-1];
			_arr.pop_back();
			--_size;
			_Adjustdown(0);
		}
	}
		
	T Top()
	{
		if(!Empty())
			return _arr[0];
	}	
		
	size_t Size()
	{
		return _size;
	}
	
	void Print()
	{ //打印堆的信息
		int flag = 1;
		for(int i=0; i < _size ; ++i)
		{
			cout<<_arr[i]<<" ";
			if(i == 0)
			{
				flag = 2;
				cout<<endl;
			}
			if(i == flag)
			{
				cout<<endl;
				flag += flag*2;
			}
		}
		cout<<endl;
	}

protected:
	void _Adjustdown(int root)
	{ //向下调整的方法，建堆的过程，Push方法，Remove方法会调用该函数
		int left = root*2+1;
		int right = left+1;
		Com compare;
		while(left < _size)
		{
			int key = left;
			//if(right < _size && _arr[right] < _arr[left])
			if(right < _size &&  compare(_arr[right],_arr[left]) )
			{
				key = left + 1;
			}
			//if(_arr[root] > _arr[key])
			if( compare( _arr[key],_arr[root]) )
			{
				swap(_arr[root],_arr[key]);
				root = key;
				left = key*2 + 1;
				right = left + 1;
			}
			else
			{
				break;
			}
		}
	}

	void _Adjustup(int base)
	{ //向上调整，Push和Append方法会调用到
		int root = (base-1) / 2;
		Com compare;
		while(root >= 0)
		{
			//if(_arr[root] > _arr[base])
			if( compare(_arr[base],_arr[root]) )
			{
				swap(_arr[root],_arr[base]);
				
				if(root == 0)
				{
					break;
				}
				
				base = root;
				root = (base-1)/2;
			}
			else
			{
				break;
			}
		}
	}

private:
	vector<T>	_arr;
	int         _size;
};
