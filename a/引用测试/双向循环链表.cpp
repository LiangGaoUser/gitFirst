#include<malloc.h>
#include <stdio.h>
#include <cstdlib>//����system("pause")

#define ElemType int
#define Status int


typedef struct DuLNode
{
	ElemType data;
	struct DuLNode*prior;
	struct DuLNode*next;
}DuLNode,*DuLinkList;
//��ʼ����:˫��ѭ����������
//�������:ͷ�巨������
Status InitDuList(DuLinkList&L,int n)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));//LΪͷ���
	if (!L) return -1;
	L->next = L;
	L->prior = L;
	DuLinkList p;


	p = (DuLinkList)malloc(sizeof(DuLNode));//�������ǵ�һ���������ͷ�巨
	printf("������:\n");
	scanf_s("%d", &p->data);
	p->next = L->next;
	p->prior = L;
	L->prior = p;
	L->next = p;

	for (int i = 1; i < n; i++)
	{
		p = (DuLinkList)malloc(sizeof(DuLNode));
		printf("������:\n");
		scanf_s("%d", &p->data);
		p->next = L->next;
		p->prior = L;
		L->next->prior = p;
		L->next = p;
	}

	return 1;

}
//��ʼ����:˫��ѭ���������
//�������:pΪ����һ��nextָ��
Status PrintNext_DuL(DuLinkList&L,DuLinkList&p)
{
	if (p == L)
	{
		DuLinkList q=L->next;
		while (q!= L)
		{
			printf("%d", q->data);
			q = q->next;
		}
		return 1;
	}
	DuLinkList s = p;
	while (p->next!=s)
	{
		if (p != L)
		{
			printf("%d\n", p->data);
		}
		p = p->next;
	}
	printf("%d\n", p->data);//��ӡs֮ǰ������
	return 1;
}
//��ʼ����:˫��ѭ���������
//�������:pΪ����һ��priorָ��
Status PrintPiror_DuL(DuLinkList&L, DuLinkList&p)
{
	if (p == L)
	{
		DuLinkList q = L->prior;
		while (q != L)
		{
			printf("%d", q->data);
			q = q->prior;
		}
		return 1;
	}
	DuLinkList s=p;
	while (p ->prior!=s)
	{
		if (p != L)
		{
			printf("%d", p->data);
		}	
		p = p->prior;
	}
	printf("%d", p->data);//��ӡs֮ǰ������
	return 1;
}
//��ʼ����:˫��ѭ���������
//�������:���ص�i��Ԫ�ص�ָ�룬1<=i<=length+1,i������Χ����NULL
DuLinkList GetElemP_DuL(DuLinkList&L, int i)
{
	if (i < 1) return NULL;
	DuLinkList p = L->next;
	int j = 0;
	//printf("----------\n");
	while (p != L && j < i - 1)
	{
		//printf("%d",p->data);
		p = p->next;
		j++;
	}
	//printf("----------\n");
	if (p == L) return NULL;
	else return p;
}
//��ʼ����:˫��ѭ���������
//�������:��˫��ѭ�������i��Ԫ��֮ǰ����Ԫ��e,1<=i<=length+1
Status ListInsert_DuL(DuLinkList&L, int i, ElemType e)
{
	DuLinkList p= GetElemP_DuL(L, i)->prior;
	if (p == NULL)
	{
		return -1;
	}
	//printf("%d*****\n", p->data);
	DuLinkList q;
	q = (DuLinkList)malloc(sizeof(DuLNode));
	if (!q) return -1;
	q->data = e;

	q->next = p->next;
	q->prior = p;
	p->next->prior = q;
	p->next = q;
	return 1;
}
//��ʼ����:˫��ѭ���������
//�������:ɾ��˫��ѭ������ĵ�i��Ԫ�أ�1<=i<=length
Status ListDelete_DuL(DuLinkList&L, int i, ElemType e)
{
	DuLinkList p = GetElemP_DuL(L, i);
	if (p == NULL)
	{
		return -1;
	}
	//printf("%d*****\n", p->data);
	p->prior->next = p->next;
	p->next->prior = p->prior;
	
	return 1;
}





int main()
{
	DuLinkList L;
	InitDuList(L, 5);

	PrintNext_DuL(L, L);

	//DuLinkList s = L->next->next;
	//PrintNext_DuL(L, s);

	//s = L->prior->prior;
	//PrintPiror_DuL(L, s);

	printf("&&&&\n");

	ListInsert_DuL(L, 3, 9);
	PrintNext_DuL(L, L);
	printf("&&&&\n");
	ListDelete_DuL(L, 3, 9);
	PrintNext_DuL(L, L);
	/*DuLinkList t;
	t = GetElemP_DuL(L, 5);
	if (t != NULL)
	{
		printf("%d", t->data);
	}
	else
	{
		printf("NULL");
	}*/
	
	system("pause");


}