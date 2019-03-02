#include <cstdlib>
#include <stdio.h>
#define  Status int
#define  ElemType int
#define startLength 100//初始容量为100个ElemType数据
#define addLength 10//如果线性表的长度超过存储容量，则增长addLength个ElemType数据的容量
typedef struct
{
	ElemType*elem;
	int listlength;//线性表当前的长度
	int listsize;//线性表的存储容量
}SqList;
//SqList L;

//初始条件：线性表不存在
//操作结果：构成一个线性表
Status InitList(SqList&L)
{
	L.elem = (ElemType*)malloc(startLength * sizeof(ElemType));
	if (!L.elem) return -1;
	L.listlength = 0;
	L.listsize = startLength;
	return 0;
}
//初始条件：线性表已经存在
//操作结果：向线性表第i个位置之前中插入元素，1<=i<=L.listlength+1,第i~L.listlength个元素向后移动
Status ListInsert(SqList&L,int i,ElemType e)
{
	printf("begin\n");
	if (i<1 || i>L.listlength+1) return -1;
	if (L.listlength >= L.listsize)
	{
		ElemType*newbase;
		newbase = (ElemType*)realloc(L.elem, (L.listsize + addLength) * sizeof(ElemType));
		if (!newbase) return -1;
		L.elem = newbase;
		L.listsize = L.listsize + addLength;
	}
	if (L.listlength == 0)//在空表里面插入一个元素
	{
		L.elem[0] = e;
		L.listlength++;
		printf("end\n");
		return 1;
	}
	/*if (i = L.listlength + 1||L.listlength!=0)
	{
		L.elem[L.listlength] = e;
		L.listlength++;
		return 1;
	}*/
	ElemType*p, *q;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.listlength - 1]); p >= q; --p)
	{
		*(p + 1) = *p;
	}
	*q = e;
	L.listlength++;
	printf("end2\n");
	return 1;
}
//初始条件：线性表存在
//操作结果：删除第i个元素，用e返回删除的元素，i<=1<=L.listlength(注意listlength=0时的情况)，将第i+1~L.listlength都向前移动一个位置
Status ListDelete(SqList&L,int i,ElemType&e)
{
	if (i<1 && i>L.listlength) return -1;
	if (L.listlength == 0)
	{
		printf("线性表已经为空，无法再进行删除!");
		return -1;
	}
	e = L.elem[i-1];
	printf("e=%d,i=%d\n", e,i);
	ElemType*p;
	for (p = &(L.elem[i-1]); p <= &(L.elem[L.listlength - 2]); p++)
	{
		*p=*(p+1);
	}
	L.listlength--;
	return 1;
}
//初始条件：L存在
//操作结果：在L中查找有没有和e满足<,>,=关系的数据，如果存在返回true否则返回false
Status LocateElem(SqList&L,ElemType e,const char a[])
{
	ElemType*p;
	if (a == "equal")
	{
		for (p = &(L.elem[0]); p <= &(L.elem[L.listlength - 1]); p++)
		{
			if (*p == e)
			{
				return true;
			}
		}
		return false;
	}
	else if (a == "less")
	{
		for (p = &(L.elem[0]); p <= &(L.elem[L.listlength - 1]); p++)
		{
			if (*p < e)
			{
				return true;
			}
		}
		return false;
	}
	else if (a == "more")
	{
		for (p = &(L.elem[0]); p <= &(L.elem[L.listlength - 1]); p++)
		{
			if (*p > e)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}
//初始条件：LA，LB
//操作结果：将存在LB不存在LA中的元素插入到LA中
Status ListaUListb(SqList&LA, SqList&LB)
{
	ElemType*p,e;
	for (p = &(LB.elem[0]); p <= &(LB.elem[LB.listlength-1]); p++)
	{
		e = *p;
		if (!LocateElem(LA,e,"equal"))
		{
			ListInsert(LA, LA.listlength + 1, e);
		}
	}
	return 1;
}
//初始条件：线性表LA,LB存在，且LA和LB都是非递减有序序列
//操作结果：LA和LB归并成LC，LC中的元素也是非递减有序序列
Status MergeList(SqList LA, SqList LB, SqList&LC)
{
	ElemType*p, *q;
	int i = 0;
	p = &(LA.elem[0]);
	q = &(LB.elem[0]);
	while (p <= &(LA.elem[LA.listlength - 1]) && q <= &(LB.elem[LB.listlength - 1]))
	{
		if (*p <= *q)
		{
			ListInsert(LC, LC.listlength+1, *p);
			p++;
		}
		else
		{
			ListInsert(LC, LC.listlength+1, *q);
			q++;
		}
	}
	if (p < &(LA.elem[LA.listlength - 1]))
	{
		for (p; p < &(LA.elem[LA.listlength - 1]); p++)
		{
			ListInsert(LC, LC.listlength+1, *p);
		}
	}
	if(q< &(LB.elem[LB.listlength - 1]))
	{
		for (q; q <= &(LB.elem[LB.listlength - 1]); q++)
		{
			ListInsert(LC, LC.listlength+1, *q);
		}
	}
	return true;
}
Status ListPrint(SqList&L)
{
	printf("BeginPrint\n");
	ElemType*p;
	for (p = &(L.elem[0]); p <= &(L.elem[L.listlength - 1]); p++)
	{
		printf("%d\n",*p);
	}
	printf("EndPrint\n");
	return 1;
}
/*int main()
{

	SqList L;
	printf("%d", InitList(L));
	for (int i = 1; i < 5; i++)
	{
		ListInsert(L, i, i);
	}
	ListPrint(L);

	ElemType e;
	for (int i = 1; i < 3; i++)
	{
		ListDelete(L, i, e);//删除第1和第3个元素
		//printf("e=%d\n", e);
	}
	ListPrint(L);

	SqList LA, LB;
	InitList(LA);
	InitList(LB);
	for (int i = 1; i < 4; i++)
	{
		ListInsert(LA, i, i);
	}
	for (int i = 1; i < 7; i++)
	{
		ListInsert(LB, i, i);
	}
	ListPrint(LA);
	ListPrint(LB);
	printf("LA.listlength=%d,LB.listlength=%d\n", LA.listlength, LB.listlength);
	ListaUListb(LA, LB);
	printf("LA.listlength=%d,LB.listlength=%d\n", LA.listlength, LB.listlength);
	ListPrint(LA);

	//test MergeList
	SqList La, Lb,Lc;
	InitList(La);
	InitList(Lb);
	InitList(Lc);
	for (int i = 1; i < 5; i++)
	{
		ListInsert(La, i, i);
	}
	for (int i = 1; i < 10; i++)
	{
		ListInsert(Lb, i, i);
	}
	ListPrint(La);
	ListPrint(Lb);
	MergeList(La, Lb, Lc);
	ListPrint(Lc);
	system("pause");
	return 0;
}*/
