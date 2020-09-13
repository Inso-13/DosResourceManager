/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：与文件节点操作相关的部分函数，比较底层
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
    函数功能：添加子节点
    输入参数：parent——父节点, child——子节点
    输出参数：无
    返回值：成功则返回1, 失败则返回0
*/
int IAddChild(IFileNode * parent,IFileNode * child)
{
    IFileNode * temp=NULL;

    if(!parent) return 0;
    //父节点为空，返回0
    
    if(!strcmp(child->file.name,""))
    {
        free(child);
        child=NULL;
        return 0;
    }
    //子节点为僵尸节点，清除并返回0
    
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
    //如果父节点已有子节点
    else
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=4;        //child->isHead=1;
    }
    //如果父节点未有子节点
    return 1;   
    //成功添加，返回1
}

/*
    函数功能：得到路径下的所有文件，以链表的形式返回
    输入参数：path——绝对路径
    输出参数：无
    返回值：路径下的文件链表
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
    //"*.*"，0xf7所有文件节点   ft存储查找结果
    
    while(1)
    {
        j++;
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        //跳过无用节点
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
        //初始化新节点

        ret=_dos_findnext(&ft);
        //查找下一个节点

        if(ret) break;
        if(j>120) break;
        //如果该路径下节点数大于120, 则不再继续查找

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
    函数功能：在parent文件夹中添加name文件节点
    输入参数：parent——父节点, name——子节点文件名
    输出参数：无
    返回值：成功则返回1, 失败则返回0
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
    //查找name文件

    if(ret) return 0;   
    //查找不到，返回0
        
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
    //初始化该节点

    return IAddChild(parent,child);
}

/*
    函数功能：在parent文件夹中删除name文件节点
    输入参数：parent——父节点, name——子节点文件名
    输出参数：无
    返回值：成功则返回1, 失败则返回0
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
    //如果是链表头
    else
    {
        child->pre->next=child->next;
        if(child->next) child->next->pre=child->pre;
    }
    //如果不是链表头

    free(child);
    return 1;
}

/*
    函数功能：递归删除整个链表
    输入参数：root要删除的文件书根节点
    输出参数：无
    返回值：无
*/
void IDelFilelist(IFileNode* root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    //深度优先
    if(root->next)
    {
        IDelFilelist(root->next);
    }
    free(root);
    root=NULL;
}

/*
    函数功能：递归添加整个树
    输入参数：root要增枝的文件书根节点
    输出参数：无
    返回值：无
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
    //深度优先

    if(root->next)
        IAddFilelist(root->next);
}

/*
    函数功能：查看文件夹内是否有子文件夹
    输入参数：node——目标节点, path——绝对路径
    输出参数：无
    返回值：若有子文件夹，返回1; 否则返回0
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
    函数功能：排序时,用于交换两个兄弟节点在链表中的顺序
    输入参数：(node1,node2)——两个需要交换的节点
    输出参数：无
    返回值：无
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
    //如果node1是链表头
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
    //如果node1不是链表头
}