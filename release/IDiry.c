#include<STRING.H>
#include<STDLIB.H>
#include<CONIO.H>
#include<ALLOC.H>
#include"INode.h"
#include"IDirBase.h"
#include"IUtility.h"
#include"IDiry.h"

#ifdef DB
    #include<STDIO.H>
#endif


IBool Irename(IFileNode far* oldName,IFileNode far* newName)
{
    char temp[80];

    if(!IGetPath(oldName,temp)) return 0;
    Icd(temp);
    rename(oldName->file.name,newName->file.name);
    return 1;
}
void IDetree(IFileNode far* root)
{
    if(!root) return;
    strcpy(root->file.type,"0");
    IDelFilelist(root->child);
    root->child=NULL;
}
void IEntree(IFileNode far* root)
{
    IFileNode far* childRoot;

    if(!root) return;
    if(IisFolder(root))
    {
        childRoot=IGetFileNodeList(root->file.path);
        IAddChild(root,childRoot);
#ifdef  DB
        printf("%s is entreed\n",root->file.name);
#endif    
    }
    strcpy(root->file.type,"1");
}
void Icplr(IFileNode far* oldParent,IFileNode far* newParent)
{
    IFileNode far* tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->isSelect)
            Icpr(tempNode,newParent);
        tempNode=tempNode->next;
    }
}
void Irmlr(IFileNode far* oldParent,IFileNode far* rootR)
{
    IFileNode far* tempNode=oldParent->child;

    if(rootR) Icplr(oldParent,rootR);
    while(tempNode)
    {
        if(tempNode->isSelect)
            Irmr(tempNode);
        tempNode=tempNode->next;
    }
}
IFileNode far* ISearch(IFileNode far* node,IFileNode far* name)
{
    IFileNode far* findedNode,*headNode,*tempNode,*ttempNode;
    if(!node)
    {
        return NULL;
    }

    headNode=(IFileNode far*)malloc(sizeof(IFileNode));
    IFileNodeSetNull(headNode);

    if(IMatch(node->file.name,name->file.name))
    {
        headNode->child=node;
    }
    if(IisFolder(node))
    {
        IEntree(node);
        strcpy(node->file.type,"0");
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
        farfree(headNode->pre);
        headNode->pre=NULL;
    }
    return headNode;
}