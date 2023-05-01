#include <stdio.h>
#include "CriticalPath.h"

void CriticalPath(ALGraph G)
{
	int i, j, k, e, l;
	int *Ve, *Vl;
	ArcNode *p;
	Ve = new int[G.vexnum];
	Vl = new int[G.vexnum];
	for (i = 0; i < G.vexnum; i++)
		Ve[i] = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		ArcNode *p = G.vertices[i].firstarc;
		while (p!=NULL)
		{
			k = p->adjvex;
			if (Ve[i] + p->info > Ve[k])
				Ve[k] = Ve[i] + p->info;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G.vexnum; i++)
		Vl[i] = Ve[G.vexnum - 1];
	for (i = G.vexnum - 2; i; i--)
	{
		p = G.vertices[i].firstarc;
		while (p!=NULL)
		{
			k = p->adjvex;
			if (Vl[k] - p->info < Vl[i])
				Vl[i] = Vl[k] - p->info;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			k = p->adjvex;
			e = Ve[i];
			l = Vl[k] - p->info;
			char tag = (e == l) ? '*' : ' ';
			printf("(%c,%c),e=%d,l=%d,%c\n", G.vertices[i].data, G.vertices[k].data, e, l, tag);
			p = p->nextarc;
		}
	}
}