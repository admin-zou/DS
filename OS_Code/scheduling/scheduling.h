#ifndef _SCHEDULING_
#define _SCHEDULING_

#include <iostream>
#include <stdlib.h>
using namespace std;

enum Tag{UNSHD,SHD}; //标记是否被调度过

struct PCB
{
	int      pcbid;			//进程号
	size_t  arrtime;			//到达时间
	size_t  sertime;			//服务时间
	size_t  begtime;			//开始时间
	size_t  endtime;			//完成时间
	size_t  turntime;		//周转时间
	float    weighttime;		//带权周转时间
	PCB *   next;			//指向下个节点的指针
	Tag     tag;				//标记是否被调度过
	
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

/////先来先服务算法
	void FIFS()
	{
		if(empty())
		{
			cout<<"没有任务";
			exit(-1);
		}
		_clear();  //清理一下，可重复计算
		_sort_t(); //按到达时间排序
		PCB* cur = _head->next;
		while(NULL != cur)
		{
			if(_curtime < cur->arrtime)
			{ 
				_curtime = cur->arrtime; 
			}
			cur->begtime = _curtime; 
			cur->endtime = _curtime + cur->sertime;		//完成时间等于开始时间加服务时间
			cur->turntime = cur->endtime - cur->arrtime;	 //周转时间=完成时间-到达时间
			cur->weighttime  = (float)cur->turntime / (float)cur->sertime;  //带权周转时间=周转时间/服务时间
			cur->tag = SHD; //标记为已经服务
			_curtime += cur->sertime;
			cur = cur->next;
		}
	}

/////短作业

	void Short()
	{
		if (empty())
		{
			cout << "没有任务";
			exit(-1);
		}
		_clear();  //清理一下，可重复计算
		_sort_t(); //按到达时间排序
		
		PCB* cur = _head->next;
		while (NULL != cur)
		{
			if (_curtime < cur->arrtime)
			{
				_curtime = cur->arrtime;
			}
			cur->begtime = _curtime;
			cur->endtime = _curtime + cur->sertime;		//完成时间等于开始时间加服务时间
			cur->turntime = cur->endtime - cur->arrtime;	 //周转时间=完成时间-到达时间
			cur->weighttime = (float)cur->turntime / (float)cur->sertime; //带权周转时间=周转时间/服务时间
			cur->tag = SHD; //标记为已经服务
			_curtime += cur->sertime;
			cur = cur->next;
		
			//将该进程调度完的时刻已经到达的进程按短作业优先排序	
			_sort_l(cur,_curtime);  //从该进程开始进行短作业排序

		}
	}

	void Init_task()
	{
		int tasknum=0;
		size_t id=0;
		size_t atime=0;
		size_t stime=0;
		cout<<"请输入任务的个数:";
		cin>>tasknum;	
		for(int i = 0; i<tasknum;i++)
		{
			cout<<"请分别输入任务的编号,到达时间,运行时间:";
			cin>>id>>atime>>stime;
			push(id,atime,stime);
		}
	}

	void Push()
	{	
		size_t id=0;
		size_t atime=0;
		size_t stime=0;
		cout<<"请分别输入任务的编号,到达时间,运行时间:";
		cin>>id>>atime>>stime;
		push(id,atime,stime);
	}
	
	void Print()
	{
		if(empty())
			return ;
		PCB* cur = _head->next;
		printf("进程号 到达时间 服务时间 开始时间 完成时间 周转时间 带权周转时间 \n");
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
	
	bool push(int n,size_t a,size_t s) //插入到链表尾部
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

// 按照到达时间排序
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

// 按照作业长短排序
	void _sort_l(PCB*& head,size_t curtime)
	{
		if (NULL == head || NULL == head->next)
			return;
		PCB* prev = head;
		PCB* cur = prev->next;
		int size = 0;  //计算进程的数目
		PCB* tmp = head;
		while (tmp)
		{
			++size;
			tmp = tmp->next;
		}

		for (int i = 0; cur->arrtime < curtime && i < size - 1; i++)
		{
			if (prev->arrtime > curtime)
			{//作业还没到达就不排序
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
	size_t  _tasknum;	//作业个数
};

#endif