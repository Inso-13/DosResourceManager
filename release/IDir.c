#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include"IUtility.h"
#include"IType.h"
#include"IDir.h"

#define BUFFSIZE 1024

#ifndef far
    #define far 
#endif
IFileNode far* IDiskInit()
{
    IFileNode far* root=(IFileNode far*)farmalloc(sizeof(IFileNode)),*tempNode=root,*lastNode=root;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    strcpy(temp,"C:");
    for(i=0;i<26;i++)
    {
        setdisk(i);
        disk=getdisk();
        if(disk==i)
        {
            if(disk<2||disk>24)
                continue;
            tempNode->file.size=0;
            tempNode->file.date.year=1980;
            tempNode->file.date.month=1;
            tempNode->file.date.day=1;
            tempNode->file.date.hour=0;
            tempNode->file.date.minute=0;
            strcpy(tempNode->file.type,"0");
            temp[0]=disk+'A';
            strcpy(tempNode->file.name,temp);
            strcpy(tempNode->file.path,temp);
            tempNode=(IFileNode far*)farmalloc(sizeof(IFileNode));
            IFileNodeSetNull(tempNode);
            lastNode->next=tempNode;
            tempNode->pre=lastNode;
            lastNode=lastNode->next;
        }
    }
    lastNode->pre->next=NULL;
    free(lastNode);
    Icd("D:");
    return root;
}
IBool IisFolder(IFileNode far* node)
{
    return !strcmp(node->file.type,"0")||!strcmp(node->file.type,"1");
}
void Icd(char far* path)
{
    char temp[80]="";

    if(path[1]==':'&&getdisk()!=(path[0]-'A'))
    {
        setdisk(path[0]-'A');
#ifdef  DB
        printf("switch to disk %c\n",getdisk()+'A');
#endif
        if(strlen(path)<=3)
        {
            strcpy(temp,path);
            strcpy(temp+1,"");
            strcat(temp,":\\.");
            chdir(temp);
        }
    }    
    chdir(path);
#ifdef  DB
    getcwd(temp,80);
    puts(temp);
#endif
}
IBool IMatch(char* src,char* pattern)
{
    IBool flag;

    while(*src)
    {
        if(*pattern=='*')
        {
            while((*pattern=='*')||(*pattern)=='?')
                pattern++;
            if(!*pattern)
                return 1;
            while(*src && !(*src==*pattern))
                src++;
            if(!*src) 
                return 0;
            flag=IMatch(src,pattern);
            while((!flag)&&*(src+1)&&(*(src+1)==*pattern))
                flag=IMatch(++src,pattern);
            return flag;
        }
        else
        {
            if((*src==*pattern)||('?'==*pattern))
                return IMatch(++src,++pattern);
            else
                return 0;
        }
    }
    if(*pattern)
    {
        if((*pattern=='*')&&(*(pattern+1)==0))
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
IBool IGetPath(IFileNode far* node,char* temp)
{
    int i,n;

    n=strlen(node->file.path);
    i=n-1;
    while(node->file.path[i]!='\\')
    {
        i--;
        if(i==0)
            return 0;
    }
    strcpy(temp,node->file.path);
    strcpy(temp+i,"");
    return 1;
}
IFileNode far* IGetFileNodeList(char far* path)
{
    IFileNode far* childRoot=(IFileNode far*)farmalloc(sizeof(IFileNode)), far*tempNode=childRoot, far*lastNode=childRoot;
    int ret,i;
    struct find_t ft;
    if(childRoot==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
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
                    strcpy(tempNode->file.type,"no");
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
        tempNode=(IFileNode far*)farmalloc(sizeof(IFileNode));
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
IBool IAddFileNode(IFileNode far *parent,char* name)
{
    IFileNode far* child=(IFileNode far*)farmalloc(sizeof(IFileNode));
    int ret,i;
    struct find_t ft;
    if(child==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
    Icd(parent->file.path);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name,0xf7,&ft);

    if(ret) return 0;
        
    strcpy(child->file.name,ft.name);
    child->file.size=(ft.size/512+1)/2;
    if(ft.attrib&0x10) strcpy(child->file.type,"0");
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
                strcpy(child->file.type,"no");
        }
    }
    
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

    return IAddChild(parent,child);
}
IBool IDelFileNode(IFileNode far *parent,char* name)
{
    IFileNode far* child=parent->child;
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
    if(child->isHead)
    {
        child->pre->child=child->next;
        if(child->next)
        {
            child->next->pre=child->pre;
            child->next->isHead=1;
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
IBool IEntree(IFileNode far* root)
{
    IFileNode far* childRoot;

    if(!strcmp(root->file.type,"0"))
        strcpy(root->file.type,"1");
    if(IisFolder(root))
    {
        childRoot=IGetFileNodeList(root->file.path);
        IAddChild(root,childRoot);
#ifdef  DB
        printf("%s is entreed\n",root->file.name);
#endif    
    }
    if(root->child&&!strcmp(root->child->file.type,"1"))
        IEntree(root->child);
    if(root->next)
        IEntree(root->next);
    return 1;
}
void IDetree(IFileNode far* root)
{
    strcpy(root->file.type,"0");
    IDelFilelist(root->child);
    root->child=NULL;
}
IFileNode far* IFindNodeByPath(char far* path,IFileNode far* root)
{
    IFileNode far* temp;

    if(!root)
        return 0;

    if(!strcmp(root->file.path,path))
        return root;
    
    temp=IFindNodeByPath(path,root->child);
    if(temp)
        return temp;

    temp=IFindNodeByPath(path,root->next);
    if(temp)
        return temp;
    
    return 0;
}
IFileNode far* IFindNodeByName(char far* name,IFileNode far* root)
{
    IFileNode far* temp;

    if(!root)
        return 0;

    if(!strcmp(root->file.name,name))
        return root;
    
    temp=IFindNodeByName(name,root->next);
    if(temp)
        return temp;

    temp=IFindNodeByName(name,root->child);
    if(temp)
        return temp;
    
    return 0;
}
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
    free(buff);

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
IBool Irename(IFileNode far* oldName,IFileNode far* newName)
{
    char temp[80];

    if(!IGetPath(oldName,temp)) return 0;
    Icd(temp);
    rename(oldName->file.name,newName->file.name);
    return 1;
}
void ICopyAll(IFileNode far* oldChildChild,IFileNode far* newChild)
{
    if(IisFolder(oldChildChild))
    {
        if(!oldChildChild->child)
            IEntree(oldChildChild);
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
void IPeek(IFileNode far* node)
{
    int ret;
    struct find_t ft;
    char temp[80];
    IFileNode far* tempNode=(IFileNode far*)malloc(sizeof(IFileNode));
    if(tempNode==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
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
            strcpy(temp,node->file.path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            strcpy(tempNode->file.path,temp);
            IPeek(tempNode);
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
IFileNode far* ISearch(IFileNode far* node,IFileNode far* name)
{
    IFileNode far* findedNode,*tempNode,*ttempNode;
    int ret,i;
    if(findedNode==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
    IFileNodeSetNull(findedNode);
    
    IEntree(node);
    tempNode=node->child;
    while(tempNode)
    {
        if(IisFolder(tempNode))
        {
            ttempNode=ISearch(tempNode,name);
            if(ttempNode)
            {
                IAddChild(findedNode,ttempNode);                
            }
            else if(tempNode->child)
                IDetree(tempNode->child);
        }
        else if(IMatch(tempNode->file.name,name->file.name))
        { 
            IAddChild(findedNode,ttempNode);                
        }
        tempNode=tempNode->next;
    }

    tempNode=findedNode->child;
    return tempNode;
}