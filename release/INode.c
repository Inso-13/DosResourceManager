#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include"IUtility.h"
#include"INode.h"
#ifdef DB
    #include<STDIO.H>
#endif
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
        child->flags&=3;       //child->isHead=0;
    }
    else    //如果父节点未有子节点
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=4;        //child->isHead=1;
    }
#ifdef  DB
    printf("%s is added as %s's child\n",child->file.name,parent->file.name);
    printf("its path is %s\n",child->file.path);
#endif
    return 1;   //成功添加，返回1
}
IFileNode *IGetFileNodeList(char * path)
{
    IFileNode * childRoot=(IFileNode *)malloc(sizeof(IFileNode)), *tempNode=childRoot, *lastNode=childRoot;
    int ret,i,j=0;
    struct find_t ft;
    if(childRoot==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
        printf("%ld",coreleft());
#endif
        IQuit();
    }
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*",0xf7,&ft);

    while(j<=30)
    {
        j++;
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=(ft.size/512+1)/2;
        tempNode->file.readOnly=ft.attrib&0x01;
        tempNode->file.isHidden=ft.attrib&0x02;
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
        
        tempNode->file.date.year=ft.wr_date/512+1980;
        ft.wr_date%=512;
        tempNode->file.date.month=ft.wr_date/32;
        tempNode->file.date.day=ft.wr_date%32;
        
        tempNode->file.date.hour=ft.wr_time/2048;
        ft.wr_time%=2048;
        tempNode->file.date.minute=ft.wr_time/32;
        
        strcpy(tempNode->file.path,path);
        strcat(tempNode->file.path,"\\");
        strcat(tempNode->file.path,tempNode->file.name);
        ret=_dos_findnext(&ft);
        if(ret) break;
        lastNode=tempNode;
        tempNode=(IFileNode *)malloc(sizeof(IFileNode));
        if(tempNode==NULL)
        {
#ifdef  DB
            printf("not enough memory\n");
            printf("%ld",coreleft());
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
    if(child==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
        printf("%ld",coreleft());
#endif
        IQuit();
    }
    Icd(parent->file.path);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name,0xf7,&ft);  //查找name文件

    if(ret) return 0;   //查找不到，返回0
        
    strcpy(child->file.name,ft.name);
    child->file.size=(ft.size/512+1)/2;
    child->file.date.year=ft.wr_date/512+1980;
    ft.wr_date%=512;
    child->file.date.month=ft.wr_date/32;
    child->file.date.day=ft.wr_date%32;
    
    child->file.date.hour=ft.wr_time/2048;
    ft.wr_time%=2048;
    child->file.date.minute=ft.wr_time/32;
    
    strcpy(child->file.path,parent->file.path);
    strcat(child->file.path,"\\");
    strcat(child->file.path,child->file.name);
    if(ft.attrib&0x10)
    {
        strcpy(child->file.type,"0");
        IPeek(child);
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

    if(child==NULL)
    {
#ifdef  DB
        printf("nothing to del\n");
#endif
    }
    Icd(parent->file.path);

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
void IDelFilelist(IFileNode * root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    if(root->next)
    {
        IDelFilelist(root->next);
    }
#ifdef  DB
    printf("%s is freed\n",root->file.name);
    printf("near:%u\n",coreleft());
#endif
    free(root);
}
void IAddFilelist(IFileNode * root)
{
    IFileNode * childRoot;

    if(!root->child&&IisFolder(root))
    {
        childRoot=IGetFileNodeList(root->file.path);
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
void IPeek(IFileNode * node)
{
    int ret;
    struct find_t ft;
    char temp[80];
    IFileNode * tempNode=(IFileNode *)malloc(sizeof(IFileNode));
    if(!IisFolder(node)) return;
    if(tempNode==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
        printf("%ld",coreleft());
#endif
        IQuit();  
    }
    node->hasFile=0;
    node->hasFolder=0;
    Icd(node->file.path);
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
            sprintf(tempNode->file.path,"%s\\%s",node->file.path,ft.name);
            strcpy(tempNode->file.type,"0t");
            IPeek(tempNode);    //深度优先搜索
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
    Icd(node->file.path);
    free(tempNode);
}
