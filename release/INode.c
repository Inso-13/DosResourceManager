/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵�������ļ��ڵ������صĲ��ֺ������Ƚϵײ�
*/


#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<STDIO.H>
#include"IUtility.h"
#include"IQuit.h"
#include"INode.h"

/*
    �������ܣ�����ӽڵ�
    ���������parent�������ڵ�, child�����ӽڵ�
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IAddChild(IFileNode * parent,IFileNode * child)
{
    IFileNode * temp=NULL;

    if(!parent) return 0;
    //���ڵ�Ϊ�գ�����0
    
    if(!strcmp(child->file.name,""))
    {
        free(child);
        child=NULL;
        return 0;
    }
    //�ӽڵ�Ϊ��ʬ�ڵ㣬���������0
    
    if(parent->child)
    {
        temp=parent->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=child;
        child->pre=temp;
        child->flags&=27;       //child->isHead=0;
    }
    //������ڵ������ӽڵ�
    else
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=4;        //child->isHead=1;
    }
    //������ڵ�δ���ӽڵ�
    return 1;   
    //�ɹ���ӣ�����1
}

/*
    �������ܣ��õ�·���µ������ļ������������ʽ����
    ���������path��������·��
    �����������
    ����ֵ��·���µ��ļ�����
*/
IFileNode *IGetFileNodeList(char * path)
{
    IFileNode * childRoot=(IFileNode *)malloc(sizeof(IFileNode)), *tempNode=childRoot, *lastNode=childRoot;
    int ret,i,j=0;
    struct find_t ft;


    if(childRoot==NULL)
    {
        IQuit();
    }
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*",0xf7,&ft);  
    //"*.*"��0xf7�����ļ��ڵ�   ft�洢���ҽ��
    
    while(1)
    {
        j++;
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        //�������ýڵ�
        if(ret)
        {
            free(childRoot);
            childRoot=NULL;
            break;
        }
        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=(ft.size/512+1)/2;
        if(ft.attrib&0x01)
            tempNode->flags|=8;
        if(ft.attrib&0x02)
            tempNode->flags|=16;
        if(ft.attrib&0x10)
        {
            strcpy(tempNode->file.type,"0");
        }
        else
        {
            for(i=0;i<strlen(tempNode->file.name);i++)
            {
                if(tempNode->file.name[i]=='.')
                {
                    strcpy(tempNode->file.type,tempNode->file.name+i+1);
                    break;
                }
                if(i==strlen(tempNode->file.name)-1)
                    strcpy(tempNode->file.type,"NOT");
            }
        }
        tempNode->file.date=ft.wr_date;
        tempNode->file.time=ft.wr_time;
        //��ʼ���½ڵ�

        ret=_dos_findnext(&ft);
        //������һ���ڵ�

        if(ret) break;
        if(j>120) break;
        //�����·���½ڵ�������120, ���ټ�������

        lastNode=tempNode;
        tempNode=(IFileNode *)malloc(sizeof(IFileNode));

        if(tempNode==NULL)
        {
            IQuit();
        }
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    return childRoot;
}

/*
    �������ܣ���parent�ļ��������name�ļ��ڵ�
    ���������parent�������ڵ�, name�����ӽڵ��ļ���
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IAddFileNode(IFileNode  *parent,char* name)
{
    IFileNode * child=(IFileNode *)malloc(sizeof(IFileNode));
    int ret,i;
    struct find_t ft;
    char temp[150];

    if(child==NULL)
        IQuit();
    
    IGetAbsolutePath(parent,temp);
    Icd(temp);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name,0xf7,&ft);  
    //����name�ļ�

    if(ret) return 0;   
    //���Ҳ���������0
        
    strcpy(child->file.name,ft.name);
    child->file.date=ft.wr_date;
    child->file.time=ft.wr_time;
    child->file.size=(ft.size/512+1)/2;
    
    if(ft.attrib&0x10)
        strcpy(child->file.type,"0");
    
    else
    {
        for(i=0;i<strlen(child->file.name);i++)
        {
            if(child->file.name[i]=='.')
            {
                strcpy(child->file.type,child->file.name+i+1);
                break;
            }
            if(i==strlen(child->file.name)-1)
                strcpy(child->file.type,"NOT");
        }
    }
    //��ʼ���ýڵ�

    return IAddChild(parent,child);
}

/*
    �������ܣ���parent�ļ�����ɾ��name�ļ��ڵ�
    ���������parent�������ڵ�, name�����ӽڵ��ļ���
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IDelFileNode(IFileNode *parent,char* name)
{
    IFileNode * child=parent->child;
    int ret,i;
    char temp[150];

    IGetAbsolutePath(parent,temp);
    Icd(temp);

    while(strcmp(child->file.name,name)&&child!=NULL)
       child=child->next;
    
    if(child==NULL)
        return 0;

    if(child->flags&4)
    {
        child->pre->child=child->next;
        if(child->next)
        {
            child->next->pre=child->pre;
            child->next->flags|=4;
        }
    }
    //���������ͷ
    else
    {
        child->pre->next=child->next;
        if(child->next) child->next->pre=child->pre;
    }
    //�����������ͷ

    free(child);
    return 1;
}

/*
    �������ܣ��ݹ�ɾ����������
    ���������rootҪɾ�����ļ�����ڵ�
    �����������
    ����ֵ����
*/
void IDelFilelist(IFileNode* root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    //�������
    if(root->next)
    {
        IDelFilelist(root->next);
    }
    free(root);
    root=NULL;
}

/*
    �������ܣ��ݹ����������
    ���������rootҪ��֦���ļ�����ڵ�
    �����������
    ����ֵ����
*/
void IAddFilelist(IFileNode* root)
{
    IFileNode* childRoot;
    char temp[150];

    if(!root->child&&IisFolder(root))
    {
        IGetAbsolutePath(root,temp);
        childRoot=IGetFileNodeList(temp);
        IAddChild(root,childRoot);
    }
    
    if(root->child)
        IAddFilelist(root->child);
    //�������

    if(root->next)
        IAddFilelist(root->next);
}

/*
    �������ܣ��鿴�ļ������Ƿ������ļ���
    ���������node����Ŀ��ڵ�, path��������·��
    �����������
    ����ֵ���������ļ��У�����1; ���򷵻�0
*/
int IPeek(IFileNode* node,char* path)
{
    int ret;
    struct find_t ft;
    char temp[150];

    if(!IisFolder(node)) return 0;

    Icd(path);
    ret=_dos_findfirst("*.*",0xf7,&ft);

    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        if(ft.attrib&0x10)
            return 1;

        ret=_dos_findnext(&ft);
        if(ret) break;
    }
    return 0;
}

/*
    �������ܣ�����ʱ,���ڽ��������ֵܽڵ��������е�˳��
    ���������(node1,node2)����������Ҫ�����Ľڵ�
    �����������
    ����ֵ����
*/
void IExchangeFileNode(IFileNode* node1,IFileNode* node2)
{
    if(node1->flags&4)
    {
        node1->flags&=27;
        node2->flags|=4;
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
    //���node1������ͷ
    else
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
    //���node1��������ͷ
}