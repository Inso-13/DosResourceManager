#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<STDIO.H>
#include"IUtility.h"
#include"INode.h"

// #define DB

IBool IAddChild(IFileNode * parent,IFileNode * child)
{
    IFileNode * temp=NULL;

    if(!parent) return 0;   //父节点为空，返回0
    if(!strcmp(child->file.name,""))    //子节点为僵尸节点，清除并返回0
    {
        free(child);
        child=NULL;
        return 0;
    }
    if(parent->child)   //如果父节点已有子节点
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
    else    //如果父节点未有子节点
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=4;        //child->isHead=1;
    }
    return 1;   //成功添加，返回1
}
IFileNode *IGetFileNodeList(char * path)  //48 pre node
{
    IFileNode * childRoot=(IFileNode *)malloc(sizeof(IFileNode)), *tempNode=childRoot, *lastNode=childRoot;
    int ret,i,j=0;
    struct find_t ft;

#ifdef  DB
    printf("%u\n",coreleft());
#endif
    if(childRoot==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*",0xf7,&ft);  //"*.*"，0xf7所有文件节点   ft存储查找结果
    
    while(1)
    {
        j++;
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
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
        
        ret=_dos_findnext(&ft);
        if(ret) break;
        if(j>300) break;
        lastNode=tempNode;
        tempNode=(IFileNode *)malloc(sizeof(IFileNode));
#ifdef  DB
        printf("%u\n",coreleft());
#endif
        if(tempNode==NULL)
        {
#ifdef  DB
            printf("not enough memory\n");
#endif
            IQuit();
        }
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    return childRoot;
}
IBool IAddFileNode(IFileNode  *parent,char* name)
{
    IFileNode * child=(IFileNode *)malloc(sizeof(IFileNode));
    int ret,i;
    struct find_t ft;
    char temp[50];
#ifdef  DB
    printf("%u\n",coreleft());
#endif
    if(child==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
        printf("%u",coreleft());
#endif
        IQuit();
    }
    IGetAbsolutePath(parent,temp);
    Icd(temp);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name,0xf7,&ft);  //查找name文件

    if(ret) return 0;   //查找不到，返回0
        
    strcpy(child->file.name,ft.name);
    child->file.date=ft.wr_date;
    child->file.time=ft.wr_time;
    child->file.size=(ft.size/512+1)/2;
    
    if(ft.attrib&0x10)
    {
        strcpy(child->file.type,"0");
        strcat(temp,"\\");
        strcat(temp,name);
    }
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

    return IAddChild(parent,child);
}
IBool IDelFileNode(IFileNode  *parent,char* name)
{
    IFileNode * child=parent->child;
    int ret,i;
    char temp[50];

    if(child==NULL)
    {
#ifdef  DB
        printf("nothing to del\n");
#endif
    }
    IGetAbsolutePath(parent,temp);
    Icd(temp);

   while(strcmp(child->file.name,name)&&child!=NULL)
       child=child->next;
    if(child==NULL)
    {
#ifdef  DB
        printf("nothing to del\n");
#endif
        return 0;
    }
    if(child->flags&4)
    {
        child->pre->child=child->next;
        if(child->next)
        {
            child->next->pre=child->pre;
            child->next->flags|=4;
        }
    }
    else
    {
        child->pre->next=child->next;
        if(child->next) child->next->pre=child->pre;
    }
    free(child);
    return 1;
}
void IDelFilelist(IFileNode* root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    if(root->next)
    {
        IDelFilelist(root->next);
    }
    free(root);
    root=NULL;
#ifdef  DB
    printf("%u\n",coreleft());
#endif
}
void IAddFilelist(IFileNode * root)
{
    IFileNode * childRoot;
    char temp[50];

    if(!root->child&&IisFolder(root))
    {
        IGetAbsolutePath(root,temp);
        childRoot=IGetFileNodeList(temp);
        IAddChild(root,childRoot);
#ifdef  DB
        printf("%s is entreed\n",root->file.name);
#endif    
    }
    if(root->child)
        IAddFilelist(root->child);
    if(root->next)
        IAddFilelist(root->next);
}
void IPeek(IFileNode* node,char* path)
{
    int ret;
    struct find_t ft;
    char temp[50];
    IFileNode * tempNode=(IFileNode *)malloc(sizeof(IFileNode));
#ifdef  DB
    printf("%u\n",coreleft());
#endif
    if(!IisFolder(node)) return;
    if(tempNode==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();  
    }
    node->hasFile=0;
    node->hasFolder=0;
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
        {
            node->hasFolder++;
            IFileNodeSetNull(tempNode);
            sprintf(temp,"%s\\%s",path,ft.name);
            strcpy(tempNode->file.type,"0t");
            IPeek(tempNode,temp);    //深度优先搜索
            node->hasFile+=tempNode->hasFile;
            node->hasFolder+=tempNode->hasFolder;
        }
        else
        {
            node->hasFile++;
        }
        ret=_dos_findnext(&ft);
        if(ret) break;
    }
    Icd(path);
    free(tempNode);
#ifdef  DB
    printf("%u\n",coreleft());
#endif
}
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
}