#define	_CRT_NOWANRINGS
#include"scheduling.h"

int main()
{
	int select=1;
	scheduling mytask;
	while(select)
	{
		cout<<"****************************"<<endl;
		cout<<"*   1.��ʼ��               *"<<endl;
		cout<<"*   2.�²���һ������       *"<<endl;
		cout<<"*   3.�����ȷ�������㷨   *"<<endl;
		cout<<"*   4.����ҵ�����㷨       *"<<endl;
		cout<<"*   5.��ʾ�������         *"<<endl;
		cout<<"*   0.�˳�                 *"<<endl;
		cout<<"****************************"<<endl;
		int item=0;
		cout<<"������:";
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

//��������
/*
5
1 0 4
2 2 4
3 3 3
4 5 6
5 6 3
*/