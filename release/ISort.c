/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ����������
 **************************************************
 */


#include"ISort.h"

/*
    �������ܣ�����
    ���������parent�������ڵ�, fun��������ȷ��˳��ĺ���ָ��
    �����������
    ����ֵ����
*/
void ISort(IFileNode *parent,int (*fun)(IFileNode*,IFileNode*))
{
    IFileNode *tempNode=parent->child;
    int n=0,i,j,u;

    while(tempNode)
    {
        n++;
        tempNode=tempNode->next;
    }    //��������ĳ���

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)    
        {
            tempNode=parent->child;
            for(u=0;u<j;u++)
                tempNode=tempNode->next;
            if(fun(tempNode,tempNode->next)>0)
                IExchangeFileNode(tempNode,tempNode->next); //�����ڵ�
        }
    }   //ð������
}

/*
    �������ܣ���ʱ����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortDateUp(IFileNode *node1,IFileNode *node2)
{
    int t;  

    t=(int)node1->file.date-(int)node2->file.date;
    if(t) return t; //�ȱȽ�����
    t=(int)node1->file.time-(int)node2->file.time;
    return t;   //��Ƚ�ʱ��
}

/*
    �������ܣ���ʱ�併������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortDateDown(IFileNode *node1,IFileNode *node2)
{
    int t;

    t=(int)node2->file.date-(int)node1->file.date;
    if(t) return t; //�ȱȽ�����
    t=(int)node2->file.time-(int)node1->file.time;
    return t; //��Ƚ�ʱ��
}

/*
    �������ܣ����ļ���С��������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortSizeUp(IFileNode *node1,IFileNode *node2)
{
    if(IisFolder(node1))
    {
        if(IisFolder(node2))
            return 0;
        else 
            return -1;
    }   
    else if(IisFolder(node2))
        return 1;   //�ļ�����С

    else if(node1->file.size<0)
    {
        if(node2->file.size<0)
            return 0;
        else 
            return 1;
    }
    else if(node2->file.size<0)
        return -1;  //����32K���ļ����
    else
        return node1->file.size-node2->file.size;
}

/*
    �������ܣ����ļ���С��������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortSizeDown(IFileNode *node1,IFileNode *node2)
{
    if(IisFolder(node1))
    {
        if(IisFolder(node2))
            return 0;
        else 
            return 1;
    }
    else if(IisFolder(node2))
        return -1;  //�ļ�����С
    else if(node1->file.size<0)
    {
        if(node2->file.size<0)
            return 0;
        else 
            return -1;
    }
    else if(node2->file.size<0)
        return 1;   //����32K���ļ����
    else
        return node2->file.size-node1->file.size;
}

/*
    �������ܣ����ļ�����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortNameUp(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node1->file.name,node2->file.name);
}

/*
    �������ܣ����ļ�����������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortNameDown(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node2->file.name,node1->file.name);
}

/*
    �������ܣ����ļ�������������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortTypeUp(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node1->file.type,node2->file.type);
}

/*
    �������ܣ����ļ����ͽ�������
    ���������(node1,node2)������Ҫ�Ƚϵ������ڵ�
    �����������
    ����ֵ����
*/
int ISortTypeDown(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node2->file.type,node1->file.type);
}

/*
    �������ܣ�������˵�
    ���������flag��������˵��򿪱�־, null��������ռλ
    �����������
    ����ֵ����
*/
void ISortMenuActive(IFileNode *flag,IFileNode *null)
{
    char *n=(char*)flag;   
    
    ICheckNull(null);
    *n|=1;  //���򿪱�־��Ϊ1
}

/*
    �������ܣ�����������
    ���������cur������ǰ�ڵ�, pfun��������ȷ��˳��ĺ���ָ�룬������lambda
    �����������
    ����ֵ����
*/
void ISortActive(IFileNode *cur,IFileNode *pfun)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;   //��ǰ�ڵ�
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;  //�ȽϺ���ָ��
    
    if(curNode->child->child)
        ISort(curNode->child,fun);  //����������
}

/*
    �������ܣ�����ʱ,���ڽ��������ֵܽڵ��������е�˳��
    ���������(node1,node2)����������Ҫ�����Ľڵ�
    �����������
    ����ֵ����
*/
void IExchangeFileNode(IFileNode *node1,IFileNode *node2)
{
    if(node1->flags&NODE_IS_HEAD)  //���node1������ͷ
    {
        node1->flags&=NODE_DEL_HEAD;
        node2->flags|=NODE_ADD_HEAD;
        node1->pre->child=node2;
        node2->pre=node1->pre;
        if(node2->next)
        {
            node2->next->pre=node1;
            node1->next=node2->next;
        }
        else 
            node1->next=NULL;
        node2->next=node1;
        node1->pre=node2;
    }
    else //���node1��������ͷ
    {
        if(node2->next)
        {
            node2->next->pre=node1;
            node1->next=node2->next;
        }
        else
            node1->next=NULL;
        node1->pre->next=node2;
        node2->pre=node1->pre;
        node2->next=node1;
        node1->pre=node2;
    }
}