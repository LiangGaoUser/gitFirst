//引入静态链表的目的是因为有的高级语言没有指针，这时候可用静态链表来替代，它具有和链表插入删除不需要移动元素的优点
#include <stdio.h>
#include <cstdlib>//包含system("pause")
#define ElemType int
#define Status int
#define MAXSIZE 20

typedef struct
{
	ElemType data;
	int cur;//游标，相当于单链表中的指针
}component,SLinkList[MAXSIZE];//SLinkList[MAXSIZE]是结构体数组，要足够大，有的空间可能用不到
//初始条件：静态链表L不存在
//操作结果：初始化L，形成一个备用链表，L[0]为头结点，L[0].cur指向第一个结点
Status InitList_SL(SLinkList&L)
{
	for (int i = 0; i < MAXSIZE-1; i++)
	{
		L[i].cur = i + 1;
	}
	L[MAXSIZE].cur = 0;//最后一个结点的游标为0相当于空
	return 1;
}
//初始条件:静态链表L存在
//操作结果:从静态链表L取下一个空闲的结点，返回int表示这个结点在L中的位置
Status Malloc_SL(SLinkList&L)
{
	int i = L[0].cur;
	if (i)
	{
		L[0].cur = L[i].cur;
		return i;
	}
	return -1;
}
//初始条件:静态链表L存在
//操作结果:将静态链表第k个位置的结点加入到备用链表中去
Status Free_SL(SLinkList&L,int k)
{
	L[k].cur = L[0].cur;
	L[0].cur = k;
	return 1;
}
//初始条件:静态链表L存在
//操作结果:打印该静态链表，其中n是头结点，L[n].cur是指向第一个结点的指针
Status Print_SL(SLinkList&L, int n)
{
	int i = L[n].cur;
	if (!i)
	{
		printf("静态链表为空表\n");
		return -1;//空表
	}
	while (i)
	{
		printf("%d\n", L[i].data);
		i = L[i].cur;
	}
	return 1;
}
//初始条件:静态链表L存在
//操作结果:在静态链表S中寻找e是否存在，存在返回i否则返回-1
Status GetElem_SL(SLinkList&L, int S,ElemType e)
{
	int i = L[S].cur;
	while (i)
	{
		if (L[i].data == e)
		{
			return i;
		}
	}
	return -1;

}
//初始条件:静态链表L存在
//操作结果:输入集合A，建立以S为头结点的静态链表，然后输入集合B，如果S表中存在和B中相同的元素则删除，不存在则把B的元素插入到S表中
Status difference(SLinkList&L, int &S)
{
	int m, n,r,k,number;
	printf("输入集合A的个数\n");
	scanf_s("%d", &m);
	printf("\n");
	printf("输入集合B的个数\n");
	scanf_s("%d", &n);
	printf("\n");
	r=S = Malloc_SL(L);
	for (int i = 0; i < m; i++)
	{
		k=Malloc_SL(L);
		printf("输入集合A的元素\n");
		scanf_s("%d", &L[k].data);
		printf("\n");
		L[r].cur = k;
		r = k;
	}
	L[r].cur = 0;
	printf("开始打印单链表222\n");
	Print_SL(L, S);
	int p,q;
	for (int j = 0; j < n; j++)
	{
		printf("输入集合B的元素\n");
		scanf_s("%d", &number);
		printf("\n");
		p = S;
		q = L[S].cur;
		while (q != L[r].cur&&L[q].data != number)
		{
			p = q;
			q = L[q].cur;
		}
		if (q == L[r].cur)//如果S中不存在元素number
		{
			int t = Malloc_SL(L);
			L[t].data = number;
			L[t].cur = L[r].cur;
			L[r].cur = t;
			r = t;//这里和书上写的不太一样，书上r不变，这里r始终指向最后一个位置
			//printf("开始打印单链表333\n");
			//Print_SL(L, S);
		}
		else
		{
			L[p].cur = L[q].cur;
			Free_SL(L, q);
			if (q == r)
			{
				r = p;
			}
			//printf("开始打印单链表444\n");
			//Print_SL(L, S);
		}
	}
	return 1;
}

//int main()
//{
//	SLinkList L;
//	InitList_SL(L);
//	int S;
//	difference(L, S);
//	printf("开始打印单链表\n");
//	Print_SL(L, S);
//	system("pause");
//
//
//}