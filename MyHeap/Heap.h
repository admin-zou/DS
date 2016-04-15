// 堆， 堆排序，  堆实现优先级队列，  仿函数实现堆

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace Heap
{

	template<class T>
	class Heap
	{//小堆
	public:
		Heap(const T* arr, int size)//建堆时间复杂度  N*lg(N)
		{
			array.reserve(size); //事先知道空间大小后，直接开辟需要的空间，不需要在插入过程中扩增容量

			for (int i = 0; i < size; i++)
			{
				array.push_back(arr[i]);
			}

			int begin = array.size() / 2 - 1;
			while (begin >= 0)
			{
				_AdjustDown(begin);
				begin--;            //从下往上调用向下排序就可以完成最小堆排序
			}
		}

		Heap(vector<T>& arr)
		{
			array = arr;
		}

		void Insert(const T& x) //时间复杂度  lg(N)
		{
			array.push_back(x);
			int begin = array.size() - 1;
			_AdjustUp(begin);
		}

		void RemoveHeapTop() //时间复杂度lg(N)
		{
			array[0] = array[array.size() - 1];
			array.pop_back();
			_AdjustDown(0);
		}

		void Clear()
		{
			array.clear();
		}

		bool Empty()
		{
			return array.empty();
		}

		const T& Top()
		{
			if (!Empty())
				return array[0];
		}

	protected:
		void _AdjustDown(int root) // 可以用来排序，排序后把首位互换，依次进行，最后排列成降序
		{
			int size = array.size();
			int left = root * 2 + 1;
			int right = left + 1;
			int min = left;
			while (left <= size)
			{
				if (right < size && array[left] > array[right])  //右边小
					min = right;
				else
					min = left;

				if (array[root] > array[min]) //左边小
					swap(array[min], array[root]);

				root = left;
				left = root * 2 + 1;
				right = left + 1;
			}
		}
		void _AdjustUp(int child)
		{
			int size = array.size();
			int root = (child - 1) / 2;
			int left = root * 2 + 1;
			int right = left + 1;
			int min = root;
			while (root > 0)
			{
				if (right < size && array[right] < array[left])
					min = right;
				else
					min = left;

				if (array[root] > array[min])
					swap(array[root], array[min]);

				root = (root - 1) / 2;  //root无法小于0，所以循环条件为	root > 0
				left = root * 2 + 1;
				right = left + 1;
			}
			//当root为0时跳出循环了，需要再出循环后再判断一次
			if (right < size && array[right] < array[left])
				min = right;
			else
				min = left;

			if (array[root] > array[min])
				swap(array[root], array[min]);
		}

	private:
		vector<T> array;  //借助vector来当作数据成员
	};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//优先级队列 
	template<class T>
	class PriorityQueue
	{
	public:
		PriorityQueue(const T* arr, int size) :_prique(arr, size)
		{
			_tasknum = size;
		}

		void Push(const T& x) //插入一个队列到对尾，并按优先级排序
		{
			_prique.Insert(x);
			_tasknum++;
		}

		void Pop() //删除最对头
		{
			if (!Empty())
			{
				_prique.RemoveHeapTop();
				--_tasknum;
			}
		}

		void Makeempty() //置空
		{
			_prique.Clear();
			_tasknum = 0;
		}

		bool Empty() //判空
		{
			return _tasknum == 0;
		}

		int Size() //大小
		{
			return _tasknum;
		}
	private:
		Heap<T>  _prique;
		int		 _tasknum;
	};


}




namespace HeapSort
{


	//堆排序 //求100个数中的前10个最大数
	template<class T>
	class BigData;

	template<class T>
	class MinHeap
	{//小堆
		friend class BigData<T>;
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
			for (int i = 0; i < len; i++)
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

		//查找100个数里面的前10个最大
		void FindNMaxNum(const T* array, int num)
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
			while (left <= size)
			{
				if (right <= size && _array[left] > _array[right])  //右边小
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
			for (int i = 0; i < 10; i++)
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
			for (int i = 10; i < num; i++)
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



}





namespace FUNC
{


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//仿函数实现堆 （重载括号 operator()）

	template<class T>
	class LESS
	{
	public:
		bool operator() (const T& left, const T& right)
		{
			return left > right;
		}
	};

	template<class T>
	class BIG
	{
	public:
		bool operator() (const T& left, const T& right)
		{
			return left < right;
		}
	};



	template<class T, class Container>
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
				_AdjustDown(begin, len); //从下往上调用向下排序就可以完成最小堆排序
				begin--;           
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
			for (int i = 0; i < len; i++)
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
			int key = left;
			while (left <= size)
			{//Container()仿函数
				if (right < size && Container()(_array[left],_array[right]))  //右边小
				{
					key = right;
				}
				else
				{
					key = left;
				}

				if (Container()(_array[key], _array[root]))
				{
					break;
				}
				else if (Container()(_array[root],_array[key])) //左边小
				{
					swap(_array[key], _array[root]);
				}
				root = key;
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
				if (right < size && Container()(_array[right],_array[left]))
					min = right;
				else
					min = left;

				if (Container()(_array[root],_array[min]))
					swap(_array[root], _array[min]);

				root = (root - 1) / 2;  //root无法小于0，所以循环条件为	root > 0
				left = root * 2 + 1;
				right = left + 1;
			}
			//当root为0时跳出循环了，需要再出循环后再判断一次
			if (right < size &&  Container()(_array[left], _array[right]))
				min = right;
			else
				min = left;

			if (Container()(_array[root],_array[min]))
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
				if (Container()(ret,_array[0]))
				{
					_array[0] = ret;
					_AdjustDown(0, 10);
				}
			}
		}

	private:
		vector<T> _array;  //借助vector来当作数据成员
	};


}