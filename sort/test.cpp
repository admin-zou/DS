#define _CRT_SECURE_NO_WARNINGS
#include"Sort.h"

int main()
{
//4个测试用例
	//int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int array[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }; 
	//int array[10] = { 0, 1, 5, 3, 7, 6, 2, 4, 8, 9 };
	//int array[10] = { 1, 3, 5, 0, 7, 6, 9, 8, 4, 2 };
	

	//int arrayTest[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,23,45,32,77,29};
	
	//BubbleSort(array, 10);

	//InsertSort(array, 10);

	SelectSort(array, 10);

	//HeapSort(array, 10);

	//ShellSort(array, 10);

//快速排序
	//数组形式newArr[]的快排
	//QuickSort1(array, 10);
	//QuickSort2(array, 10);
	//QuickSort3(array, 10);
	//可用于数组和链表的快排
	//QuickSort4(array, 10);
	//优化的快速排序
	// QuickSort5(arrayTest, 15);
	//PrintArr(arrayTest, 15);
	//QuickSort5(array, 10);

	//MergeSort(array, 10);

	//RadixSort(array, 10, 1);
	//CountingSort(array, 10);
	PrintArr(array, 10);



	//int array[12] = {332,633,59,589,232,664,179,457,825,714,405,361}; //基数排序数组
	//RadixSort(array, 12, 3);
	//PrintArr(array, 12);
	
	return 0;
}
