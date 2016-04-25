#define _CRT_SECURE_NO_WARNINGS
#include "firstfit.h"

//void test1()
//{
//	FIRSTFIT::Firstfit task(512);
//	task.push(1,30);
//	task.push(2, 20);
//	task.push(3, 50);
//	task.push(4, 20);
//	task.push(5, 60);
//	task.PrintMemList();
//	task.pop(3);
//	task.PrintMemList();
//	//task.pop(1);
//	task.push(6, 10);
//	task.push(7, 20);
//	task.PrintMemList();
//	task.pop(5);
//	task.pop(1);
//	//task.pop(2);
//	task.PrintMemList();
//
//}
//void test2()
//{
//	BESTFIT::Firstfit task(512);
//	task.push(1, 30);
//	task.push(2, 20);
//	task.push(3, 50);
//	task.push(4, 20);
//	task.push(5, 60);
//	task.PrintMemList();
//	task.pop(1);
//	task.PrintMemList();
//	task.pop(3);
//	task.PrintMemList();
//	task.pop(2);
//	task.PrintMemList();
//}

/*
	1 30
	2 20
	3 50 
	4 20
	5 60

	3
	1

	6 10
	7 20

	2
	5
*/
int main()
{
	FIRSTFIT::Firstfit task1(512);
	FIRSTFIT::Firstfit task2(512);
	int select = 1;
	while (select)
	{
		cout << "|------------------------------------------|" << endl;
		cout << "|  0.退出                                  |" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "|首次适应算法                              |" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "|  1.添加进程           2.删除一个进程     |" << endl;
		cout << "|  3.查看空闲链表       4.打印进程地址     |" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "|最佳适应算法                              |" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "| 5.添加进程           6.删除一个进程      |" << endl;
		cout << "| 7.查看空闲链表       8.打印进程地址      |" << endl;
		cout << "|------------------------------------------|" << endl;
		cout << "请输入:";
		cin >> select;
		switch (select)
		{
		case 0:
			exit(0);
			break;
		case 1:
			task1.push();
			break;
		case 2:
			task1.pop();
			break;
		case 3:
			task1.PrintMemList();
			break;
		case 4:
			task1.PrintPcbMem();
			break;
		case 5:
			task2.push();
			break;
		case 6:
			task2.pop();
			break;
		case 7:
			task2.PrintMemList();
			break;
		case 8:
			task2.PrintPcbMem();
			break;
		default:
			break;
		}
	}
	
	return 0;
}
