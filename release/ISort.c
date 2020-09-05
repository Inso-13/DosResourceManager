/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：主要定义排序函数
*/


#include<STRING.H>
#include"INode.h"
#include"ISort.h"

/*
    函数功能：排序
    输入参数：parent——父节点, fun——用于确定顺序的函数指针
    输出参数：无
    返回值：无
*/
void ISort(IFileNode* parent,int (*fun)(IFileNode*,IFileNode*))
{
    IFileNode* tempNode=parent->child;
    int n=0,i,j,u;

    while(tempNode)
    {
        n++;
        tempNode=tempNode->next;
    }
    //计算链表的长度

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

/*
    函数功能：按时间升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortDateUp(IFileNode* node1,IFileNode* node2)
{
    int t;
    t=(int)node1->file.date-(int)node2->file.date;
    if(t) return t;
    t=(int)node1->file.time-(int)node2->file.time;
    return t;
}

/*
    函数功能：按时间降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortDateDown(IFileNode* node1,IFileNode* node2)
{
    int t;
    t=(int)node2->file.date-(int)node1->file.date;
    if(t) return t;
    t=(int)node2->file.time-(int)node1->file.time;
    return t;
}

/*
    函数功能：按文件大小升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortSizeUp(IFileNode* node1,IFileNode* node2)
{
    return node1->file.size-node2->file.size;
}

/*
    函数功能：按文件大小降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortSizeDown(IFileNode* node1,IFileNode* node2)
{
    return node2->file.size-node1->file.size;
}

/*
    函数功能：按文件名升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortNameUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.name,node2->file.name);
}

/*
    函数功能：按文件名降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortNameDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.name,node1->file.name);
}

/*
    函数功能：按文件类型升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortTypeUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.type,node2->file.type);
}

/*
    函数功能：按文件类型降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortTypeDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.type,node1->file.type);
}