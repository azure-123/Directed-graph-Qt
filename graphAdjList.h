#pragma once
#define MAX_VERTEX_NUM 20
typedef int VertexType;

typedef struct ArcNode 
{
	int adjvex;//该弧指向的顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	int info;//结点信息，此处指权重

}ArcNode;//边结点类型

typedef struct VNode
{
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;//邻接表
	int vexnum, arcnum;
}ALGraph;

int LocateVex(ALGraph G, char u);
void CreateALGraph_adjlist(ALGraph &G);
void PrintGraph_adjlist(ALGraph G);
