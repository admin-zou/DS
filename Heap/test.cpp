#define _CRT_SECURE_NO_WARNINGS
#include"Heap.h"
int main()
{
	int arr[10] = { 8, 6, 4, 9, 2, 20, 3, 5, 7, 14 };
	//¶Ñ
	/*Heap<int> heap(arr,10);
	heap.Insert(1);
	heap.RemoveHeapTop();*/


	//ÓÅÏÈ¶ÓÁÐ
	/*PriorityQueue<int> pque(arr, 10);
	pque.Push(1);
	pque.Pop();
	pque.Makeempty();*/

	//¶ÑÅÅÐò
	//MinHeap<int> mh(arr, 10);
	//mh.HeapSort();
	//mh.Print();

	int arry[100] ={ 12,31,26,317,82,35,2831,6,52,49,
					124,71,247,18,2,71,8,9,247,133,
					124,9,810,190,31,2,31,7,2,38,
					12,31,25,36,1,24,3,16,24,31,
					2,5,3,41,25,6,34,12,65,31,
					42,63514,784,33,8,76,5,5,4,1,
					35,14,735,6,4,273,45,23,7,555,
					4,2,5,7,132,356,2,7,8,58,
					7,23,56,235,6285,2,6,5,8,27,
					364,32,8,4,66,2,3,4,2,39562 
				  };
	HeapSort::MinHeap<int> myhp0(arr,10);
	myhp0.Insert(1);
	myhp0.Print();
	HeapSort::MinHeap<int> mymp(10); //ÃüÃû¿Õ¼ä
	mymp.FindNMaxNum(arry, 100);
 
	FUNC::MinHeap<int, FUNC::LESS<int> > myhp1(arr, 10);
	myhp1.Print();
	FUNC::MinHeap<int, FUNC::BIG<int> > myhp2(arr, 10);
	myhp2.Print();
	
	FUNC::MinHeap<int, FUNC::LESS<int> > myhp3(10);
	myhp3.FindNMaxNum(arry,100);

	FUNC::MinHeap<int, FUNC::BIG<int> >myhp4(10);
	myhp4.FindNMaxNum(arry,100);
	
	return 0;
}
