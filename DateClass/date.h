#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>
#include<stdlib.h>
using namespace std;

class Date
{
public:
	Date(int year=1990, int month=1, int day=1) :_year(year), _month(month), _day(day)
	{
		if (Illegal(year, month, day))
		{
			cout << "���ڷǷ�"<<endl;
			exit(-1);
		}
	}
	Date(const Date& date)
	{
		this->_year = date._year;
		this->_month = date._month;
		this->_day = date._day;
	}
	Date& operator=(const Date& date)
	{
		if (&date != this)
		{
			this->_year = date._year;
			this->_month = date._month;
			this->_day = date._day;
		}
		return *this;
	}
	~Date()
	{}
public:
	void show()
	{
		cout << _year << "." << _month << "." << _day << endl;
	}
	Date operator+(int day) //���ı�ö������Բ��������÷���
	{
		Date tmp(*this);
		tmp._day += day;
		if (tmp._day <= 0 || tmp._day > Getday(tmp._year, tmp._month)) //��������˵����Ծ�ˣ���Ҫ����
		{
			tmp.AdjustDay();
		}	
		return tmp;
	}
	Date operator-(int day)
	{
		Date tmp(*this);
		tmp._day -= day;
		if (tmp._day <= 0 || _day > Getday(tmp._year, tmp._month))//��������˵����Ծ�ˣ���Ҫ����
		{
			tmp.AdjustDay();
		}
		return tmp;
	}
	int operator-(Date& date) //�����������С�������ϼӣ��ӵ���ȣ���Լʱ�䵫��Ч��
	{
		Date min = *this;
		Date max = date;
		int flag = 1;
		if (min > max)
		{
			Date tmp = min;
			min = max;
			max = tmp;
			flag = -1;
		}
		int count = 0;
		while (min != max)
		{
			++min;
			count++;
		}
		return flag*count;
	}

	Date& operator+=(int day)
	{
		//_day = _day + day; //��Ҫ����Adjust����
		*this = *this + day; //������+�Ѿ��������
		return *this;
	}
	Date& operator-=(int day)
	{
		//_day = _day - day; //��Ҫ����Adjust����
		*this = *this - day;//������'-'�Ѿ��������
		return *this;
	}
	Date& operator++()//ǰ��++
	{
		//_day++; //��Ҫ����Adjust����
		//if (_day > Getday(_year, _month))//��������˵�������ˣ���Ҫ����
		//{
		//	AdjustDay();
		//}
		*this += 1; //+= ���Դ���
		return *this;
	}
	Date operator++(int) //����++
	{
		Date tmp(*this);
		//_day++;
		//if (_day > Getday(_year, _month))//��������˵�������ˣ���Ҫ����
		//{
		//	AdjustDay();
		//}
		*this += 1;
		return tmp;
	}
	Date& operator--()
	{
		//_day--;
		//if (_day == 0)//��������˵�������ˣ���Ҫ����
		//{
		//	AdjustDay();
		//}
		*this -= 1;
		return *this;
	}
	Date operator--(int) //����++
	{
		Date tmp(*this);
		/*_day--;
		if (_day ==0)
		{
			AdjustDay();
		}*/
		*this -= 1;
		return tmp;
	}
	bool operator>(const Date& date)
	{
		return (_year > date._year
			|| (_year==date._year && _month>date._month)
			|| (_year==date._year && _month==date._month && _day>date._day));
	}
	bool operator<(const Date& date)
	{
		return (_year < date._year
			|| (_year==date._year && _month<date._month)
			|| (_year==date._year && _month==date._month && _day<date._day));
	}
	bool operator==(const Date& date)
	{
		return (_year == date._year && _month == date._month &&_day == date._day);
	}
	bool operator!=(const Date& date)
	{
		return !(*this == date);
	}
protected:
	bool IsLeap(int year)
	{
		return  (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
	}
	int Getday(int year,int month)
	{
		if (year < 0 || month<0 || month>12)
			exit(-1);
		static int Month[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		
		if (IsLeap(year) && month == 2)//��������������������
			return Month[2] - 1;
		
		return Month[month];
	}
	bool Illegal(int year, int month, int day)
	{
		if (year < 0 || month < 0 || month > 12 || day < 0 || day > Getday(year, month))
			return true;
		return false;
	}
	void AdjustDay() //������������������ȷ��������
	{
		if (_day >Getday(_year, _month))
		{
			while (_day > Getday(_year, _month))
			{
				_day -= Getday(_year, _month);
				_month++;
				if (_month == 13)
				{
					_month = 0;
					_year++;
				}
			}
		}
		else if (_day <= 0)
		{
			while (_day <= 0)
			{
				_month--;
				if (_month == 0)
				{
					_year--;
					_month = 12;
				}
				_day += Getday(_year, _month);
			}
		}
	}
	friend istream& operator>>(istream&in, Date& d);
	friend ostream& operator<<(ostream&out, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

istream& operator>>(istream& in, Date& d)
{
	in >> d._year;
	in >> d._month;
	in >> d._day;
	if (d.Illegal(d._year, d._month, d._day))
	{
		cout << "���ڷǷ�"<<endl;
		exit(-1);
	}
	return in;
}

ostream& operator<<(ostream& out, Date& d)
{
	out << d._year<<".";
	out << d._month<<".";
	out << d._day<<endl;
	return out;
}

//void test1()
//{
//	Date date2(2013, 1, 2);
//	date2.show();
//	date2 = date2 - 3;
//	date2.show();
//	date2 -= 3;
//	date2.show();
//	date2 += 3;
//	date2.show();
//	date2 = date2 + 3;
//	date2.show();
//}
//
//void test2()
//{
//	Date date(2005, 11, 30);
//	date.show();
//	date++;
//	date.show();
//	date--;
//	date.show();
//	date = date + 60;
//	date.show();
//	date = date + (-60);
//	date.show();
//}
//
//void test3()
//{
//	Date d1(2015, 12, 3);
//	Date d2(2016, 1, 1);
//	Date d3(d2);
//	d3 = d2;
//	int ret = d1 - d2;
//	cout << ret << endl;
//	cout << d1;
//	cout << d2;
//	cout << d3;
//}
//
//void test4()
//{
//	Date d1;
//	Date d2;
//	cin >> d1;
//	cin >> d2;
//	cout << d1;
//	cout << d2;
//}
#endif