#include<STRING.H>
#include<STDLIB.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<IO.H>
#include<STDIO.H>
#include"INode.h"
#include"IDirBase.h"
#include"IUtility.h"
#include"IDiry.h"

IBool Inew(IFileNode * pathNode,char* fileName)
{
    char temp[50];
    IGetAbsolutePath(pathNode,temp);
    Icd(temp);
    if(creatnew(fileName,0)==-1)
        return 0;
    return IAddFileNode(pathNode,fileName);    
}
IBool Irename(IFileNode * oldName,char* newName) //������oldName�ļ�
{
    char temp[50];
    int i;

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  //������
    strcpy(oldName->file.name,newName);
    for(i=0;i<strlen(oldName->file.name);i++)
    {
        if(oldName->file.name[i]=='.')
        {
            strcpy(oldName->file.type,oldName->file.name+i+1);
            break;
        }
        if(i==strlen(oldName->file.name)-1)
            strcpy(oldName->file.type,"NOT");
    }
    return 1;
}
void IDetree(IFileNode * root) //��rootĿ¼�µ��ļ����ļ����ϼ���
{
    if(!root) return;
    if(root->file.type[1]=='\\')
    {
        root->file.type[0]='0';
        return;
    }
    if(!IisFolder(root)) return;
    root->file.type[0]='0';
    if(!root->child) return;
    IDelFilelist(root->child);
    root->child=NULL;
}
void IEntree(IFileNode * root) //��rootĿ¼�µ��ļ��ӵ��ļ�����
{
    IFileNode * childRoot;
    char temp[50];

    if(!root) return;
    if(!strcmp(root->file.type,"0ds"))
        return;
    if(root->file.type[1]=='\\')
    {
        root->file.type[0]='1';
        return;
    }
    if(root->file.type[0]=='1'||root->child)
    {
        root->file.type[0]='1';
        return;
    }
    if(IisFolder(root))
    {
        IGetAbsolutePath(root,temp);
        childRoot=IGetFileNodeList(temp);
        if(childRoot)
            IAddChild(root,childRoot);
        while(childRoot&&IisFolder(childRoot))
        {
            IGetAbsolutePath(childRoot,temp);
            IPeek(childRoot,temp);
            childRoot=childRoot->next;
        }
    root->file.type[0]='1';
    }
}
void Icplr(IFileNode * oldParent,IFileNode * newParent)//����oldParentĿ¼�����б�ѡ�е��ļ�
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Icpr(tempNode,newParent);
        tempNode=tempNode->next;
    }
}
void Irmlr(IFileNode * oldParent,IFileNode * rootR) //ɾ��oldParentĿ¼�����б�ѡ�е��ļ�
{
    IFileNode * tempNode=oldParent->child;

    if(rootR) Icplr(oldParent,rootR);
    while(tempNode)
    {
        if(tempNode->flags&2)
            Irmr(tempNode);
        tempNode=tempNode->next;
    }
}
void ISearch(IFileNode * parent,char* name) //���ļ����ڵ�ǰ�ļ��в����ļ�
{
    IFileNode *tempNode=parent->child;
    while(tempNode)
    {
        if(IMatch(tempNode->file.name,name))
        {
            tempNode->flags|=2;
        }
        else
        {
            tempNode->flags&=29;
        }
        tempNode=tempNode->next;
    }
}
