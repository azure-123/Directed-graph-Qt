#define _CRT_SECURE_NO_WARNINGS
#include"graphAdjList.h"
#include<stdio.h>
#include<stdlib.h>


//查找顶点在图中的位置
int LocateVex(ALGraph G, char u)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (u == G.vertices[i].data)
			return i;
	}
	if (i == G.vexnum)
	{
		return -1;
	}
	return 0;
}


void CreateALGraph_adjlist(ALGraph &G)
{
	int i, j, k, w;
	char v1, v2;
	ArcNode *p;
	printf("Input vexnum and arcnum:");
	scanf("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	printf("Input Vertices:");
	for (i = 0; i < G.vexnum; i++)
	{
		G.vertices[i].data = getchar();
		//scanf("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	getchar();
	printf("Input Arcs(v1,v2,w):\n");
	for (k = 0; k < G.arcnum; k++)
	{
		scanf("%c,%c,%d", &v1, &v2, &w);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->info = w;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
	return;
}

void PrintGraph_adjlist(ALGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].firstarc != NULL)
		{
			printf("%c", G.vertices[i].data);
			ArcNode *p=G.vertices[i].firstarc;
			printf("-->");
			printf("%d", G.vertices[i].firstarc->adjvex);
			while (p->nextarc != NULL)
			{
				p = p->nextarc;
				printf("-->");
				printf("%d", p->adjvex);
			}
			printf("\n");
		}
	}
}