#pragma once
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

//��ӡ����
void PrintArr(int* arr, int size)
{
	assert(arr && size>0);
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}


//1.ð������
void BubbleSort(int* arr, int size)
{
	assert(arr && size > 0);
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = 0;  //�����Ż�������
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


//2.��������
void InsertSort(int* arr, int size)
{
	assert(arr && size > 0);
	for (int i = 1; i < size; ++i)
	{
		int tmp = arr[i];  //��ʱ��Ÿ�ֵ
		int j = i-1;
		while (j >= 0 && arr[j] >= tmp)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j+1] = tmp;
	}
}


//3.ѡ������
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

		if (min == right && max == left)  //��������������λᵼ�´���(���εݼ�)
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


//4.������
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

		if (arr[begin] < arr[max])  //����Ҷ��С���򽻻�
		{
			swap(arr[begin], arr[max]);
		}
		else  //�����˳�
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
	
	//����
	int root = size / 2 - 1;
	while (root >= 0)
	{
		AdjustDown(arr, root, size);
		--root;
	}

	//����
	int begin = size-1; 
	while (begin)
	{
		swap(arr[0], arr[begin]);
		AdjustDown(arr, 0, begin);
		--begin;
	}
}


//5.ϣ������
void ShellSort(int * arr, int size)
{
	assert(arr && size > 1);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;  //ѡ��gap
		for (int i = 0; i < gap; ++i)
		{
			for (int j = i+gap; j < size; j = j + gap) //��gapΪ�����������
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


//6.��������1��������ʽ�ģ����ݹ�ͷǵݹ飩
void QuickSort1(int* arr, int size) //һ�㷽ʽ
{
	assert(arr);
	if (size <= 1)
	{
		return;
	}

	int key = arr[size - 1]; //�����һ��Ԫ��Ϊkeyֵ
	int begin = 0;
	int end = size - 2;
	while (begin < end)
	{
		while (begin<end && arr[begin] <= key)  //�Ҵ�
		{
			++begin;
		}
		while (end>begin && arr[end] >= key)	 //��С
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

	if (begin==end && arr[begin] < key)  //��������ʱ����
	{
		begin++;
	}

	if (begin != size - 1)  //���������һ���غ��ˣ��Ͳ�������
	{
		swap(arr[begin], arr[size - 1]);
	}

	QuickSort1(arr, begin);  //��ߵݹ�����,begin��ʱ��������Ԫ�صĸ���
	QuickSort1(arr + begin + 1, size - begin - 1); //�ұߵݹ�����
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
void QuickSort2(int* arr, int size) //����ȡ�з�
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
	

	QuickSort2(arr, begin); //begin��ʱ��������Ԫ�ص���Ŀ����ߵݹ�����
	QuickSort2(arr + begin + 1, size - begin - 1); //�ұߵݹ�����
}

void QuickSort3(int* arr, int size) //�ǵݹ�ʵ�ֿ�������
{
	assert(arr);
	if (size <= 1)
		return;
	stack<int> sk;

	sk.push(0); 
	sk.push(size-1);
	//ѹջ����������±꣬������Ĳ�ͬ����Ҫע��
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
			sk.push(end1-1); //��ʱѹ�����±�
		}

		int begin2 = begin + 1;
		int end2 = last;
		if (end2 - begin2 > 1)
		{
			sk.push(begin2);
			sk.push(end2); //��ʱѹ�����±�
		}
	}
}


//7.��������2�����飬����
void  QuickSort4(int* arr, int size) //���������������Ŀ���
{
	assert(arr);
	if (size <= 1)
		return;

	int pos = MidValue(arr, size); //size��ʾԪ�ظ���
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


//8.�Ż��Ŀ�������
void QuickSort5(int* arr, int size)  //����������С��13�ʹ���13
{
	assert(arr);
	if (size <= 1)
		return;

	if (size < 13)
	{//��������
		InsertSort(arr, size);
	}
	else
	{//��������
		QuickSort1(arr, size);
	}
}


//9.�鲢���򣨵ݹ�ͷǵݹ飩
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

//10.��������
void CountingSort(int* arr, int size)  //��������
{//���ݼ��еĵ�ʱ��ܺ�
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
	//�Ҵ�����
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

//11.��������
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

	for (int i = left; i <= right; ++i) //ͳ��ÿλ��Ԫ�صĸ���
	{
		++count[digData(arr[i], dig)];  
	}
	for (int i = 1; i < 10; ++i) //��¼�µ���ΪԪ�صĿ�ʼ��ַ
	{
		count[i] = count[i] + count[i - 1];
	}
	for (int i = left; i <= right; ++i)  //��������Ԫ��д�븨������newArr��
	{
		int pos = digData(arr[i], dig);
		newArr[--count[pos]] = arr[i];
	}
	int j = 0;
	for (int i = left; i <= right; ++i, ++j) //������õ�Ԫ��д��arr��
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