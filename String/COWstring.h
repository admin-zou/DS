#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>
#include <assert.h>
using namespace std;

namespace COW  //写时拷贝 （引用计数）
{

	class String
	{
	public:
		String(const char* str = "")
			:_str(new char[strlen(str) + 5])
		{
			_str = _str + 4;
			_GetSize(_str)=1;
			strcpy(_str, str);
		}
		String(const String& s)
		{
			_str = s._str;
			++_GetSize(_str);
		}
		String& operator=(const String& s)
		{
			if (&s != this && _str != s._str)
			{
				_Release();
				_str = s._str;
				++*((int*)_str - 1);
			}
			return *this;
		}
		~String()
		{
			_Release();
		}
	public:
		char& operator[](int pos)
		{
			if (_GetSize(_str) > 1)
			{
				--_GetSize(_str);
				char* tmp = new char[strlen(_str) + 5];
				tmp += 4;
				strcpy(tmp, _str);
				_GetSize(tmp) = 1;
				_str = tmp;
			}
			return _str[pos];
		}
	protected:
		void _Release()
		{
			if (*((int*)_str - 1) == 0)
			{
				_str = (char*)((int*)_str - 1);
				delete[] _str;
			}
		}
		int& _GetSize(char* _ptr)
		{
			return *(int*)(_ptr - 4);
		}
	private:
		char*	_str;
	};

}

void test3()
{
	COW::String s("hehe");
	COW::String s1(s);
	COW::String s2(s1);
	COW::String s3(s2);
	COW::String s4;
	s4 = s2;
	cout << s1[2] << endl;	//operator的特性，读这个的时候也会拷贝,用const无法实现
	s1[0] = 'x';  //都没有问题，但是写的时候所有对象全部改变了，所以实现写时拷贝，谁写谁新开辟空间
}

#endif