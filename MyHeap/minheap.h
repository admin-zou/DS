//堆排序 //求100个数中的前10个最大数
#pragma once
#include<iostream>
#include <vector>
using namespace std;

template<class T>
class MinHeap
{//小堆
public:
	MinHeap(const T* arr, int size)//建堆时间复杂度  N*lg(N)
	{
		_array.reserve(size); //事先知道空间大小后，直接开辟需要的空间，不需要在插入过程中扩增容量

		for (int i = 0; i < size; i++)
		{
			_array.push_back(arr[i]);
		}
		int len = _array.size();
		int begin = len / 2 - 1;
		while (begin >= 0)
		{
			_AdjustDown(begin, len);
			begin--;            //从下往上调用向下排序就可以完成最小堆排序
		}
	}

	MinHeap(vector<T>& arr)
	{
		_array = arr;
	}

	MinHeap(int n)
	{
		_array.reserve(n);
	}

	MinHeap()
	{}

	void Insert(const T& x) //时间复杂度  lg(N)
	{
		_array.push_back(x);
		int begin = _array.size() - 1;
		_AdjustUp(begin);
	}

	void Pop() //删除最对头
	{
		if (!Empty())
		{
			swap(_array[0], _array[_array.size() - 1]);
			_AdjustDown(0, _array.size() - 1);
		}
	}

	void HeapSort() //时间复杂度lg(N)
	{
		int len = _array.size();

		while (len)
		{
			swap(_array[0], _array[len - 1]); //每次排序后，将堆顶与堆尾交换，堆尾减一
			_AdjustDown(0, len);
			--len;
		}
	}

	void Print(void)
	{
		int len = _array.size();
		for (int i = 0; i < len - 1; i++)
			cout << _array[i] << " ";
		cout << endl;
	}

	void Clear()
	{
		_array.clear();
	}

	bool Empty()
	{
		return _array.empty();
	}

	const T& Top()
	{
		if (!Empty())
			return _array[0];
	}

	void FindNMaxNum(const T* array, int num)//查找100个数里面的前10个最大
	{
		_FindNMaxNum(array, num);
		Print();
	}

protected:
	void _AdjustDown(int root, int len) // 可以用来排序，排序后把首位互换，依次进行，最后排列成降序
	{
		int size = len - 1;
		int left = root * 2 + 1;
		int right = left + 1;
		int min = left;
		while (left < size)
		{
			if (right < size && _array[left] > _array[right])  //右边小
			{
				min = right;
			}
			else
			{
				min = left;
			}

			if (_array[root] < _array[min])
			{
				break;
			}
			else if (_array[root] > _array[min]) //左边小
			{
				swap(_array[min], _array[root]);
			}
			root = min;
			left = root * 2 + 1;
			right = left + 1;
		}
	}
	void _AdjustUp(int child)
	{
		int size = _array.size();
		int root = (child - 1) / 2;
		int left = root * 2 + 1;
		int right = left + 1;
		int min = root;
		while (root > 0)
		{
			if (right < size && _array[right] < _array[left])
				min = right;
			else
				min = left;

			if (_array[root] > _array[min])
				swap(_array[root], _array[min]);

			root = (root - 1) / 2;  //root无法小于0，所以循环条件为	root > 0
			left = root * 2 + 1;
			right = left + 1;
		}
		//当root为0时跳出循环了，需要再出循环后再判断一次
		if (right < size && _array[right] < _array[left])
			min = right;
		else
			min = left;

		if (_array[root] > _array[min])
			swap(_array[root], _array[min]);
	}

	void _FindNMaxNum(const T* array, int num)
	{
		for (int i = 0; i < 10; i++) //先填10个数，排序好
		{
			int ret = array[i];
			_array.push_back(ret);
		}
		int len = _array.size();
		int begin = len / 2 - 1;
		while (begin >= 0)
		{
			_AdjustDown(begin, len);
			begin--;
		}

		for (int i = 10; i < num; i++) //来一个数与堆顶比较一下，大则替换堆顶元素，再次排序
		{
			int ret = array[i];
			if (ret > _array[0])
			{
				_array[0] = ret;
				_AdjustDown(0, 10);
			}
		}
	}

private:
	vector<T> _array;  //借助vector来当作数据成员
};