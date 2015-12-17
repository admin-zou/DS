#include <iostream>
using namespace std;

enum NodeType
{
	HEAD_TYPE,		  // ͷ�ڵ�
	VALUE_TYPE,	     //  ֵ�ڵ�
	SUB_TYPE,	     //  �ӽڵ�
};

struct GeneralListNode
{
	NodeType _type;
	GeneralListNode* next;
	union 
	{
		char _Value;
		GeneralListNode * _SubListLink;
	};
   
	GeneralListNode(NodeType Type = HEAD_TYPE, char val = '\0') :next(NULL), _type(Type)
	{
		if (Type == VALUE_TYPE)
		{	_Value = val; }
		else if (Type == SUB_TYPE)
		{	_SubListLink = NULL; }
	}
};

class GeneralList
{
public:
	GeneralList(const char* str)
	{
		_GreateGeneralList(head,str);
	}

	GeneralList(GeneralList& gl)
	{
		head = _CopyGeneralList(gl.head);
	}

	/*GeneralList& operator=(GeneralList gl)  //��ֵ���
	{
		swap(head,gl.head);
		return *this;
	}*/

	GeneralList& operator=(const GeneralList& gl) //��ֵ���
	{
		if (&gl != this)
		{ 
			_Distory();
			head = _CopyGeneralList(gl.head);
		}
		return *this;
	}

	~GeneralList()
	{
		_Distory();
	}
public:
	void Deep()
	{	cout << Deep(head) << endl;}

	void Length()
	{	cout << "Length:" << Length(head)<< endl; }

	void Print()
	{
		cout << "(";
			_Print(head->next);
		cout << endl;
	}

	void _Distory()
	{
		_Distory(head);
	}
protected:
	bool IsRigt(const char ch)
	{
		if (ch >= '0' && ch <= '9' || ch >= 'a'&& ch <= 'z' || ch >= 'A'&& ch <= 'Z')
		{
			return true;
		}
		return false;
	}	
	
	void _GreateGeneralList(GeneralListNode*& begin,const char*& str)
	{//����������ʱ��ŵݹ鴴��
		if (*str != '(')
		{
			cout << "failed";
			return;
		}
		str++;
			//ͷ�ڵ�
		GeneralListNode* Cur;
		GeneralListNode* HeadNode = new GeneralListNode(HEAD_TYPE);
		begin = HeadNode;
		Cur = begin;
		while (*str != '\0' &&  *str != ')')
		{
			//ֵ�ڵ�
			if (IsRigt(*str))
			{
				GeneralListNode* ValNode = new GeneralListNode(VALUE_TYPE, *str);
				Cur->next = ValNode;
				Cur = ValNode;
			}
			//�ӱ�
			else if (*str == '(')
			{
				GeneralListNode* SubNode = new GeneralListNode(SUB_TYPE);
				Cur->next = SubNode;
				_GreateGeneralList(SubNode->_SubListLink, str);
				Cur = SubNode;
			}
			//�������
			else if (*str == ')')
			{
				return ;
			}
			//�ո񣬻򶺺�
			str++;
		}		
	}

	void _Distory(GeneralListNode* g)
	{
		if (g == NULL)
			return;
		GeneralListNode* cur = g;
		GeneralListNode* delNode;
		while (cur)
		{
			if (cur->_type == HEAD_TYPE || cur->_type == VALUE_TYPE)
			{
				delNode = cur;
				cur = cur->next;
				delete delNode;
			}
			else if (cur->_type == SUB_TYPE)
			{
				delNode = cur;
				_Distory(cur->_SubListLink);
				cur = cur->next;
				delete delNode;
			}
		}

	}

	GeneralListNode* _CopyGeneralList(GeneralListNode* head)
	{
		GeneralListNode* NewNode = new GeneralListNode(HEAD_TYPE);
		GeneralListNode* PNode = NewNode;
		GeneralListNode* cur = head->next;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE) //����ֵ�ڵ�
			{
				PNode->next = new GeneralListNode(VALUE_TYPE, cur->_Value);
				PNode = PNode->next;
				cur = cur->next;
			}
			else if (cur->_type == SUB_TYPE) //�������ֱ�
			{
				PNode->next = new GeneralListNode(SUB_TYPE);
				PNode = PNode->next;
				PNode->_SubListLink = _CopyGeneralList(cur->_SubListLink); //�����ֱ�
				cur = cur->next;
			}
		}
		return NewNode;
	}

	void _Print(GeneralListNode*& begin)
	{
		if (begin == NULL)
		{
			cout << ")";
		}
		else if (begin->_type == VALUE_TYPE)
		{
			cout << begin->_Value;
			if (begin->next != NULL)
				cout << ",";
			_Print(begin->next);
		}
		else if(begin->_type == SUB_TYPE)
		{
			_Print(begin->_SubListLink);
			if (begin->next != NULL)
				cout << ",";
			_Print(begin->next);
		}
		else
		{
			cout << "(";
			_Print(begin->next);
		}
	}

	int Length(GeneralListNode*& head)
	{
		int len = 0;
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				len++;
			}
			else if (cur->_type == SUB_TYPE)
			{
				len += Length(cur->_SubListLink);
			}
			cur = cur->next;
		}
		return len;
	}

	int Deep(GeneralListNode*& head)
	{
		int deep = 1;
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB_TYPE)
			{
				int tmp = 1 + Deep(cur->_SubListLink);
				if (tmp > deep)
					deep = tmp;
			}
			cur = cur->next;
		}
		return deep;
	}
	
private:
	GeneralListNode*  head;
};


//////////////////////////////////////////////////////////////////////////////////////////////////
//һֱ�ݹ鴴������

//void _GreateGeneralList(GeneralListNode*& begin, const char*& str)
//{
//	while (*str++ != '\0' &&  *str != ')')
//	{
//		if (*str == ',')
//			str++;
//		if (*str == '(')
//		{
//			GeneralListNode* NewSubNode = new GeneralListNode(SUB_TYPE);
//			begin->next = _SubListLink;
//			NewSubNode->_SubListLink = new GeneralListNode(HEAD_TYPE);
//			_GreateGeneralList(NewSubNode->_SubListLink, str);
//			_GreateGeneralList(_SubListLink, str);
//		}
//		else
//		{
//			GeneralListNode* NewNode = new GeneralListNode(VALUE_TYPE, *str);
//			begin->next = NewNode;
//			_GreateGeneralList(NewNode, str);//���õݹ飬ֱ����ǰ��
//		}
//		return;
//	}
//}

////���
/*int Deep(GeneralListNode*& cur, int& tp, int& dp)
{
if (cur == NULL)
{
if (tp > dp)
{
dp = tp;
tp = 1;
}
return dp;
}
if (cur->_type == SUB_TYPE)
{
++tp;
Deep(cur->_SubListLink, tp, dp);
Deep(cur->next, tp, dp);
}
else
{
Deep(cur->next, tp, dp);
}
return dp;
}*/
////�󳤶�
/*int Length(GeneralListNode*& cur, int& count)
{
if (cur == NULL)
{	return count;}
else if (cur->_type == SUB_TYPE)
{
Length(cur->_SubListLink, count);
Length(cur->next, count);
}
else if (cur->_type == VALUE_TYPE)
{
++count;
Length(cur->next, count);
}
else
{
Length(cur->next, count);
}
return count;
}*/