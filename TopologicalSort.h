#pragma once
//结构体定义栈结构
#include "graphAdjList.h"
typedef struct stack 
{
	VertexType data;
	struct stack* next;
}stack;

void initStack(stack** S);
bool StackEmpty(stack S);
void push(stack *S, VertexType u);
void pop(stack *S, VertexType *i);
void FindInDegree(ALGraph G, int indegree[]);
void TopologicalSort(ALGraph G);