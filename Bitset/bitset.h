#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

class Bitset
{
public:
	Bitset(size_t Num)
	{
		_size = Num / 32 + 1;
		_array = new size_t [_size];
		memset(_array, 0, sizeof(size_t)*_size);
	}
	~Bitset()
	{
		_size = 0;
		delete[] _array;
	}
	void Set(size_t num)
	{
		int index = num / 32;
		int pos = num % 32;
		assert(index < _size);
		_array[index] |= (1 << (32 - pos));
	}
	void ReSet(size_t num)
	{
		int index = num / 32;
		int pos = num % 32;
		assert(index < _size);
		_array[index] &= ~(1 << (32 - pos));
	}
	void Clear()
	{
		memset(_array, 0, sizeof(size_t)*_size);
	}
	bool Test(size_t num)
	{
		int index = num / 32;
		int pos = num % 32;
		assert(index < _size);
		return (_array[index] & (1 << (32 - pos)));
	}
private:
	size_t* _array;
	size_t  _size;
};