//������ //��100�����е�ǰ10�������
#pragma once
#include<iostream>
#include <vector>
using namespace std;

template<class T>
class MinHeap
{//С��
public:
	MinHeap(const T* arr, int size)//����ʱ�临�Ӷ�  N*lg(N)
	{
		_array.reserve(size); //����֪���ռ��С��ֱ�ӿ�����Ҫ�Ŀռ䣬����Ҫ�ڲ����������������

		for (int i = 0; i < size; i++)
		{
			_array.push_back(arr[i]);
		}
		int len = _array.size();
		int begin = len / 2 - 1;
		while (begin >= 0)
		{
			_AdjustDown(begin, len);
			begin--;            //�������ϵ�����������Ϳ��������С������
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

	void Insert(const T& x) //ʱ�临�Ӷ�  lg(N)
	{
		_array.push_back(x);
		int begin = _array.size() - 1;
		_AdjustUp(begin);
	}

	void Pop() //ɾ�����ͷ
	{
		if (!Empty())
		{
			swap(_array[0], _array[_array.size() - 1]);
			_AdjustDown(0, _array.size() - 1);
		}
	}

	void HeapSort() //ʱ�临�Ӷ�lg(N)
	{
		int len = _array.size();

		while (len)
		{
			swap(_array[0], _array[len - 1]); //ÿ������󣬽��Ѷ����β��������β��һ
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

	void FindNMaxNum(const T* array, int num)//����100���������ǰ10�����
	{
		_FindNMaxNum(array, num);
		Print();
	}

protected:
	void _AdjustDown(int root, int len) // ��������������������λ���������ν��У�������гɽ���
	{
		int size = len - 1;
		int left = root * 2 + 1;
		int right = left + 1;
		int min = left;
		while (left < size)
		{
			if (right < size && _array[left] > _array[right])  //�ұ�С
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
			else if (_array[root] > _array[min]) //���С
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

			root = (root - 1) / 2;  //root�޷�С��0������ѭ������Ϊ	root > 0
			left = root * 2 + 1;
			right = left + 1;
		}
		//��rootΪ0ʱ����ѭ���ˣ���Ҫ�ٳ�ѭ�������ж�һ��
		if (right < size && _array[right] < _array[left])
			min = right;
		else
			min = left;

		if (_array[root] > _array[min])
			swap(_array[root], _array[min]);
	}

	void _FindNMaxNum(const T* array, int num)
	{
		for (int i = 0; i < 10; i++) //����10�����������
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

		for (int i = 10; i < num; i++) //��һ������Ѷ��Ƚ�һ�£������滻�Ѷ�Ԫ�أ��ٴ�����
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
	vector<T> _array;  //����vector���������ݳ�Ա
};