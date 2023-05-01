#pragma once
#define MAX_VERTEX_NUM 20
typedef int VertexType;

typedef struct ArcNode 
{
	int adjvex;//�û�ָ��Ķ����λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
	int info;//�����Ϣ���˴�ָȨ��

}ArcNode;//�߽������

typedef struct VNode
{
	VertexType data;//������Ϣ
	ArcNode *firstarc;//ָ���һ�������ö����ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;//�ڽӱ�
	int vexnum, arcnum;
}ALGraph;

int LocateVex(ALGraph G, char u);
void CreateALGraph_adjlist(ALGraph &G);
void PrintGraph_adjlist(ALGraph G);
