#define	_CRT_NOWANRINGS
#include"scheduling.h"

int main()
{
	int select=1;
	scheduling mytask;
	while(select)
	{
		cout<<"****************************"<<endl;
		cout<<"*   1.初始化               *"<<endl;
		cout<<"*   2.新插入一个进程       *"<<endl;
		cout<<"*   3.先来先服务调度算法   *"<<endl;
		cout<<"*   4.短作业调度算法       *"<<endl;
		cout<<"*   5.显示调度情况         *"<<endl;
		cout<<"*   0.退出                 *"<<endl;
		cout<<"****************************"<<endl;
		int item=0;
		cout<<"请输入:";
		cin>>select;
		switch(select)
		{
		case 1:
			mytask.Init_task();		
			break;
		case 2:
			mytask.Push();
			break;
		case 3:
			mytask.FIFS();
			break;
        case 4:
			mytask.Short();
			break;
		case 5:
			mytask.Print();
			cout << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}

//测试条件
/*
5
1 0 4
2 2 4
3 3 3
4 5 6
5 6 3
*/