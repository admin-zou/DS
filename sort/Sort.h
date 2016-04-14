#pragma once
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

//打印数组
void PrintArr(int* arr, int size)
{
	assert(arr && size>0);
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}


//1.冒泡排序
void BubbleSort(int* arr, int size)
{
	assert(arr && size > 0);
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = 0;  //用于优化该排序
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j + 1] < arr[j])
			{
				swap(arr[j + 1], arr[j]);
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}


//2.插入排序
void InsertSort(int* arr, int size)
{
	assert(arr && size > 0);
	for (int i = 1; i < size; ++i)
	{
		int tmp = arr[i];  //暂时存放该值
		int j = i-1;
		while (j >= 0 && arr[j] >= tmp)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j+1] = tmp;
	}
}


//3.选择排序
void SelectSort(int *arr,int size)
{
	assert(arr && size > 0);
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int max = left;
		int min = left;
		for (int i = left + 1; i <= right; ++i)
		{
			if (arr[i]>arr[max])
				max = i;
			if (arr[i] < arr[min])
				min = i;
		}

		if (min == right && max == left)  //此种情况交换两次会导致错误(依次递减)
		{
			swap(arr[min], arr[max]);
			++left;
			--right;
			continue;
		}

		if (min != left)
		{
			swap(arr[left], arr[min]);
		}
		
		if (max != right)
		{
			swap(arr[right], arr[max]);
		}
		
		++left;
		--right;
	}
}


//4.堆排序
void AdjustDown(int* arr, int root, int size)
{
	int begin = root;
	int left = 2 * root + 1;
	int right = left + 1;
	while (left < size)
	{
		int max = left;
		if (right<size && arr[right]>arr[max])
		{
			max = right;
		}

		if (arr[begin] < arr[max])  //根比叶子小，则交换
		{
			swap(arr[begin], arr[max]);
		}
		else  //否则，退出
		{
			break;
		}

		begin = max;
		left = begin * 2 + 1;
		right = left + 1;
	}
}
void HeapSort(int* arr, int size)
{
	assert(arr && size > 0);
	
	//建堆
	int root = size / 2 - 1;
	while (root >= 0)
	{
		AdjustDown(arr, root, size);
		--root;
	}

	//排序
	int begin = size-1; 
	while (begin)
	{
		swap(arr[0], arr[begin]);
		AdjustDown(arr, 0, begin);
		--begin;
	}
}


//5.希尔排序
void ShellSort(int * arr, int size)
{
	assert(arr && size > 1);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;  //选择gap
		for (int i = 0; i < gap; ++i)
		{
			for (int j = i+gap; j < size; j = j + gap) //以gap为间隔插入排序
			{
				int tmp = arr[j];
				int k = j - gap;
				while (k>=0 && arr[k]>tmp)
				{
					arr[k + gap] = arr[k];
					k -= gap;
				}
				arr[k + gap] = tmp;
			}
		}
	}
}


//6.快速排序1（数组形式的）（递归和非递归）
void QuickSort1(int* arr, int size) //一般方式
{
	assert(arr);
	if (size <= 1)
	{
		return;
	}

	int key = arr[size - 1]; //以最后一个元素为key值
	int begin = 0;
	int end = size - 2;
	while (begin < end)
	{
		while (begin<end && arr[begin] <= key)  //找大
		{
			++begin;
		}
		while (end>begin && arr[end] >= key)	 //找小
		{
			--end;
		}
		
		if (arr[begin] > arr[end])
		{
			swap(arr[begin], arr[end]);
			++begin;
			--end;
		}
	}

	if (begin==end && arr[begin] < key)  //避免逆序时出错
	{
		begin++;
	}

	if (begin != size - 1)  //若它和最后一个重合了，就不交换了
	{
		swap(arr[begin], arr[size - 1]);
	}

	QuickSort1(arr, begin);  //左边递归排序,begin此时代表数组元素的个数
	QuickSort1(arr + begin + 1, size - begin - 1); //右边递归排序
}

int MidValue(int* arr, int size)
{
	if (size == 1)
		return 0;

	int left = arr[0];
	int right = arr[size - 1];
	int mid = arr[(size - 1) / 2];

	if (left > right)
	{
		if (mid>left)
			return 0;
		else
		{
			if (mid < right)
				return size-1;
			else
				return (size-1)/2;
		}
	}
	else
	{
		if (mid>right)
			return (size - 1);
		else
		{
			if (mid < left)
				return 0;
			else
				return (size - 1) / 2;
		}
	}
}
void QuickSort2(int* arr, int size) //三数取中法
{
	assert(arr);
	if (size <= 1)
		return;
	int pos = MidValue(arr, size);
	swap(arr[pos], arr[size - 1]);
	int key = arr[size - 1];

	int begin = 0;
	int end = size - 2;
	while (begin < end)
	{
		while (begin<end && arr[begin] <= key)
		{
			++begin;
		}
		while (end>begin && arr[end] >= key)
		{
			--end;
		}

		if (arr[begin] > arr[end])
		{
			swap(arr[begin], arr[end]);
			++begin;
			--end;
		}
	}

	if (begin == end && arr[begin] < key)
	{
		++begin;
	}
	if (begin != size-1)
		swap(arr[begin], arr[size-1]);
	

	QuickSort2(arr, begin); //begin此时代表数组元素的数目，左边递归排序
	QuickSort2(arr + begin + 1, size - begin - 1); //右边递归排序
}

void QuickSort3(int* arr, int size) //非递归实现快速排序
{
	assert(arr);
	if (size <= 1)
		return;
	stack<int> sk;

	sk.push(0); 
	sk.push(size-1);
	//压栈的是数组的下标，与上面的不同，需要注意
	while (!sk.empty())
	{
		int last = sk.top();
		sk.pop();
		int first = sk.top();
		sk.pop();
		int begin = first;
		int end = last-1;
		int key = arr[end+1];
		while (begin < end)
		{
			while (begin < end && arr[begin] <= key)
			{
				++begin;
			}
			while (end>begin && arr[end] >= key)
			{
				--end;
			}
			
			if (arr[begin] > arr[end])
				swap(arr[begin], arr[end]);
		}
		if (begin == end && arr[begin] < key)
			begin++;
		if (begin != end + 1)
			swap(arr[begin], arr[last]);
		
		int begin1 = first;
		int end1 = begin;
		if (end1 - begin1 > 1)
		{
			sk.push(begin1);
			sk.push(end1-1); //此时压的是下标
		}

		int begin2 = begin + 1;
		int end2 = last;
		if (end2 - begin2 > 1)
		{
			sk.push(begin2);
			sk.push(end2); //此时压的是下标
		}
	}
}


//7.快速排序2（数组，链表）
void  QuickSort4(int* arr, int size) //可用于数组和链表的快排
{
	assert(arr);
	if (size <= 1)
		return;

	int pos = MidValue(arr, size); //size表示元素个数
	swap(arr[pos], arr[size - 1]);
	int key = arr[size - 1];

	int prev = -1;
	int cur = 0;
	while (cur < size)
	{
		if (arr[cur] < key)
		{
			++prev;
			if (prev != cur)
				swap(arr[prev], arr[cur]);
		}
		++cur;
	}

	swap(arr[++prev],arr[size-1]);

	QuickSort4(arr,prev);
	QuickSort4(arr+prev+1,size-prev-1);
}


//8.优化的快速排序
void QuickSort5(int* arr, int size)  //按区间排序，小于13和大于13
{
	assert(arr);
	if (size <= 1)
		return;

	if (size < 13)
	{//插入排序
		InsertSort(arr, size);
	}
	else
	{//快速排序
		QuickSort1(arr, size);
	}
}


//9.归并排序（递归和非递归）
void doMerge(int* newArr, int left, int right)
{
	assert(newArr);
	if (left == right)
		return;
	int mid = left + (right - left) / 2;
	doMerge(newArr, left, mid);
	doMerge(newArr, mid + 1, right);
	for (int i = left + 1; i <= right; ++i)
	{
		int tmp = newArr[i];
		int end = i-1;
		while (end >= left && newArr[end] > tmp)
		{
			newArr[end+1] = newArr[end];
			--end;
		}
		newArr[end+1] = tmp;
	}
}
void Merge(int* arr, int* newArr, int left, int mid, int right)
{
	assert(arr);
	assert(newArr);
	if (left == right)
		return;
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	int pos = 0;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (newArr[begin1] <= newArr[begin2])
		{
			arr[pos++] = newArr[begin1++];
		}
		else
		{
			arr[pos++] = newArr[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		arr[pos++] = newArr[begin1++];
	}
	while (begin2 <= end2)
	{
		arr[pos++] = newArr[begin2++];
	}
}
void MergeSort(int* arr, int size)
{
	assert(arr);
	if (size <= 1)
		return;

	int left = 0;
	int right = size - 1;
	int mid = (size-1) / 2;

	int * newArr = new int[size];
	memcpy(newArr, arr, sizeof(int)*size);
	assert(newArr);

	doMerge(newArr, left, mid);
	doMerge(newArr, mid + 1, right);
	Merge(arr, newArr, left, mid, right);
}

//10.计数排序
void CountingSort(int* arr, int size)  //计数排序
{//数据集中的的时候很好
	assert(arr);
	if (size <= 1)
		return;

	int min = arr[0];
	int max = 0[arr];

	for (int i = 1; i < size; ++i)
	{
		if (arr[i]>max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	//找打区间
	int arrSize = max - min + 1;
	int* newArr = new int[arrSize];
	memset(newArr, 0, sizeof(int)*arrSize);
	for (int i = 0; i < size; ++i)
	{
		++newArr[arr[i] - min];
	}

	for (int j = 0 , i=0; j < arrSize; ++j)
	{
		while (newArr[j] != 0)
		{
			arr[i++] = j + min;
			--newArr[j];
		}
	}
}

//11.基数排序
int digData(int data, int dig)
{
	while (--dig)
	{
		data /= 10;
	}
	return data % 10;
}
void radixSort(int* arr, int left, int  right, int dig)
{
	if (left>=right || dig < 1)
		return;

	int* count = new int[10];
	int* newArr = new int[right - left + 1];
	memset(count, 0, sizeof(int)* 10);
	memset(newArr, 0, sizeof(int)* (right - left + 1));

	for (int i = left; i <= right; ++i) //统计每位的元素的个数
	{
		++count[digData(arr[i], dig)];  
	}
	for (int i = 1; i < 10; ++i) //记录新的以为元素的开始地址
	{
		count[i] = count[i] + count[i - 1];
	}
	for (int i = left; i <= right; ++i)  //将排序后的元素写入辅助数组newArr中
	{
		int pos = digData(arr[i], dig);
		newArr[--count[pos]] = arr[i];
	}
	int j = 0;
	for (int i = left; i <= right; ++i, ++j) //将排序好的元素写回arr中
	{
		arr[i] = newArr[j];
	}
	
	for (int i = 0; i < 10; i++)
	{
		int first = count[i];
		int last = count[i + 1] - 1;
		radixSort(arr, first, last, dig - 1);
	}
}

void RadixSort(int* arr, int size,int dig)
{
	assert(arr);
	if (size <= 1 || dig < 1)
		return;
	
	int left = 0;
	int right = size - 1;
	radixSort(arr, left, right, dig);
}