#include "graphmainwindow.h"
#include "ui_graphmainwindow.h"
#include "inputgraphdialog.h"
#include <QApplication>
#include "CriticalPath.h"
#include "graphAdjList.h"
#include "TopologicalSort.h"
#include "inputgraphdialog.h"
#include <string>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

GraphMainWindow::GraphMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphMainWindow)
{
    ui->setupUi(this);
}

GraphMainWindow::~GraphMainWindow()
{
    delete ui;
}

void GraphMainWindow::on_showLinklist_clicked()
{
    ALGraph G;
    int vexnum=ui->lineEdit_vexnum->text().toInt();
    G.vexnum=vexnum;
    int arcnum=ui->lineEdit_arcnum->text().toInt();
    G.arcnum=arcnum;
    QString Qvertices=ui->lineEdit_vertices->text();
    string vertices=Qvertices.toStdString();
    if(int(vertices.length())!=vexnum)
    {
        QMessageBox::critical(this,"错误","输入顶点表示不满足顶点个数！");
        return;
    }

    int i, j, k, w;
    char v1, v2;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = vertices[i];
        //scanf("%c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    /*qDebug()<<"vexnum:"<<vexnum
           <<"arcnum:"<<arcnum
          <<"vertices:"<<Qvertices;*/
    QString Qrelations=ui->plainTextEdit_relation->toPlainText();
    string relations=Qrelations.toStdString();
    if((int(relations.length())!=6*G.arcnum)&&(int(relations.length())!=6*G.arcnum-1))
    {
        QMessageBox::critical(this,"错误","输入顶点关系不满足输入弧的个数！");
        qDebug()<<relations.length();
        return;
    }

    for (k = 0; k < G.arcnum; k++)
    {
        v1=relations[k*6];
        v2=relations[k*6+2];
        w=int(relations[k*6+4]-'0');
        qDebug()<<v1<<v2<<w;
        i = LocateVex(G, v1);
        if(i==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        j = LocateVex(G, v2);
        if(j==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = w;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
    QString output;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].firstarc != NULL)
        {
            output.append(G.vertices[i].data);
            ArcNode *p=G.vertices[i].firstarc;
            output.append("-->");
            output.append(QString::number(G.vertices[i].firstarc->adjvex,10));
            while (p->nextarc != NULL)
            {
                p = p->nextarc;
                output.append("-->");
                output.append(QString::number(p->adjvex,10));
            }
            output.append("\n");
        }
    }
    ui->textEdit_output->setText(output);
}


void GraphMainWindow::on_showTopologicalSort_clicked()
{
    ALGraph G;
    int vexnum=ui->lineEdit_vexnum->text().toInt();
    G.vexnum=vexnum;
    int arcnum=ui->lineEdit_arcnum->text().toInt();
    G.arcnum=arcnum;
    QString Qvertices=ui->lineEdit_vertices->text();
    string vertices=Qvertices.toStdString();
    if(int(vertices.length())!=vexnum)
    {
        QMessageBox::critical(this,"错误","输入顶点表示不满足顶点个数！");
        return;
    }

    int i, j, k, w;
    char v1, v2;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = vertices[i];
        //scanf("%c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    qDebug()<<"vexnum:"<<vexnum
           <<"arcnum:"<<arcnum
          <<"vertices:"<<Qvertices;
    QString Qrelations=ui->plainTextEdit_relation->toPlainText();
    string relations=Qrelations.toStdString();
    if((int(relations.length())!=6*G.arcnum)&&(int(relations.length())!=6*G.arcnum-1))
    {
        QMessageBox::critical(this,"错误","输入顶点关系不满足输入弧的个数！");
        return;
    }


    qDebug()<<Qrelations;
    for (k = 0; k < G.arcnum; k++)
    {
        v1=relations[k*6];
        v2=relations[k*6+2];
        w=int(relations[k*6+4]-'0');
        qDebug()<<v1<<v2<<w;
        i = LocateVex(G, v1);
        if(i==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        j = LocateVex(G, v2);
        if(j==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = w;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
    int indegree[100];//创建记录各顶点入度的数组
    FindInDegree(G, indegree);//统计各顶点的入度
    //建立栈结构，程序中使用的是链表
    stack* S;
    initStack(&S);
    //查找度为 0 的顶点，作为起始点
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!indegree[i])
        {
            push(S, i);
        }
    }
    int count = 0;
    QString output;
    QString sortResult;
    //当栈为空，说明排序完成
    while (!StackEmpty(*S))
    {
        int index;
        //弹栈，并记录栈中保存的顶点所在邻接表数组中的位置
        pop(S, &index);
        //printf("选择顶点%c\n", G.vertices[index].data);
        output.append("选择顶点");
        output.append(G.vertices[index].data);
        sortResult.append(G.vertices[index].data);
        output.append("\n");
        ++count;
        //依次查找跟该顶点相链接的顶点，如果初始入度为 1，当删除前一个顶点后，该顶点入度为 0
        for (ArcNode* p = G.vertices[index].firstarc; p; p = p->nextarc)
        {
            VertexType k = p->adjvex;
            if (!(--indegree[k]))
            {
                //顶点入度为 0，入栈
                push(S, k);
            }
        }
        //printf("入度：\n");
        output.append("入度：");
        output.append("\n");
        for (int i = 0; i < G.vexnum; i++)
        {
            //printf("%c:%d ", G.vertices[i].data, indegree[i]);
            output.append(G.vertices[i].data);
            output.append(":");
            output.append(QString::number(indegree[i],10));
            output.append(" ");
        }
        //printf("\n");
        output.append("\n");
     }
        //如果 count 值小于顶点数量，表明该有向图有环
    if (count < G.vexnum)
    {
        output.append("该有向图有环");
        return;
    }
    else
    {
        output.append("拓扑排序完成\n");
        output.append("排序结果："+sortResult);
        //printf("拓扑排序完成\n");
    }

    ui->textEdit_output->setText(output);
}

void GraphMainWindow::on_showCriticalPath_clicked()
{
    ALGraph G;
    int vexnum=ui->lineEdit_vexnum->text().toInt();
    G.vexnum=vexnum;
    int arcnum=ui->lineEdit_arcnum->text().toInt();
    G.arcnum=arcnum;
    QString Qvertices=ui->lineEdit_vertices->text();
    string vertices=Qvertices.toStdString();
    if(int(vertices.length())!=vexnum)
    {
        QMessageBox::critical(this,"错误","输入顶点表示不满足顶点个数！");
        return;
    }

    int i, j, k, w;
    char v1, v2;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = vertices[i];
        //scanf("%c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    qDebug()<<"vexnum:"<<vexnum
           <<"arcnum:"<<arcnum
          <<"vertices:"<<Qvertices;
    QString Qrelations=ui->plainTextEdit_relation->toPlainText();
    string relations=Qrelations.toStdString();
    if((int(relations.length())!=6*G.arcnum)&&(int(relations.length())!=6*G.arcnum-1))
    {
        QMessageBox::critical(this,"错误","输入顶点关系不满足输入弧的个数！");
        return;
    }


    for (k = 0; k < G.arcnum; k++)
    {
        v1=relations[k*6];
        v2=relations[k*6+2];
        w=int(relations[k*6+4]-'0');
        qDebug()<<v1<<v2<<w;
        i = LocateVex(G, v1);
        if(i==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        j = LocateVex(G, v2);
        if(j==-1)
        {
            QMessageBox::critical(this,"错误","未找到顶点！");
            return;
        }
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = w;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }

    QString output;
    //int i, j, k, e, l;
    int e,l;
    int *Ve, *Vl;
    //ArcNode *p;
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
            output.append("(");
            output.append(G.vertices[i].data);
            output.append(",");
            output.append(G.vertices[k].data);
            output.append("),e=");
            output.append(QString::number(e,10));
            output.append(",l=");
            output.append(QString::number(l,10)+tag);
            output.append("\n");
            p = p->nextarc;
        }
    }
    ui->textEdit_output->setText(output);
}
