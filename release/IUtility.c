#include<STRING.H>
#include<DIR.H>
#include<CONIO.H>
#include<ALLOC.H>
#include"IUtility.h"
#ifdef DB
    #include<STDIO.H>
#endif
IFileNode * IFindNodeByPath(char * path,IFileNode * root)
{
    IFileNode * tempNode;

    if(!root)
        return 0;

    if(!strcmp(root->file.path,path))   //比较路径，一致则返回
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
        if(strlen(path)<=3)     //路径标准化
        {
            strcpy(temp,path);
            strcpy(temp+1,"");
            strcat(temp,":\\.");
            chdir(temp);
        }
    }    
    chdir(path);    //更改路径
#ifdef  DB
    getcwd(temp,80);
    puts(temp);
#endif
}
IBool IisFolder(IFileNode * node)
{
    return !strcmp(node->file.type,"0")||!strcmp(node->file.type,"1");
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
IBool IGetPath(IFileNode * node,char* temp)
{
    int i,n;

    n=strlen(node->file.path);
    i=n-1;
    while(node->file.path[i]!='\\') //找到最后一个反斜杠
    {
        i--;
        if(i==0)
            return 0;
    }
    strcpy(temp,node->file.path);
    strcpy(temp+i,"");
    return 1;
}
IFileNode * IDiskInit()
{
    IFileNode * root=(IFileNode *)malloc(sizeof(IFileNode)),* rootC=(IFileNode *)malloc(sizeof(IFileNode)),*tempNode=rootC,*lastNode=rootC;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    IFileNodeSetNull(rootC);
    root->child=rootC;
    rootC->pre=root;
    rootC->isHead=1;
    strcpy(temp,"C:");
    for(i=0;i<26;i++)   //遍历26个英文字母，查找所有磁盘
    {
        setdisk(i);
        disk=getdisk();
        if(disk==i)     //如果磁盘存在，初始化磁盘节点
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
    node->isHead=0;
    node->isSelect=0;
    node->hasFile=0;
    node->hasFolder=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
IFileNode * IFindParent(IFileNode * child)
{
    IFileNode * temp=child;
    
    while(!temp->isHead)    //找到链表头
    {
        temp=temp->pre;
    }
    return temp->pre;
}
