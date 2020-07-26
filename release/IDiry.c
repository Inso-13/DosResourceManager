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
IBool Irename(IFileNode * oldName,char* newName) //重命名oldName文件
{
    char temp[50];
    int i;

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  //重命名
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
void IDetree(IFileNode * root) //将root目录下的文件从文件树上减除
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
void IEntree(IFileNode * root) //将root目录下的文件加到文件树上
{
    IFileNode * childRoot;
    char temp[50];

    if(!root) return;
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
void Icplr(IFileNode * oldParent,IFileNode * newParent)//复制oldParent目录下所有被选中的文件
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Icpr(tempNode,newParent);
        tempNode=tempNode->next;
    }
}
void Irmlr(IFileNode * oldParent,IFileNode * rootR) //删除oldParent目录下所有被选中的文件
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
IFileNode * ISearch(IFileNode * node,IFileNode * name) //按文件名查找文件，耗内存，请慎用
{
    IFileNode * findedNode,*headNode,*tempNode,*ttempNode;
    if(!node)
    {
        return NULL;
    }

    headNode=(IFileNode *)malloc(sizeof(IFileNode));
    IFileNodeSetNull(headNode);

    if(IMatch(node->file.name,name->file.name))
    {
        headNode->child=node;
    }
    if(IisFolder(node))
    {
        IEntree(node);
        node->file.type[0]='0';
        tempNode=node->child;
        while(tempNode)
        {
            ttempNode=ISearch(tempNode,name);
            if(ttempNode)
            {
                if(headNode->next)
                {
                    findedNode=ttempNode;
                    while(findedNode->next)
                        findedNode=findedNode->next;
                    headNode->next->pre=findedNode;
                    findedNode->next=headNode->next;
                }
                headNode->next=ttempNode;
                ttempNode->pre=headNode;                
            }
            tempNode=tempNode->next;
        }
        if(!headNode->next)
            IDetree(node);
    }

    if(!headNode->next&&!headNode->child)
        return NULL;
    else if(!headNode->child)
    {
        headNode=headNode->next;
        free(headNode->pre);
        headNode->pre=NULL;
    }
    return headNode;
}