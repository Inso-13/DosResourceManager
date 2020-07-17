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
IBool IAddSibling(IFileNode far* pre,IFileNode far* next)
{
    return IAddChild(IFindParent(pre),next);
}
IBool IAddChild(IFileNode far* parent,IFileNode far* child)
{
    IFileNode far* temp=NULL;
    if(!parent) return 0;
    if(!strcmp(child->file.name,""))
    {
        farfree(child);
        child=NULL;
        return 0;
    }
    if(parent->child)
    {
        temp=parent->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=child;
        child->pre=temp;
        child->isHead=0;
    }
    else
    {
        parent->child=child;
        child->pre=parent;
        child->isHead=1;
    }
#ifdef  DB
    printf("%s is added as %s's child\n",child->file.name,parent->file.name);
    printf("its path is %s\n",child->file.path);
#endif
    return 1;
}
IFileNode far* IGetFileNodeList(char far* path)
{
    IFileNode far* childRoot=(IFileNode far*)farmalloc(sizeof(IFileNode)), far*tempNode=childRoot, far*lastNode=childRoot;
    int ret,i,j=0;
    struct find_t ft;
    if(childRoot==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
        printf("%ld",farcoreleft());
#endif
        IQuit();
    }
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*",0xf7,&ft);

    while(j<100)
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
            printf("%ld",farcoreleft());
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
        printf("%ld",farcoreleft());
#endif
        IQuit();
    }
    Icd(parent->file.path);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name,0xf7,&ft);

    if(ret) return 0;
        
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
                strcpy(child->file.type,"no");
        }
    }

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
    farfree(child);
    return 1;
}
void IDelFilelist(IFileNode far* root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
        root->child=NULL;
    }
    if(root->next)
    {
        IDelFilelist(root->next);
        root->next=NULL;
    }
#ifdef  DB
    printf("%s is freed\n",root->file.name);
    printf("%ld",farcoreleft());
#endif
    IFileNodeSetNull(root);
    farfree(root);
    root=NULL;
}
void IAddFilelist(IFileNode far* root)
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
        IAddFilelist(root->child);
    if(root->next)
        IAddFilelist(root->next);
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
        printf("%ld",farcoreleft());
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
    farfree(tempNode);
}
