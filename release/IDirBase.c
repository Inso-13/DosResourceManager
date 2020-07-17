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

#define BUFFSIZE 1024

IBool Icopy(IFileNode far* inFile,IFileNode far* outParent)
{
    FILE far* fin,*fout;
    char far* buff,temp[80],ttemp[80],i[4];
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
    if(!strcmp(inFile->file.path,temp))
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

    buff=farmalloc(BUFFSIZE);
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
    farfree(buff);

    IAddFileNode(outParent,inFile->file.name);
    return 1;
}
IBool Irmf(IFileNode far* fileNode)
{
    remove(fileNode->file.path);
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name);
}
IBool Inew(IFileNode far* pathNode,IFileNode far* fileName)
{
    Icd(pathNode->file.path);
    if(creatnew(fileName->file.name,0)==-1)
        return 0;
    return IAddFileNode(pathNode,fileName->file.name);    
}
void Imkdir(IFileNode far* pathNode,IFileNode far* folderName)
{
    char temp[80];

    strcpy(temp,pathNode->file.path);
    strcat(temp,"\\");
    strcat(temp,folderName->file.name);
    mkdir(temp);
    IAddFileNode(pathNode,folderName->file.name);
}
IBool Irmdir(IFileNode far* node)
{
    if(node->child) 
        return Irmdir(node->child);
    if(node->next)
        return Irmdir(node->next);
    IDelFileNode(IFindParent(node),node->file.name);
    return !rmdir(node->file.path);
}
void Imvdir(IFileNode far* oldChild,IFileNode far* newParent)
{
    Imkdir(newParent,oldChild);
    Irmdir(oldChild);
}
void ICopyAll(IFileNode far* oldChildChild,IFileNode far* newChild)
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
void Icpr(IFileNode far* oldChild,IFileNode far* newParent)
{
    if(IisFolder(oldChild))
    {
        Imkdir(newParent,oldChild);
        ICopyAll(oldChild->child,IFindNodeByName(oldChild->file.name,newParent));
    }
    else
        Icopy(oldChild,newParent);
}
void IDelAll(IFileNode far* oldChildChild)
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
void Irmr(IFileNode far* oldChild)
{
    if(IisFolder(oldChild))
    {
        IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    while(Irmdir(oldChild));
}
