#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<dir.h>
#include"IType.h"
#include"IDir.h"
#define DB

void Icd(char* path)
{
    char temp[80]="";

    if(path[1]==':')
    {
        setdisk(path[0]-'A');
#ifdef  DB
        printf("switch to disk %c\n",getdisk()+'A');
#endif
    }
    if(strlen(path)<=3)
    {
        strcpy(temp,path);
        strcpy(temp+1,"");
        strcat(temp,":\\.");
        strcpy(path,temp);
    }
    chdir(path);
#ifdef  DB
    getcwd(temp,80);
    puts(temp);
#endif
}
IFileNode* IAddFileNode(char* path)
{
    IFileNode* childRoot=(IFileNode*)malloc(sizeof(IFileNode)),*tempNode=childRoot,*lastNode=childRoot;
    int ret,i;
    struct find_t ft;
#ifdef  DB
    if(childRoot==NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
#endif
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*",0xf7,&ft);

    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=ft.size;
        if(ft.attrib&0x10) strcpy(tempNode->file.type,"0");
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
        tempNode=(IFileNode*)malloc(sizeof(IFileNode));
#ifdef  DB
        if(tempNode==NULL)
        {
            printf("not enough memory\n");
            exit(-1);
        }

#endif
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    return childRoot;
}
IBool IEntree(IFileNode* root)
{
    IFileNode* childRoot;
    if(strcmp(root->file.type,"0"))
        return 0;
    strcpy(root->file.type,"1");
    childRoot=IAddFileNode(root->file.path);
    IAddChild(root,childRoot);
#ifdef  DB
    printf("%s is entreed\n",root->file.name);
#endif
    return 1;
}
void IDetree(IFileNode* root)
{
    strcpy(root->file.type,"0");
    root=root->child;
    while(root)
    {
#ifdef  DB
        printf("%s is freed\n",root->file.name);
#endif
        free(root);
        root=NULL;
        root=root->next;
    }
}
void IUpdateFileNode(IFileNode* curNode)
{
    int i,n;
    char temp[80];
    IFileNode* tempNode,*childNode;
    IBool flag;

#ifdef  DB
    if(curNode==NULL)
    {
        printf("curNode is NULL\n");
        exit(-1);
    }
    if(childNode==NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
#endif
    IDetree(curNode);
    IEntree(curNode);
}