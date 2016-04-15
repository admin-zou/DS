#ifndef _MEMORY_
#define _MEMORY_

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

struct Pcb
{
	int			pcbid;
	size_t		needMem; //������ڴ��С
	size_t		realMem; //ʵ���ڴ�
	size_t		begin;
	size_t		end;
	Pcb*			next;

	Pcb(int id = 0, int need = 0)
		:pcbid(id), needMem(need), realMem(0), begin(0), end(0), next(NULL)
	{}
};

struct memList	//��������
{
	size_t		msize;	//��С
	size_t		first;	//��ʼ��ַ
	size_t		end;		//��ֹ��ַ
	memList*		next;
	memList*		prev;
	memList(size_t f = 0, size_t e = 0)
		:msize(e-f),first(f), end(e), next(NULL), prev(NULL)
	{}
};

namespace FIRSTFIT   
{//�״���Ӧ�㷨

	class Firstfit 
	{
	public:
		Firstfit(size_t total) :_memNum(total), _blockNum(1), _pcbNum(0)
		{
			_pcbHead = new Pcb();
			_memHead = new memList(0, total);	  //ȫ������
		}

		void push()
		{
			int size = 0;
			cout << "��������̸���" << endl;
			cin >> size;
			for (int i = 0; i < size; ++i)
			{
				int id;
				size_t mem;
				cout << "���������<���>��<�ڴ��С>:" << endl;
				cin >> id >> mem;
				push(id, mem);
			}
		}
		
		void push(int id, int mem)		//����һ������
		{
			
			Pcb* newPcb = new Pcb(id, mem);
			newPcb->next = _pcbHead->next;
			_pcbHead->next = newPcb;
			_distribute(newPcb, mem);
			++_pcbNum;
		}

		void pop()   //ɾ��һ������
		{
			int id = 0;
			cout << "������Ҫɾ���Ľ��̵�<���>:" << endl;
			cin >> id;

			//��ɾ����һ������ô��
			Pcb* prev = _find(id);   //���ظý��̵�ǰһ������
			if (NULL == prev)    //û�иý���
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
				cout << " ��:" << i++ << "��ַ:" << cur->first << "~" << cur->end << "---->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}

		void PrintPcbMem()
		{
			int id = 0;
			cout << "���������id:";
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
				cout << "�ڴ����ʧ��" << endl;
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

			if (end <= prev->first)  //�ڵ�һ��ǰ�棬������Ҫ�޸�_memHeadָ��
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

			while (cur)  //cur �ǿ�
			{
				if (begin == prev->end)  //�ڸÿ�ĺ���
				{
					if (end == cur->first) // 1.ǰ����Ի���,��ϲ���һ��
					{
						prev->end = cur->end;
						if (NULL != cur->next)
						{
							cur->next->prev = prev;
						}
						prev->next = cur->next;
						delete cur;
					}
					else if (end < cur->first) // 2 ��ǰ��ĺϲ�
					{
						prev->end += size;
					}
					return;
				}
				else if (begin > prev->end && end <= cur->end)
				{
					if (end == cur->first)  //3 �ͺ���Ŀ�����
					{
						cur->first -= size;
					}
					else if (end < cur->first)  //4������ǰ�󶼲�������
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

			if (cur == NULL)   //  ���������Ŀ�ģ�������ǰ��Ŀ�
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
			if (pcbEmpty())  //���̶���Ϊ��
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

			if (NULL == cur)  //û�ҵ�
				return NULL;
			return prev;  //�ҵ�����������ǰһ���ڵ�
		}

	private:
		size_t		_memNum;			//���ڴ�
		size_t		_blockNum;		//�ڴ��
		size_t		_pcbNum;			//������Ŀ
		Pcb*			_pcbHead;		//��������
		memList*		_memHead;		//�ڴ�����
	};

}


namespace BESTFIT   
{//�����Ӧ�㷨
	class Firstfit 
	{
	public:
		Firstfit(size_t total) :_memNum(total), _blockNum(1), _pcbNum(0)
		{
			_pcbHead = new Pcb();
			_memHead = new memList(0, total);	  //ȫ������
		}

		void push()
		{
			int size = 0;
			cout << "��������̸���" << endl;
			cin >> size;
			for (int i = 0; i < size; ++i)
			{
				int id;
				size_t mem;
				cout << "���������<���>��<�ڴ��С>:" << endl;
				cin >> id >> mem;
				push(id, mem);
			}
		}

		void push(int id,size_t mem)	//����һ������
		{
			Pcb* newPcb = new Pcb(id, mem);
			newPcb->next = _pcbHead->next;
			_pcbHead->next = newPcb;
			_distribute(newPcb, mem);
			++_pcbNum;
		}

		void pop()   //ɾ��һ������
		{
			int id = 0;
			cout << "������Ҫɾ���Ľ��̵�<���>:" << endl;
			cin >> id;

			Pcb* prev = _find(id);   //���ظý��̵�ǰһ������
			if (NULL == prev)    //û�иý���
			{
				return;
			}
			Pcb* cur = prev->next;
			_memRecover(cur);
			prev->next = cur->next;
			delete cur;
			_Sort(_memHead); //����������С��������
		}

		void PrintMemList()
		{
			memList* cur = _memHead;
			int i = 1;
			while (cur)
			{
				cout << " ��:" << i++ << "��ַ:" << cur->first << "~" << cur->end << "---->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}
		void PrintPcbMem()
		{
			int id = 0;
			cout << "���������id:";
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
				cout << "�ڴ����ʧ��" << endl;
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
			int flag = 0;	//����ָ���Ƿ������ӿ�
			memList* visitBegin = NULL; //����ָ��ǰ���Ƿ�ϲ�
			memList* visitEnd = NULL; //����ָ������Ƿ�ϲ�
			memList* tmp = _memHead;
			int len = 0;
			while (tmp)
			{
				len++;
				tmp = tmp->next;
			}
			
			//��һ��
			tmp = _memHead;
			for (int i = 0; i < len; ++i)
			{
				if (begin == tmp->end) //�ϲ�
				{
					flag = 1;  //��Ϊ1��˵�����յĲ��ǵ�����һ��
					if (visitEnd) //�������Ѿ��ϲ�
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

				if (end == tmp->first) //�ϲ�
				{
					flag = 1; //��Ϊ1��˵�����յĲ��ǵ�����һ��
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
			
			//flagΪ0��˵�����յ��ǵ�����һ��
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

			//��С��������
			_Sort(_memHead);
		}

		void _Delete(memList* node)  //�����ͷŽڵ�ĺ���
		{
			if (NULL == node)
			{
				return;
			}

			if (node->prev && node->end) //ǰ���ͺ�̶�����
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
			else if (node->prev) //ǰ�����պ���Ϊ��
			{
				node->prev->next = NULL;
				node->prev = NULL;
			}
			else  //ǰ��Ϊ�պ�̲���
			{
				if (_memHead == node) //ɾ������ͷ�ڵ�
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
			if (pcbEmpty())  //���̶���Ϊ��
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

			if (NULL == cur)  //û�ҵ�
			{
				return NULL;
			}
			return prev;  //�ҵ�����������ǰһ���ڵ�
		}

		void _Sort(memList* head) //�����������С����
		{
			if (NULL == head || NULL == head->next)
				return;
			memList* tmp = head;
			int size = 0;   //ͳ������ĸ���
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

		void Swap(memList* tmp1,memList* tmp2) //��������ʱ��������ָ�������
		{
			swap(tmp1->first, tmp2->first);
			swap(tmp1->end, tmp2->end);
			swap(tmp1->msize, tmp2->msize);
		}
	private:
		size_t		_memNum;			//���ڴ�
		size_t		_blockNum;		//�ڴ��
		size_t		_pcbNum;			//������Ŀ
		Pcb*			_pcbHead;		//��������
		memList*		_memHead;		//�ڴ�����
	};
}

#endif