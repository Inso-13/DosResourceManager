#include<STRING.H>
#include"INode.h"
#include"ISort.h"

void ISort(IFileNode* parent,int (*fun)(IFileNode*,IFileNode*))
{
    IFileNode* tempNode=parent->child;
    int n=0,i,j,u;

    while(tempNode)
    {
        n++;
        tempNode=tempNode->next;
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            tempNode=parent->child;
            for(u=0;u<j;u++)
                tempNode=tempNode->next;
            if(fun(tempNode,tempNode->next)>0)
                IExchangeFileNode(tempNode,tempNode->next);
        }
    }
}
int ISortDateUp(IFileNode* node1,IFileNode* node2)
{
    int t;
    t=(int)node1->file.date-(int)node2->file.date;
    if(t) return t;
    t=(int)node1->file.time-(int)node2->file.time;
    return t;
}
int ISortDateDown(IFileNode* node1,IFileNode* node2)
{
    int t;
    t=(int)node2->file.date-(int)node1->file.date;
    if(t) return t;
    t=(int)node2->file.time-(int)node1->file.time;
    return t;
}
int ISortSizeUp(IFileNode* node1,IFileNode* node2)
{
    return node1->file.size-node2->file.size;
}
int ISortSizeDown(IFileNode* node1,IFileNode* node2)
{
    return node2->file.size-node1->file.size;
}
int ISortNameUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.name,node2->file.name);
}
int ISortNameDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.name,node1->file.name);
}
int ISortTypeUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.type,node2->file.type);
}
int ISortTypeDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.type,node1->file.type);
}