#define _CRT_SECURE_NO_WARNINGS

#include"date.h"

int main()
{
	int select=1;
	while (select)
	{
		cout << "**************************************" << endl;
		cout << "*            1.推算日期              *" << endl;
		cout << "*            2.计算日期差            *" << endl;
		cout << "*            0.退出                  *" << endl;
		cout << "**************************************" << endl;
		cout << "请输入:";
		cin >> select;
		if (select == 0)
		{}
		if (select == 1)
		{
			cout << "请输入日期和天数:";
			Date d1;
			int days;
			cin >> d1;
			cin >> days;
			cout << d1 + days<<endl;
		}
		else if (select == 2)
		{
			cout << "请输入两个日期:"<<endl;
			Date d1;
			Date d2;
			cin >> d1;
			cin >> d2;
			cout << d1 - d2;
		}
	}
	
	return 0;
}
