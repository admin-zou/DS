#ifndef _SCHEDULING_
#define _SCHEDULING_

#include <iostream>
#include <stdlib.h>
using namespace std;

enum Tag{UNSHD,SHD}; //����Ƿ񱻵��ȹ�

struct PCB
{
	int      pcbid;			//���̺�
	size_t  arrtime;			//����ʱ��
	size_t  sertime;			//����ʱ��
	size_t  begtime;			//��ʼʱ��
	size_t  endtime;			//���ʱ��
	size_t  turntime;		//��תʱ��
	float    weighttime;		//��Ȩ��תʱ��
	PCB *   next;			//ָ���¸��ڵ��ָ��
	Tag     tag;				//����Ƿ񱻵��ȹ�
	
	PCB(int n=0,size_t a=0,size_t s=0)
		:pcbid(n),arrtime(a),sertime(s),begtime(0),endtime(0)
		,turntime(0),weighttime(0),next(NULL),tag(UNSHD)
	{}
};

class scheduling
{
public:
	scheduling():_curtime(0),_tasknum(0)
	{
		_head = new PCB();
	}

/////�����ȷ����㷨
	void FIFS()
	{
		if(empty())
		{
			cout<<"û������";
			exit(-1);
		}
		_clear();  //����һ�£����ظ�����
		_sort_t(); //������ʱ������
		PCB* cur = _head->next;
		while(NULL != cur)
		{
			if(_curtime < cur->arrtime)
			{ 
				_curtime = cur->arrtime; 
			}
			cur->begtime = _curtime; 
			cur->endtime = _curtime + cur->sertime;		//���ʱ����ڿ�ʼʱ��ӷ���ʱ��
			cur->turntime = cur->endtime - cur->arrtime;	 //��תʱ��=���ʱ��-����ʱ��
			cur->weighttime  = (float)cur->turntime / (float)cur->sertime;  //��Ȩ��תʱ��=��תʱ��/����ʱ��
			cur->tag = SHD; //���Ϊ�Ѿ�����
			_curtime += cur->sertime;
			cur = cur->next;
		}
	}

/////����ҵ

	void Short()
	{
		if (empty())
		{
			cout << "û������";
			exit(-1);
		}
		_clear();  //����һ�£����ظ�����
		_sort_t(); //������ʱ������
		
		PCB* cur = _head->next;
		while (NULL != cur)
		{
			if (_curtime < cur->arrtime)
			{
				_curtime = cur->arrtime;
			}
			cur->begtime = _curtime;
			cur->endtime = _curtime + cur->sertime;		//���ʱ����ڿ�ʼʱ��ӷ���ʱ��
			cur->turntime = cur->endtime - cur->arrtime;	 //��תʱ��=���ʱ��-����ʱ��
			cur->weighttime = (float)cur->turntime / (float)cur->sertime; //��Ȩ��תʱ��=��תʱ��/����ʱ��
			cur->tag = SHD; //���Ϊ�Ѿ�����
			_curtime += cur->sertime;
			cur = cur->next;
		
			//���ý��̵������ʱ���Ѿ�����Ľ��̰�����ҵ��������	
			_sort_l(cur,_curtime);  //�Ӹý��̿�ʼ���ж���ҵ����

		}
	}

	void Init_task()
	{
		int tasknum=0;
		size_t id=0;
		size_t atime=0;
		size_t stime=0;
		cout<<"����������ĸ���:";
		cin>>tasknum;	
		for(int i = 0; i<tasknum;i++)
		{
			cout<<"��ֱ���������ı��,����ʱ��,����ʱ��:";
			cin>>id>>atime>>stime;
			push(id,atime,stime);
		}
	}

	void Push()
	{	
		size_t id=0;
		size_t atime=0;
		size_t stime=0;
		cout<<"��ֱ���������ı��,����ʱ��,����ʱ��:";
		cin>>id>>atime>>stime;
		push(id,atime,stime);
	}
	
	void Print()
	{
		if(empty())
			return ;
		PCB* cur = _head->next;
		printf("���̺� ����ʱ�� ����ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� \n");
		while(NULL != cur)
		{
			printf("%4d %6d %8d %9d %7d  %8d\t %0.2f\n",cur->pcbid, cur->arrtime ,cur->sertime ,cur->begtime, cur->endtime ,cur->turntime ,cur->weighttime);
			cur = cur->next;
		}
	}

	
protected:
	bool empty()
	{
		return _tasknum == 0;
	}
	
	bool push(int n,size_t a,size_t s) //���뵽����β��
	{
		PCB * newtask = new PCB(n,a,s);
		PCB * cur = _head;
		while(NULL != cur->next)
			cur =cur->next;
		cur->next=newtask;
		_tasknum++;
		return true;
	}
	
	void _clear()
	{
		if(empty())
			return ;
		PCB* cur = _head->next;
		while(NULL != cur)
		{
			cur->begtime = 0;
			cur->endtime = 0;
			cur->turntime = 0;
			cur->weighttime = 0;
			cur->tag = UNSHD;
			cur = cur->next ;
		}
		_curtime = 0;
	}

// ���յ���ʱ������
	void _sort_t() 
	{
		if(empty() || _tasknum == 1)
			return;
		PCB* prev = _head->next;
		PCB* cur = prev->next;
		for(int i = 0; i< _tasknum-1; i++)
		{
			for(int j = 0; j<_tasknum-i-1; j++)
			{
				if (prev->arrtime > cur->arrtime)
				{
					_Swap(prev, cur);
				}
				prev = cur;
				cur = cur->next;
			}
			prev=_head->next;
			cur = prev->next;
		}
	}

// ������ҵ��������
	void _sort_l(PCB*& head,size_t curtime)
	{
		if (NULL == head || NULL == head->next)
			return;
		PCB* prev = head;
		PCB* cur = prev->next;
		int size = 0;  //������̵���Ŀ
		PCB* tmp = head;
		while (tmp)
		{
			++size;
			tmp = tmp->next;
		}

		for (int i = 0; cur->arrtime < curtime && i < size - 1; i++)
		{
			if (prev->arrtime > curtime)
			{//��ҵ��û����Ͳ�����
				return;
			}
			for (int j = 0; j < size - i - 1; j++)
			{
				if (cur && cur->arrtime <= curtime)
				{
					int ptime = prev->sertime;
					int ctime = cur->sertime;
					if (ptime > ctime)
					{
						_Swap(prev, cur);
					}
				}
				prev = cur;
				cur = cur->next;
			}
			prev = head;
			cur = prev->next;
		}
	}

	void _Swap(PCB * prev,PCB * cur)
	{
		swap(prev->arrtime,cur->arrtime);
		swap(prev->pcbid ,cur->pcbid );
		swap(prev->sertime ,cur->sertime );
	}

private:
	PCB *	_head;
	size_t  _curtime;	
	size_t  _tasknum;	//��ҵ����
};

#endif