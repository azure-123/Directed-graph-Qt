#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "TopologicalSort.h"

//��ʼ��ջ�ṹ
void initStack(stack** S) 
{
	(*S) = (stack*)malloc(sizeof(stack));
	(*S)->next = NULL;
}
//�ж������Ƿ�Ϊ��
bool StackEmpty(stack S) 
{
	if (S.next == NULL) 
	{
		return true;
	}return false;
}
//��ջ����ͷ�巨���½����뵽������
void push(stack* S, VertexType u) 
{
	stack* p = (stack*)malloc(sizeof(stack));
	p->data = u;
	p->next = NULL;
	p->next = S->next;
	S->next = p;
}
//��ջ������ɾ��������Ԫ����ͬʱ���ͷŸÿռ䣬�����ý���е�������ͨ����ַ��ֵ������ i; 
void pop(stack *S, VertexType *i) 
{
	stack* p = S->next;
	*i = p->data;
	S->next = S->next->next;
	free(p);
}
//ͳ�Ƹ���������
void FindInDegree(ALGraph G, int indegree[]) 
{
	//��ʼ�����飬Ĭ�ϳ�ʼֵȫ��Ϊ 0
	for (int i = 0; i < G.vexnum; i++) 
	{
		indegree[i] = 0;
	}
	//�����ڽӱ����ݸ������н���������洢�ĸ�����λ���±꣬�� indegree ������Ӧλ��+1
	for (int i = 0; i < G.vexnum; i++) 
	{
		ArcNode* p = G.vertices[i].firstarc;
		while (p) {
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}
void TopologicalSort(ALGraph G) 
{
	int indegree[100];//������¼��������ȵ�����
	FindInDegree(G, indegree);//ͳ�Ƹ���������
 //����ջ�ṹ��������ʹ�õ�������
	stack* S;
	initStack(&S);
	//���Ҷ�Ϊ 0 �Ķ��㣬��Ϊ��ʼ��
	for (int i = 0; i < G.vexnum; i++) 
	{
		if (!indegree[i]) 
		{
			push(S, i);
		}
	}
	int count = 0;
	//��ջΪ�գ�˵���������
	while (!StackEmpty(*S)) 
	{
		int index;
		//��ջ������¼ջ�б���Ķ��������ڽӱ������е�λ��
		pop(S, &index);
		printf("ѡ�񶥵�%c\n", G.vertices[index].data);
		++count;
		//���β��Ҹ��ö��������ӵĶ��㣬�����ʼ���Ϊ 1����ɾ��ǰһ������󣬸ö������Ϊ 0
		for (ArcNode* p = G.vertices[index].firstarc; p; p = p->nextarc) 
		{
			VertexType k = p->adjvex;
			if (!(--indegree[k])) 
			{
				//�������Ϊ 0����ջ
				push(S, k);
			}
		}
		printf("��ȣ�\n");
		for (int i = 0; i < G.vexnum; i++)
		{
			printf("%c:%d ", G.vertices[i].data, indegree[i]);
		}
		printf("\n");
	}
	//��� count ֵС�ڶ�������������������ͼ�л�
	if (count < G.vexnum) 
	{
		printf("������ͼ�л�\n");
		return;
	}
	else
		printf("�����������\n");
}
