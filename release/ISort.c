/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������Ҫ����������
*/


#include<STRING.H>
#include"INode.h"
#include"ISort.h"

/*
    �������ܣ�����
    ���������parent�������ڵ�, fun��������ȷ��˳��ĺ���ָ��
    �����������
    ����ֵ����
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
    //��������ĳ���

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
    �������ܣ���ʱ����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
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
    �������ܣ���ʱ�併������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
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
    �������ܣ����ļ���С��������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortSizeUp(IFileNode* node1,IFileNode* node2)
{
    return node1->file.size-node2->file.size;
}

/*
    �������ܣ����ļ���С��������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortSizeDown(IFileNode* node1,IFileNode* node2)
{
    return node2->file.size-node1->file.size;
}

/*
    �������ܣ����ļ�����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortNameUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.name,node2->file.name);
}

/*
    �������ܣ����ļ�����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortNameDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.name,node1->file.name);
}

/*
    �������ܣ����ļ�������������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortTypeUp(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node1->file.type,node2->file.type);
}

/*
    �������ܣ����ļ����ͽ�������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortTypeDown(IFileNode* node1,IFileNode* node2)
{
    return strcmp(node2->file.type,node1->file.type);
}