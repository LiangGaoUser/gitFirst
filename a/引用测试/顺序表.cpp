#include <cstdlib>
#include <stdio.h>
#define  Status int
#define  ElemType int
#define startLength 100//��ʼ����Ϊ100��ElemType����
#define addLength 10//������Ա�ĳ��ȳ����洢������������addLength��ElemType���ݵ�����
typedef struct
{
	ElemType*elem;
	int listlength;//���Ա�ǰ�ĳ���
	int listsize;//���Ա�Ĵ洢����
}SqList;
//SqList L;

//��ʼ���������Ա�����
//�������������һ�����Ա�
Status InitList(SqList&L)
{
	L.elem = (ElemType*)malloc(startLength * sizeof(ElemType));
	if (!L.elem) return -1;
	L.listlength = 0;
	L.listsize = startLength;
	return 0;
}
//��ʼ���������Ա��Ѿ�����
//��������������Ա��i��λ��֮ǰ�в���Ԫ�أ�1<=i<=L.listlength+1,��i~L.listlength��Ԫ������ƶ�
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
	if (L.listlength == 0)//�ڿձ��������һ��Ԫ��
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
//��ʼ���������Ա����
//���������ɾ����i��Ԫ�أ���e����ɾ����Ԫ�أ�i<=1<=L.listlength(ע��listlength=0ʱ�����)������i+1~L.listlength����ǰ�ƶ�һ��λ��
Status ListDelete(SqList&L,int i,ElemType&e)
{
	if (i<1 && i>L.listlength) return -1;
	if (L.listlength == 0)
	{
		printf("���Ա��Ѿ�Ϊ�գ��޷��ٽ���ɾ��!");
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
//��ʼ������L����
//�����������L�в�����û�к�e����<,>,=��ϵ�����ݣ�������ڷ���true���򷵻�false
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
//��ʼ������LA��LB
//���������������LB������LA�е�Ԫ�ز��뵽LA��
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
//��ʼ���������Ա�LA,LB���ڣ���LA��LB���Ƿǵݼ���������
//���������LA��LB�鲢��LC��LC�е�Ԫ��Ҳ�Ƿǵݼ���������
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
		ListDelete(L, i, e);//ɾ����1�͵�3��Ԫ��
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
