#ifndef _MEMORY_
#define _MEMORY_

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

struct Pcb
{
	int			pcbid;
	size_t		needMem; //申请的内存大小
	size_t		realMem; //实际内存
	size_t		begin;
	size_t		end;
	Pcb*			next;

	Pcb(int id = 0, int need = 0)
		:pcbid(id), needMem(need), realMem(0), begin(0), end(0), next(NULL)
	{}
};

struct memList	//空闲链表
{
	size_t		msize;	//大小
	size_t		first;	//起始地址
	size_t		end;		//终止地址
	memList*		next;
	memList*		prev;
	memList(size_t f = 0, size_t e = 0)
		:msize(e-f),first(f), end(e), next(NULL), prev(NULL)
	{}
};

namespace FIRSTFIT   
{//首次适应算法

	class Firstfit 
	{
	public:
		Firstfit(size_t total) :_memNum(total), _blockNum(1), _pcbNum(0)
		{
			_pcbHead = new Pcb();
			_memHead = new memList(0, total);	  //全部空闲
		}

		void push()
		{
			int size = 0;
			cout << "请输入进程个数" << endl;
			cin >> size;
			for (int i = 0; i < size; ++i)
			{
				int id;
				size_t mem;
				cout << "请输入进程<编号>和<内存大小>:" << endl;
				cin >> id >> mem;
				push(id, mem);
			}
		}
		
		void push(int id, int mem)		//来了一个进程
		{
			
			Pcb* newPcb = new Pcb(id, mem);
			newPcb->next = _pcbHead->next;
			_pcbHead->next = newPcb;
			_distribute(newPcb, mem);
			++_pcbNum;
		}

		void pop()   //删除一个进程
		{
			int id = 0;
			cout << "请输入要删除的进程的<编号>:" << endl;
			cin >> id;

			//若删除第一个该怎么办
			Pcb* prev = _find(id);   //返回该进程的前一个进程
			if (NULL == prev)    //没有该进程
			{
				return;
			}
			Pcb* cur = prev->next;
			_memRecover(cur);
			prev->next = cur->next;
			delete cur;
		}

		void PrintMemList()
		{
			memList* cur = _memHead;
			int i = 1;
			while (cur)
			{
				cout << " 块:" << i++ << "地址:" << cur->first << "~" << cur->end << "---->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}

		void PrintPcbMem()
		{
			int id = 0;
			cout << "请输入进程id:";
			cin >> id;
			Pcb* cur = _find(id);
			if (cur == NULL)
			{
				cout << "is no exisit" << endl;
				return;
			}
			cur = cur->next;
			cout << cur->pcbid << ":" << cur->begin << "~" << cur->end << endl;
		}

	protected:
		bool pcbEmpty()
		{
			return _pcbHead->next == NULL;
		}

		void _distribute(Pcb* pcb, int size)
		{
			memList* cur = _memHead;
			if (size > _memNum)
			{
				return;
			}
			while (cur && cur->msize < size)
			{
				cur = cur->next;
			}

			if (NULL == cur)
			{
				cout << "内存分配失败" << endl;
				exit(-1);
			}

			pcb->begin = cur->first;
			pcb->end = pcb->begin + size;
			pcb->realMem = size;
			cur->first += size;
			_memNum -= size;
		}

		void _memRecover(Pcb* pcbptr)
		{
			size_t begin = pcbptr->begin;
			size_t end = pcbptr->end;
			size_t size = end - begin;
			memList* prev = _memHead;
			memList* cur = _memHead->next;

			if (end <= prev->first)  //在第一块前面，可能需要修改_memHead指针
			{
				if (end == prev->first)
				{
					prev->first -= size;
				}
				else if (end < prev->first)
				{
					memList* mcur = new memList(begin, end);
					mcur->next = prev;
					prev->prev = mcur;
					_memHead = mcur;
				}
				return;
			}

			while (cur)  //cur 非空
			{
				if (begin == prev->end)  //在该块的后面
				{
					if (end == cur->first) // 1.前后可以回收,则合并成一块
					{
						prev->end = cur->end;
						if (NULL != cur->next)
						{
							cur->next->prev = prev;
						}
						prev->next = cur->next;
						delete cur;
					}
					else if (end < cur->first) // 2 和前面的合并
					{
						prev->end += size;
					}
					return;
				}
				else if (begin > prev->end && end <= cur->end)
				{
					if (end == cur->first)  //3 和后面的块相邻
					{
						cur->first -= size;
					}
					else if (end < cur->first)  //4与所有前后都不能链接
					{
						memList* mcur = new memList(begin, end);
						prev->next = mcur;
						mcur->prev = prev;
						mcur->next = cur;
						cur->prev = mcur;
					}
					return;
				}
				prev = cur;
				cur = cur->next;
			}

			if (cur == NULL)   //  可能是最后的块的，或者最前面的块
			{
				if (begin == prev->end)
				{
					prev->end += size;
				}
				else if (begin > prev->end)
				{
					memList* mcur = new memList(begin, end);
					prev->next = mcur;
					mcur->prev = prev;
				}
				return;
			}
		}

		Pcb* _find(int id)
		{
			if (pcbEmpty())  //进程队列为空
			{
				return NULL;
			}
			Pcb* prev = _pcbHead;
			Pcb* cur = prev->next;
			while (cur && cur->pcbid != id)
			{
				prev = cur;
				cur = cur->next;
			}

			if (NULL == cur)  //没找到
				return NULL;
			return prev;  //找到，返回它的前一个节点
		}

	private:
		size_t		_memNum;			//总内存
		size_t		_blockNum;		//内存块
		size_t		_pcbNum;			//进程数目
		Pcb*			_pcbHead;		//进程链表
		memList*		_memHead;		//内存链表
	};

}


namespace BESTFIT   
{//最佳适应算法
	class Firstfit 
	{
	public:
		Firstfit(size_t total) :_memNum(total), _blockNum(1), _pcbNum(0)
		{
			_pcbHead = new Pcb();
			_memHead = new memList(0, total);	  //全部空闲
		}

		void push()
		{
			int size = 0;
			cout << "请输入进程个数" << endl;
			cin >> size;
			for (int i = 0; i < size; ++i)
			{
				int id;
				size_t mem;
				cout << "请输入进程<编号>和<内存大小>:" << endl;
				cin >> id >> mem;
				push(id, mem);
			}
		}

		void push(int id,size_t mem)	//来了一个进程
		{
			Pcb* newPcb = new Pcb(id, mem);
			newPcb->next = _pcbHead->next;
			_pcbHead->next = newPcb;
			_distribute(newPcb, mem);
			++_pcbNum;
		}

		void pop()   //删除一个进程
		{
			int id = 0;
			cout << "请输入要删除的进程的<编号>:" << endl;
			cin >> id;

			Pcb* prev = _find(id);   //返回该进程的前一个进程
			if (NULL == prev)    //没有该进程
			{
				return;
			}
			Pcb* cur = prev->next;
			_memRecover(cur);
			prev->next = cur->next;
			delete cur;
			_Sort(_memHead); //将空闲链表按小到大排序
		}

		void PrintMemList()
		{
			memList* cur = _memHead;
			int i = 1;
			while (cur)
			{
				cout << " 块:" << i++ << "地址:" << cur->first << "~" << cur->end << "---->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}
		void PrintPcbMem()
		{
			int id = 0;
			cout << "请输入进程id:";
			cin >> id;
			Pcb* cur = _find(id);
			if (cur == NULL)
			{
				cout << "it has benn deleted" << endl;
				return;
			}
			cur = cur->next;
			cout <<cur->pcbid<<":"<< cur->begin << "~" << cur->end << endl;
		}
	protected:
		bool pcbEmpty()
		{
			return _pcbHead->next == NULL;
		}

		void _distribute(Pcb* pcb, int size)
		{
			memList* cur = _memHead;
			if (size > _memNum)
			{
				return;
			}
			while (cur && cur->msize < size)
			{
				cur = cur->next;
			}

			if (NULL == cur)
			{
				cout << "内存分配失败" << endl;
				exit(-1);
			}

			pcb->begin = cur->first;
			pcb->end = pcb->begin + size;
			pcb->realMem = size;
			cur->first += size;
			_memNum -= size;
		}

		void _memRecover(Pcb* pcbptr)
		{
			size_t begin = pcbptr->begin;
			size_t end = pcbptr->end;
			size_t size = end - begin;
			int flag = 0;	//用于指明是否有连接块
			memList* visitBegin = NULL; //用于指明前驱是否合并
			memList* visitEnd = NULL; //用于指明后继是否合并
			memList* tmp = _memHead;
			int len = 0;
			while (tmp)
			{
				len++;
				tmp = tmp->next;
			}
			
			//第一趟
			tmp = _memHead;
			for (int i = 0; i < len; ++i)
			{
				if (begin == tmp->end) //合并
				{
					flag = 1;  //置为1，说明回收的不是单独的一块
					if (visitEnd) //如果后继已经合并
					{
						tmp->end += visitEnd->msize;
						tmp->msize += visitEnd->msize;
						_Delete(visitEnd);
						return;
					}
					else
					{
						tmp->end += size;
						tmp->msize += size;
						visitBegin = tmp;
					}
				}

				if (end == tmp->first) //合并
				{
					flag = 1; //置为1，说明回收的不是单独的一块
					if (visitBegin)
					{
						tmp->first -= visitBegin->msize;
						tmp->msize += visitBegin->msize;
						_Delete(visitBegin);
					}
					else
					{
						tmp->first -= visitBegin->msize;
						tmp->msize += visitBegin->msize;
						visitEnd = tmp;
					}
				}
				tmp = tmp->next;
			}
			
			//flag为0，说明回收的是单独的一块
			if (0 == flag)
			{
				memList* newMem = new memList(begin,end);
				newMem->next = _memHead->next;
				if (_memHead->next)
				{
					_memHead->next->prev = newMem;
				}
				newMem->prev = _memHead;
				_memHead->next = newMem;
			}

			//从小到大排序
			_Sort(_memHead);
		}

		void _Delete(memList* node)  //用于释放节点的函数
		{
			if (NULL == node)
			{
				return;
			}

			if (node->prev && node->end) //前驱和后继都存在
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
			else if (node->prev) //前驱不空后驱为空
			{
				node->prev->next = NULL;
				node->prev = NULL;
			}
			else  //前驱为空后继不空
			{
				if (_memHead == node) //删除的是头节点
				{
					_memHead = _memHead->next;
				}
				node->next->prev = NULL;
				node->next = NULL;
			}
			delete node;
		}

		Pcb* _find(int id)
		{
			if (pcbEmpty())  //进程队列为空
			{
				return NULL;
			}
			Pcb* prev = _pcbHead;
			Pcb* cur = prev->next;
			while (cur && cur->pcbid != id)
			{
				prev = cur;
				cur = cur->next;
			}

			if (NULL == cur)  //没找到
			{
				return NULL;
			}
			return prev;  //找到，返回它的前一个节点
		}

		void _Sort(memList* head) //按空闲链表大小排序
		{
			if (NULL == head || NULL == head->next)
				return;
			memList* tmp = head;
			int size = 0;   //统计链表的个数
			while (tmp)
			{
				++size;
				tmp = tmp->next;
			}
			memList* prev = head;
			memList* cur = head->next;
			for (int i = 0; i < size - 1; ++i)
			{
				for (int j = 0; j < size - i - 1; ++j)
				{
					if (cur->msize < prev->msize)
						Swap(cur, prev);
					prev = cur;
					cur = cur->next;
				}
				prev = head;
				cur = head->next;
			}
		}

		void Swap(memList* tmp1,memList* tmp2) //用于排序时交换两个指针的内容
		{
			swap(tmp1->first, tmp2->first);
			swap(tmp1->end, tmp2->end);
			swap(tmp1->msize, tmp2->msize);
		}
	private:
		size_t		_memNum;			//总内存
		size_t		_blockNum;		//内存块
		size_t		_pcbNum;			//进程数目
		Pcb*			_pcbHead;		//进程链表
		memList*		_memHead;		//内存链表
	};
}

#endif