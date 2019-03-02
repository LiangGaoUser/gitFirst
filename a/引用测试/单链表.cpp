#include<malloc.h>
#include<stdio.h>
#include <cstdlib>//包含system("pause")
#define ElemType int
#define Status int 


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;//LinkList是指向结构体LNode的指针

//初始条件：单链表不存在
//操作结果：输入n个元素，逆序建立单链表(头插法)
Status CreateList_LA(LinkList&L,int n)
{
	L= (LinkList)malloc(sizeof(LNode));//L为头指针，可以代表一个链表
	if (!L) return -1;
	L->next = NULL;
	LinkList p;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		printf("请输入:\n");
		scanf_s("%d", &p->data);
		p->next = L->next;//注意这里经常写错
		L->next = p;
		
		
	}
	return 1;
}
//初始条件：单链表不存在
//操作结果：输入n个元素，正序建立单链表(尾插法)
Status CreateList_LB(LinkList&L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) return -1;
	L->next = NULL;
	LinkList p,q;
	q = L;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		printf("请输入:\n");
		scanf_s("%d", &p->data);
		p->next = q->next;
		q->next = p;
		q = p;
		

	}
	return 1;
}
//初始条件：单链表已经存在
//操作结果：在单链表第i个位置之前插入元素e,1<=i<=length+1,要注意length=0空链表时的情况和插入到最后的情况
Status ListInsert_L(LinkList&L, int i, ElemType e)
{
	LinkList q;
	q = L; int j = 0;
	while (q&&j < i - 1)//找到第i-1个元素
	{
		q = q->next;
	}
	if (!q) return -1;
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;

	if (NULL == L->next)
	{
		L->next = p;
		p->next = NULL;
		return 1;
	}
	p->next = q->next;
	q->next = p;
	return 1;
}
//初始条件：单链表存在，可以为空
//操作结果：将元素e添加到单链表的表尾
Status ListInsertLast_L(LinkList&L, ElemType e)
{
	LinkList p=L,q;
	while (p->next)
	{
		p = p->next;
	}
	q= (LinkList)malloc(sizeof(LNode));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}
//初始条件：单链表存在，且不为空
//操作结果:删除单链表的第i个元素，用e返回其值
Status ListDelete_L(LinkList&L, int i, ElemType e)
{
	int j = 0;
	LinkList p,q;
	p = L->next;
	while (p&&j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p) return -1;
	q = p->next;
	e = q->data;
	p->next = q->next;
	free(q);//用两个指针便于释放
	return 1;
}
//初始条件：单链表LA,LB,LC存在，LA和LB按值非递减排列
//操作结果：将单链表LA和单链表LB合并成LC，LC也按值非递减排列
Status MergeList_L(LinkList&LA,LinkList&LB,LinkList&LC)
{
	LinkList a, b;
	a = LA->next;
	b = LB->next;
	while (NULL!=a&&NULL!=b)
	{
		if (a->data <= b->data)
		{
			ListInsertLast_L(LC, a->data);
			a = a->next;
		}
		else
		{
			ListInsertLast_L(LC, b->data);
			b = b->next;
		}
	}
	if (NULL != a)
	{
		while (NULL != a)
		{
			ListInsertLast_L(LC, a->data);
			a = a->next;
		}
	}
	if (NULL != b)
	{
		while (NULL != b)
		{
			ListInsertLast_L(LC, b->data);
			b= b->next;
		}
	}
	return 1;
}
//初始条件：单链表LA,LB,LC存在，LA和LB按值非递减排列
//操作结果：将单链表LA和单链表LB合并成LC，LC也按值非递减排列(第二种归并算法)
Status MergeList_L2(LinkList&LA, LinkList&LB, LinkList&LC)
{
	LinkList pa, pb, pc;
	pa = LA->next;
	pb = LB->next;
	LC = pc = LA;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;

		}
	}
	pc->next = pa ? pa : pb;
	free(LB);
	return 1;
}
Status ListPrint_L(LinkList L)
{
	if (NULL == L->next) return -1;
	LinkList p = L->next;
	while (p)
	{
		printf("输出%d\n", p->data);
		p = p->next;
	}
	return 1;
}
/*int main()
{
	LinkList LA;
	printf("%d\n", CreateList_LA(LA,4));
	ListPrint_L(LA);
	printf("%d@", (LA->next->data));
	printf("%d@", (LA->next->next->data));
	printf("%d@\n", (LA->next->next->next->data));
	ListInsertLast_L(LA, 20);
	ListPrint_L(LA);

	printf("\n");
	LinkList LB;
	CreateList_LA(LB, 0);
	ListInsertLast_L(LB, 19);
	ListPrint_L(LB);
	//test  MergeList_L(LinkList&LA,LinkList&LB,LinkList&LC)
	LinkList a, b, c;
	CreateList_LB(a, 4);
	CreateList_LB(b, 8);
	CreateList_LB(c, 0);
	ListPrint_L(a);
	ListPrint_L(b);
	ListPrint_L(c);
	MergeList_L2(a, b, c);
	ListPrint_L(c);

	system("pause");
}*/