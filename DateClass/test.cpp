#define _CRT_SECURE_NO_WARNINGS

#include"date.h"

int main()
{
	int select=1;
	while (select)
	{
		cout << "**************************************" << endl;
		cout << "*            1.��������              *" << endl;
		cout << "*            2.�������ڲ�            *" << endl;
		cout << "*            0.�˳�                  *" << endl;
		cout << "**************************************" << endl;
		cout << "������:";
		cin >> select;
		if (select == 0)
		{}
		if (select == 1)
		{
			cout << "���������ں�����:";
			Date d1;
			int days;
			cin >> d1;
			cin >> days;
			cout << d1 + days<<endl;
		}
		else if (select == 2)
		{
			cout << "��������������:"<<endl;
			Date d1;
			Date d2;
			cin >> d1;
			cin >> d2;
			cout << d1 - d2;
		}
	}
	return 0;
}
