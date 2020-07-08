#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<dir.h>
#include"IType.h"
#include"IDir.h"

IBool Icd(char* path)
{
    char temp[80];

    if(path[1]==':')
    {
        setdisk(path[0]-'A');
    }
    chdir(path);
    getcwd(temp,80);
    puts(temp);
    return 1;
}
IFileNode* IAddFileNode(char* path)
{
    IFileNode* childRoot=(IFileNode*)malloc(sizeof(IFileNode));
    IFileNode* tempNode=childRoot,*lastNode=childRoot;
    int ret_code,i;
    struct find_t ft;

    Icd(path);
    IFileNodeSetNull(childRoot);
    ret_code=_dos_findfirst("*",0xff,&ft);

    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret_code=_dos_findnext(&ft);
            if(ret_code) break;
        }
        if(ret_code) break;
        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=ft.size;
        if(!tempNode->file.size) strcpy(tempNode->file.type,"0");
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
        ret_code=_dos_findnext(&ft);
        if(ret_code) break;
        lastNode=tempNode;
        tempNode=(IFileNode*)malloc(sizeof(IFileNode));
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    lastNode=tempNode;
    tempNode=(IFileNode*)malloc(sizeof(IFileNode));
    lastNode->next=tempNode;
    IFileNodeSetNull(tempNode);
    tempNode->pre=lastNode;
    ret_code=_dos_findfirst("*.*",0xff,&ft);

    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret_code=_dos_findnext(&ft);
            if(ret_code) break;
        }
        if(ret_code){
            free(tempNode);            
            break;
        }    
        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=ft.size;
        for(i=0;i<strlen(ft.name);i++)
        {
            if(ft.name[i]=='.')
            {
                strcpy(tempNode->file.type,ft.name+i+1);
                break;
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
        ret_code=_dos_findnext(&ft);
        if(ret_code) break;
        lastNode=tempNode;
        tempNode=(IFileNode*)malloc(sizeof(IFileNode));
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    return childRoot;
}
IBool IEntree(IFileNode* root)
{
    IFileNode* childRoot;
    childRoot=IAddFileNode(root->file.path);
    IAddChild(root,childRoot);
    while(!strcmp(childRoot->file.type,"0"))
    {
        if(!childRoot) return 1;
        IEntree(childRoot);
        Icd(root->file.path);
        childRoot=childRoot->next;
    }
    return 1;
}