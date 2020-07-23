#include<STRING.H>
#include<DIR.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<STDIO.H>
#include"IType.h"
#include"IUtility.h"

IFileNode * IFindNodeByPath(char * path,IFileNode * root)
{
    IFileNode * tempNode;
    char temp[50];

    if(!root)
        return 0;

    IGetAbsolutePath(root,temp);
    if(!strcmp(temp,path))   //比较路径，一致则返回
        return root;
    
    tempNode=IFindNodeByPath(path,root->child); //深度优先搜索
    if(tempNode)
        return tempNode;

    tempNode=IFindNodeByPath(path,root->next);
    if(tempNode)
        return tempNode;
    
    return 0;   //未找到，则返回NULL
}
IFileNode * IFindNodeByName(char * name,IFileNode * root)
{
    IFileNode * temp;

    if(!root)
        return 0;

    if(!strcmp(root->file.name,name))   //比较文件名，一致则返回
        return root;
    
    temp=IFindNodeByName(name,root->next);     //广度优先搜索
    if(temp)
        return temp;

    temp=IFindNodeByName(name,root->child);
    if(temp)
        return temp;
    
    return 0;   //未找到，则返回NULL
}
void Icd(char * path)
{
    char temp[80]="";

    if(path[1]==':'&&getdisk()!=(path[0]-'A'))  //当前磁盘与目标不一致
    {
        setdisk(path[0]-'A');   //更改磁盘
#ifdef  DB
        printf("switch to disk %c\n",getdisk()+'A');
#endif
    } 
    if(strlen(path)<=3)     //路径标准化
    {
        strcpy(temp,path);
        strcpy(temp+1,"");
        strcat(temp,":\\.");
        chdir(temp);
    }   
    chdir(path);    //更改路径
#ifdef  DB
    getcwd(temp,80);
    puts(temp);
#endif
}
IBool IisFolder(IFileNode * node)
{
    return (node->file.type[0]=='0')||(node->file.type[0]=='1');
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
void IGetAbsolutePath(IFileNode * node,char* temp)
{
    if(node->file.name[1]==':'||!strcmp(node->file.name,"DOS"))
        strcpy(temp,node->file.name);
    else
    {
        IGetAbsolutePath(IFindParent(node),temp);
        strcat(temp,"\\");
        strcat(temp,node->file.name);
    }
}
IFileNode * IDiskInit()
{
    IFileNode * root=(IFileNode *)malloc(sizeof(IFileNode)),* rootC=(IFileNode *)malloc(sizeof(IFileNode)),*tempNode=rootC,*lastNode=rootC;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    IFileNodeSetNull(rootC);
    root->child=rootC;
    strcpy(root->file.type,"1\\");
    strcpy(root->file.name,"DOS");
    root->hasFolder=-1;
    root->flags=4;
    rootC->pre=root;
    rootC->flags|=4;
    strcpy(temp,"C:");
    for(i=0;i<26;i++)   //遍历26个英文字母，查找所有磁盘
    {
        setdisk(i);
        disk=getdisk();
        if(disk==i)     //如果磁盘存在，初始化磁盘节点
        {
            if(disk<2||disk>24)
                continue;
            tempNode->file.date=33;
            tempNode->file.time=0;
            tempNode->file.size=0;
            tempNode->hasFolder=-1;
            strcpy(tempNode->file.type,"0d");
            temp[0]=disk+'A';
            strcpy(tempNode->file.name,temp);
            tempNode=(IFileNode *)malloc(sizeof(IFileNode));
            IFileNodeSetNull(tempNode);
            lastNode->next=tempNode;
            tempNode->pre=lastNode;
            lastNode=lastNode->next;
        }
    }
    lastNode->pre->next=NULL;
    free(lastNode);
#ifdef DB
    printf("near:%u\n",coreleft());
#endif
    Icd("C:");
    return root;    //返回磁盘节点的根节点
}
void IFileNodeSetNull(IFileNode * node)
{
    node->flags=0;
    node->hasFile=0;
    node->hasFolder=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
IFileNode * IFindParent(IFileNode * child)
{
    IFileNode * temp=child;
    
    while(!(temp->flags&4))    //找到链表头
    {
        temp=temp->pre;
    }
    return temp->pre;
}
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change)
{
    event->x1=x1;
    event->y1=y1;
    event->x2=x2;
    event->y2=y2;
    event->type=type;
    event->pfun=pfun;
    event->node0=node0;
    event->node1=node1;
    event->change=change;
}
