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

IBool Inew(IFileNode * pathNode,IFileNode * fileName)
{
    Icd(pathNode->file.path);
    if(creatnew(fileName->file.name,0)==-1)
        return 0;
    return IAddFileNode(pathNode,fileName->file.name);    
}
IBool Irename(IFileNode * oldName,IFileNode * newName) //重命名oldName文件
{
    char temp[80];

    if(!IGetPath(oldName,temp)) return 0;
    Icd(temp);
    rename(oldName->file.name,newName->file.name);  //重命名
    strcpy(oldName->file.name,newName->file.name);
    strcat(temp,"\\");
    strcat(temp,newName->file.name);
    strcpy(oldName->file.path,temp);    //更新节点
    return 1;
}
void IDetree(IFileNode * root,IFileNode* null) //将root目录下的文件从文件树上减除
{
    if(!root) return;
    if(root->file.type[1]=='\\')
    {
        root->file.type[0]='0';
        return;
    }
    if(!IisFolder(root)) return;
    root->file.type[0]='0';
    IDelFilelist(root->child);
    root->child=NULL;
}
void IEntree(IFileNode * root,IFileNode* null) //将root目录下的文件加到文件树上
{
    IFileNode * childRoot;

    if(!root) return;
    if(root->file.type[1]=='\\')
    {
        root->file.type[0]='1';
        return;
    }
    if(root->file.type[0]=='1'||root->child)
        return;
    if(IisFolder(root))
    {
        childRoot=IGetFileNodeList(root->file.path);
        IAddChild(root,childRoot);
        while(childRoot)
        {
            IPeek(childRoot);
            childRoot=childRoot->next;
        }
        
#ifdef  DB
        printf("%s is entreed\n",root->file.name);
        printf("%u\n",coreleft());
#endif    
    }
    root->file.type[0]='1';
}
void Icplr(IFileNode * oldParent,IFileNode * newParent)//复制oldParent目录下所有被选中的文件
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&1)
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
        if(tempNode->flags&1)
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
        IEntree(node,0);
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
            IDetree(node,0);
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