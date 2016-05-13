#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BitMap
{
public:
	BitMap(size_t size)
	{
		_array.resize((size>>5) + 1);
	}

	void Set(size_t num)
	{
		size_t index = num>>5;
		size_t pos = num % 32;
		_array[index] |= (1 << pos);
	}

	void Reset(size_t num)
	{
		size_t index = num>>5;
		size_t pos = num % 32;
		_array[index] &= ~(1 << pos);
	}

	bool Test(size_t num)
	{
		size_t index = num>>5;
		size_t pos = num % 32;
		return _array[index] & (1 << pos);
	}

	~BitMap()
	{}

private:
	vector<size_t> _array;	
};
