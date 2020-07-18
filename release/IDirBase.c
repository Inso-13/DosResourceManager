#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include"IUtility.h"
#include"INode.h"
#include"IDirBase.h"

#define BUFFSIZE 256

IBool Icopy(IFileNode * inFile,IFileNode * outParent)
{
    FILE * fin,*fout;
    char * buff,temp[80],ttemp[80],i[4];
    int ret;

    fin=fopen(inFile->file.path,"r");
    if(fin==NULL)
    {
#ifdef DB
        printf("failed to open %s\n",inFile->file.name);
#endif
        return 0;
    }

    Icd(outParent->file.path);

    strcpy(temp,outParent->file.path);
    strcat(temp,"\\");
    strcat(temp,inFile->file.name);
    if(!strcmp(inFile->file.path,temp)) //原位置拷贝
    {
        strcpy(i,"(1)");

        strcpy(temp,outParent->file.path);
        strcat(temp,"\\");
        strcat(temp,inFile->file.name);
        do
        {
            strcpy(ttemp,temp);
            strcat(ttemp,i);
            i[1]++;
        }while(searchpath(ttemp));
        strcpy(temp,ttemp);
    }

    fout=fopen(temp,"w");
    if(fout==NULL)
    {
#ifdef DB
        printf("failed to open %s\n",inFile->file.name);
#endif
        return 0;
    }

    buff=malloc(BUFFSIZE);
    if(buff==NULL)
    {
#ifdef DB
        puts("not enough memory");
#endif
        return 0;
    }

    while(1)
    {
        ret=fread(buff,1,BUFFSIZE,fin);
        fwrite(buff,ret>BUFFSIZE?BUFFSIZE:ret,1,fout);
        if(feof(fin))
            break;
    }
    fclose(fin);
    fclose(fout);
    free(buff);

    IAddFileNode(outParent,inFile->file.name);  //添加新文件节点
    return 1;
}
IBool Irmf(IFileNode * fileNode)
{
    remove(fileNode->file.path);    //删除文件
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name);     //删除文件节点
}
void Imkdir(IFileNode * pathNode,IFileNode * folderName)    //创建文件夹，并更新节点
{
    char temp[80];

    strcpy(temp,pathNode->file.path);
    strcat(temp,"\\");
    strcat(temp,folderName->file.name);
    mkdir(temp);    //创建文件夹
    IAddFileNode(pathNode,folderName->file.name);
}
IBool Irmdir(IFileNode * node)  //删除所有空文件夹，并更新节点
{
    if(node->child) 
        return Irmdir(node->child);
    if(node->next)
        return Irmdir(node->next);
    IDelFileNode(IFindParent(node),node->file.name);
    return !rmdir(node->file.path);
}
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild)   //复制链表
{
    if(IisFolder(oldChildChild))
    {
        if(!oldChildChild->child)
            IAddFilelist(oldChildChild);
        Imkdir(newChild,oldChildChild);
        if(oldChildChild->child)
            ICopyAll(oldChildChild->child,newChild->child);
    }
    else
    {
        Icopy(oldChildChild,newChild);
    }
    if(oldChildChild->next)
    {
        ICopyAll(oldChildChild->next,newChild);
    }
}
void Icpr(IFileNode * oldChild,IFileNode * newParent) //递归复制所有文件和文件夹
{
    if(IisFolder(oldChild))
    {
        Imkdir(newParent,oldChild);
        ICopyAll(oldChild->child,IFindNodeByName(oldChild->file.name,newParent));
    }
    else
        Icopy(oldChild,newParent);
}   
void IDelAll(IFileNode * oldChildChild) //删除链表
{
    if(IisFolder(oldChildChild))
    {
        if(oldChildChild->child)
            IDelAll(oldChildChild->child);
    }
    else
    {
        Irmf(oldChildChild);
    }
    if(oldChildChild->next)
    {
        IDelAll(oldChildChild->next);
    }
    Irmdir(oldChildChild);
}
void Irmr(IFileNode * oldChild)//递归删除所有文件和文件夹
{
    if(IisFolder(oldChild))
    {
        IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    while(Irmdir(oldChild));
}