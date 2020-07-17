#include<STRING.H>
#include<DIR.H>
#include<CONIO.H>
#include<ALLOC.H>
#include"IUtility.h"
#ifdef DB
    #include<STDIO.H>
#endif
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
int Istrcmp(char *s,char *t)
{
    while((*s==*t)&&(*s!='\0'))
    {
        s++;
        t++;
    }
    return *s-*t;
}
IBool IisFolder(IFileNode far* node)
{
    int flag=0;
    if(!strcmp(node->file.type,"0"))
    {
        flag=1;
    }
    if(!strcmp(node->file.type,"1"))
    {
        flag=1;
    }
    return flag;
}
IBool IMatch(char* s,char* p)
{
    IBool flag;
    char* src=s,*pattern=p;

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
IFileNode far* IDiskInit()
{
    IFileNode far* root=(IFileNode far*)malloc(sizeof(IFileNode)),* rootC=(IFileNode far*)malloc(sizeof(IFileNode)),*tempNode=rootC,*lastNode=rootC;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    IFileNodeSetNull(rootC);
    root->child=rootC;
    rootC->pre=root;
    rootC->isHead=1;
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
    farfree(lastNode);
    Icd("C:");
    return root;
}
void IFileNodeSetNull(IFileNode far* node)
{
    node->isHead=0;
    node->isSelect=0;
    node->hasFile=0;
    node->hasFolder=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
IFileNode far* IFindParent(IFileNode far* child)
{
    IFileNode far* temp=child;
    
    while(!temp->isHead)
    {
        temp=temp->pre;
    }
    return temp->pre;
}
