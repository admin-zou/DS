#ifndef _STRING_
#define _STRING_

#include <iostream>
#include <assert.h>
using namespace std;



namespace DP
{



class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		 , _size(strlen(str))
		 ,_capacity(_size+1)
	{
		strcpy(_str, str);
	}
	String(const String& s) 
		:_str(new char[strlen(s._str) + 1])
		, _size(s._size)
		, _capacity(s._capacity)
	{
		strcpy(_str, s._str);
	}
	String& operator=(const String& s)
	{
		if (&s != this)
		{
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}
public:
	bool Push_back(const char ch)
	{
		Insert(_size + 1, ch);
	}	
	bool Insert(size_t pos, const char ch)
	{
 		assert(pos <= _size);
		_checkCapacity(_size + 2);   //需要加2不能为1，否则会导致内存溢出
		int end = _size;			   //下标不能为_size+1（可能会越界）
		while (end > pos)		   //注意越界问题（无符号数）
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_str[pos] = ch;
		++_size;
		return true;
	}
	bool Insert(size_t pos, const char* str)   //kmp算法
	{
		assert(pos <= _size);
		int len = strlen(str);
		_checkCapacity(_size + len + 1);
		int begin = _size + len;
		int end = _size;
		while (begin >= pos+len)
		{
			_str[begin--] = _str[end--];
		}
		while (len)
		{
			_str[pos++] = *str++;
			len--;
		}
		_size+=len;
		return true;
	}
	size_t Find(const char ch)
	{
		for (int i = 0; i < _size; i++)
		{
			if (ch == _str[i])
			{
				return i;
			}
		}
		return -1;
	}
	int Find(const char* str) 
	{
		assert(str);
		char* pristr=_str; //主串
		int len = strlen(str);
		if (len == 1)  //长度为1的字符串，相当于查找单个字符
		{
			int pos = Find(*str);
			if (-1 == pos)
				return NULL;
			return Find(*str);
		}
		int* next = new int[len];
		memset(next, 0, sizeof(int)*len);
		_next(str, next); // next数组已经构造好了
		int s = 0;  // 主串下标
		int t = 0;  // 子串下标
		while (t < len && s<_size)
		{
			if (pristr[s] == str[t])
			{
				if (t == len - 1) //成功匹配
					return (s-t);
				++s;
				++t;
			}
			else //不相等
			{
				if (next[t] == -1)  //第一个都不匹配，子串与主串失败的下一个位置比较
				{
					++s;
					t = 0;
					continue;
				}
				t = next[t];		  //前面的已经匹配，不用再比较了
			}
		}
		return -1;
	}	
	void Erase(size_t pos)
	{
		assert(pos < _size);
		int begin = pos;
		while (begin < _size)
		{
			_str[begin++] = _str[begin + 1];
		}
		--_size;
	}
	bool operator>(const String& s)
	{
		char* str1 = _str;
		char* str2 = s._str;
		while (*str1 && *str2)
		{
			if (*str1 > *str2)
			{
				return true;
			}
			else if (*str1 < *str2)
			{
				return false;
			}
			else
			{
				++str1;
				++str2;
			}
		}
		if (*str1)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}
	bool operator==(const String& s)
	{
		char* str1 = _str;
		char* str2 = s._str;
		while (*str1&&*str2)
		{
			if (*str1 == *str2)
			{
				++str1;
				++str2;
			}
			else
			{
				return false;
			}
		}
		if (*str1 || *str2)
		{
			return false;
		}
		return true;
	}
	bool operator<(const String& s)
	{
		return !((*this > s) || (*this == s));
	}
	bool operator>=(const String& s)
	{
		return ((*this > s) || (*this == s));
	}
	bool operator<=(const String& s)
	{
		return !(*this > s);
	}
	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}
private:
	void _checkCapacity(size_t capacity)
	{
		if (capacity > _capacity)
		{
			size_t newCapacity = capacity > 2 * _capacity ? capacity : 2 * _capacity;
			char* _newstr = new char[newCapacity];
			strcpy(_newstr, _str);
			delete[] _str;
			_str = _newstr;
			_capacity = newCapacity;
		}
	}
	void _next(const char* str, int* arr) //构造next数组
	{
		int len = strlen(str);
		arr[0] = -1;  //0下标标记为-1 ，1 下标一般标记为0
		/*if (len <= 1)   //长度小于2已经考虑了
			return;
		*/
		int pos1 = 2;
		int pos2 = 0;
		for (int i = 2; i < len; i++)
		{
			if (pos1 <= i && str[pos1 - 1] == str[pos2])
			{
				arr[i] = arr[i - 1] + 1;     //若前面已经出现了前缀后缀匹配，则next值加一
				pos2++;
			}
			else
			{
				if (str[pos1 - 1] == str[0]) //前面的匹配失败，可能存在新的前缀后缀匹配
				{
					arr[i] = 1;
					pos2 = 1;
				}
			}
			++pos1;
		}
	}
private:
	char*	_str;
	size_t	_size;			//将\0计数
	size_t	_capacity;
};


}

void test1()
{
	DP::String s1("helloa d");
	s1.Erase(5);
	s1.Insert(6, 'w');
	s1.Insert(7, "orl");
}
void test2()
{
	DP::String s1("abababaababacbd");
	cout << s1.Find("ababacb") << endl;
	cout << s1.Find("baababac") << endl;
	cout << s1.Find("abcdefg") << endl;
}


#endif