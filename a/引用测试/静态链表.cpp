//���뾲̬�����Ŀ������Ϊ�еĸ߼�����û��ָ�룬��ʱ����þ�̬����������������к��������ɾ������Ҫ�ƶ�Ԫ�ص��ŵ�
#include <stdio.h>
#include <cstdlib>//����system("pause")
#define ElemType int
#define Status int
#define MAXSIZE 20

typedef struct
{
	ElemType data;
	int cur;//�α꣬�൱�ڵ������е�ָ��
}component,SLinkList[MAXSIZE];//SLinkList[MAXSIZE]�ǽṹ�����飬Ҫ�㹻���еĿռ�����ò���
//��ʼ��������̬����L������
//�����������ʼ��L���γ�һ����������L[0]Ϊͷ��㣬L[0].curָ���һ�����
Status InitList_SL(SLinkList&L)
{
	for (int i = 0; i < MAXSIZE-1; i++)
	{
		L[i].cur = i + 1;
	}
	L[MAXSIZE].cur = 0;//���һ�������α�Ϊ0�൱�ڿ�
	return 1;
}
//��ʼ����:��̬����L����
//�������:�Ӿ�̬����Lȡ��һ�����еĽ�㣬����int��ʾ��������L�е�λ��
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
//��ʼ����:��̬����L����
//�������:����̬�����k��λ�õĽ����뵽����������ȥ
Status Free_SL(SLinkList&L,int k)
{
	L[k].cur = L[0].cur;
	L[0].cur = k;
	return 1;
}
//��ʼ����:��̬����L����
//�������:��ӡ�þ�̬��������n��ͷ��㣬L[n].cur��ָ���һ������ָ��
Status Print_SL(SLinkList&L, int n)
{
	int i = L[n].cur;
	if (!i)
	{
		printf("��̬����Ϊ�ձ�\n");
		return -1;//�ձ�
	}
	while (i)
	{
		printf("%d\n", L[i].data);
		i = L[i].cur;
	}
	return 1;
}
//��ʼ����:��̬����L����
//�������:�ھ�̬����S��Ѱ��e�Ƿ���ڣ����ڷ���i���򷵻�-1
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
//��ʼ����:��̬����L����
//�������:���뼯��A��������SΪͷ���ľ�̬����Ȼ�����뼯��B�����S���д��ں�B����ͬ��Ԫ����ɾ�������������B��Ԫ�ز��뵽S����
Status difference(SLinkList&L, int &S)
{
	int m, n,r,k,number;
	printf("���뼯��A�ĸ���\n");
	scanf_s("%d", &m);
	printf("\n");
	printf("���뼯��B�ĸ���\n");
	scanf_s("%d", &n);
	printf("\n");
	r=S = Malloc_SL(L);
	for (int i = 0; i < m; i++)
	{
		k=Malloc_SL(L);
		printf("���뼯��A��Ԫ��\n");
		scanf_s("%d", &L[k].data);
		printf("\n");
		L[r].cur = k;
		r = k;
	}
	L[r].cur = 0;
	printf("��ʼ��ӡ������222\n");
	Print_SL(L, S);
	int p,q;
	for (int j = 0; j < n; j++)
	{
		printf("���뼯��B��Ԫ��\n");
		scanf_s("%d", &number);
		printf("\n");
		p = S;
		q = L[S].cur;
		while (q != L[r].cur&&L[q].data != number)
		{
			p = q;
			q = L[q].cur;
		}
		if (q == L[r].cur)//���S�в�����Ԫ��number
		{
			int t = Malloc_SL(L);
			L[t].data = number;
			L[t].cur = L[r].cur;
			L[r].cur = t;
			r = t;//���������д�Ĳ�̫һ��������r���䣬����rʼ��ָ�����һ��λ��
			//printf("��ʼ��ӡ������333\n");
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
			//printf("��ʼ��ӡ������444\n");
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
//	printf("��ʼ��ӡ������\n");
//	Print_SL(L, S);
//	system("pause");
//
//
//}