#include<malloc.h>
#include<stdio.h>
#include <cstdlib>//����system("pause")
#define ElemType int
#define Status int 


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;//LinkList��ָ��ṹ��LNode��ָ��

//��ʼ����������������
//�������������n��Ԫ�أ�������������(ͷ�巨)
Status CreateList_LA(LinkList&L,int n)
{
	L= (LinkList)malloc(sizeof(LNode));//LΪͷָ�룬���Դ���һ������
	if (!L) return -1;
	L->next = NULL;
	LinkList p;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		printf("������:\n");
		scanf_s("%d", &p->data);
		p->next = L->next;//ע�����ﾭ��д��
		L->next = p;
		
		
	}
	return 1;
}
//��ʼ����������������
//�������������n��Ԫ�أ�������������(β�巨)
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
		printf("������:\n");
		scanf_s("%d", &p->data);
		p->next = q->next;
		q->next = p;
		q = p;
		

	}
	return 1;
}
//��ʼ�������������Ѿ�����
//����������ڵ������i��λ��֮ǰ����Ԫ��e,1<=i<=length+1,Ҫע��length=0������ʱ������Ͳ��뵽�������
Status ListInsert_L(LinkList&L, int i, ElemType e)
{
	LinkList q;
	q = L; int j = 0;
	while (q&&j < i - 1)//�ҵ���i-1��Ԫ��
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
//��ʼ��������������ڣ�����Ϊ��
//�����������Ԫ��e��ӵ�������ı�β
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
//��ʼ��������������ڣ��Ҳ�Ϊ��
//�������:ɾ��������ĵ�i��Ԫ�أ���e������ֵ
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
	free(q);//������ָ������ͷ�
	return 1;
}
//��ʼ������������LA,LB,LC���ڣ�LA��LB��ֵ�ǵݼ�����
//�����������������LA�͵�����LB�ϲ���LC��LCҲ��ֵ�ǵݼ�����
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
//��ʼ������������LA,LB,LC���ڣ�LA��LB��ֵ�ǵݼ�����
//�����������������LA�͵�����LB�ϲ���LC��LCҲ��ֵ�ǵݼ�����(�ڶ��ֹ鲢�㷨)
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
		printf("���%d\n", p->data);
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