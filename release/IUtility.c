/*
    版本号：1.0
    作者：郭一菲
    生成日期：2020-9-4
    说明：主要定义了一些常用的函数
*/


#include<STRING.H>
#include<DIR.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<STDIO.H>
#include<DOS.H>
#include"IType.h"
#include"IUtility.h"

/*
    函数功能：根据路径找到节点
    输入参数：path——路径, root——起始根节点
    输出参数：无
    返回值：若找到，返回该节点；否则返回NULL
*/
IFileNode * IFindNodeByPath(char * path,IFileNode * root)
{
    IFileNode * tempNode;
    char temp[150];

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

/*
    函数功能：根据文件名找到节点
    输入参数：name——文件名, root——起始根节点
    输出参数：无
    返回值：若找到，返回该节点；否则返回NULL
*/
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

/*
    函数功能：更换磁盘并进入目录
    输入参数：path——绝对路
    输出参数：无
    返回值：无
*/
void Icd(char * path)
{
    char temp[150]="";

    if(path[1]==':'&&getdisk()!=(path[0]-'A'))  //当前磁盘与目标不一致
    {
        setdisk(path[0]-'A');   //更改磁盘
    } 
    if(strlen(path)<=3)     //路径标准化
    {
        strcpy(temp,path);
        strcpy(temp+1,"");
        strcat(temp,":\\.");
        chdir(temp);
    }   
    chdir(path);    //更改目录
}

/*
    函数功能：判断节点是否为目录
    输入参数：node——待判断的节点
    输出参数：无
    返回值：是目录则返回1，不是目录则返回0
*/
int IisFolder(IFileNode * node)
{
    return (node->file.type[0]=='0')||(node->file.type[0]=='1');
}

/*
    函数功能：通配符匹配
    输入参数：s——待匹配的字符串, p——通配符
    输出参数：无
    返回值：匹配则返回1，否则返回0
*/
int IMatch(char* s,char* p)
{
    int flag;
    char* src=s,*pattern=p;

    while(*src)
    {
        if(*pattern=='*')
        {
            while((*pattern=='*')||(*pattern)=='?')
                pattern++;
            if(!*pattern)
                return 1;
            while(*src && !IMatchi(*src,*pattern))
                src++;
            if(!*src) 
                return 0;
            flag=IMatch(src,pattern);
            while((!flag)&&*(src+1)&&IMatchi(*(src+1),*pattern))
                flag=IMatch(++src,pattern);
            return flag;
        }
        else
        {
            if(IMatchi(*src,*pattern)||('?'==*pattern))
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

/*
    函数功能：通配符匹配不区分大小写辅助函数
    输入参数：(a,b)——待匹配的两个字符
    输出参数：无
    返回值：匹配则返回1，否则返回0
*/
int IMatchi(char a,char b)
{
    if(a>='a'&&a<='z')
        a+='A'-'a';
    if(b>='a'&&b<='z')
        b+='A'-'a';
    if(a==b)
        return 1;
    else
        return 0;
}

/*
    函数功能：根据节点得到绝对路径
    输入参数：node——文件节点
    输出参数：temp——文件的绝对路径
    返回值：无
*/
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

/*
    函数功能：初始化文件根节点
    输入参数：id——用户身份
    输出参数：无
    返回值：根文件节点
*/
IFileNode * IDiskInit(int id)
{
    IFileNode * root=(IFileNode *)malloc(sizeof(IFileNode)),* rootC=(IFileNode *)malloc(sizeof(IFileNode)),*tempNode=rootC,*lastNode=rootC;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    IFileNodeSetNull(rootC);
    root->child=rootC;
    strcpy(root->file.type,"1\\");
    strcpy(root->file.name,"DOS");
    root->flags=12;
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
            tempNode->file.size=-1;
            tempNode->flags|=8;
            if(disk==2&&id==0)
                strcpy(tempNode->file.type,"0ds");
            else
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
    Icd("C:");
    return root;    //返回磁盘节点的根节点
}

/*
    函数功能：初始化文件节点
    输入参数：node——文件节点
    输出参数：无
    返回值：无
*/
void IFileNodeSetNull(IFileNode * node)
{
    node->flags=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}

/*
    函数功能：返回文件节点的父节点
    输入参数：child——子节点
    输出参数：无
    返回值：父节点
*/
IFileNode * IFindParent(IFileNode * child)
{
    IFileNode * temp=child;
    
    if(temp->file.type[1]=='\\')
        return NULL;
    //如果child是DOS根节点, 则返回NULL

    while(!(temp->flags&4))    //找到链表头
    {
        temp=temp->pre;
    }
    return temp->pre;
}

/*
    函数功能：设置(初始化)事件
    输入参数：event——待初始化的事件, 其他——事件的属性
    输出参数：无
    返回值：无
*/
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

/*
    函数功能：析构curNode链表
    输入参数：pointer——curNode节点
    输出参数：无
    返回值：无
*/
void IDelPointer(IFileNodePointer* pointer)
{
    IFileNodePointer* tempNode=pointer;
    while(tempNode->next)
    {
        tempNode=tempNode->next;
    }
    //找到链表尾

    while(tempNode->pre)
    {
        tempNode=tempNode->pre;
        free(tempNode->next);
        tempNode->next=NULL;
    }
    free(tempNode);
}

/*
    函数功能：根据文件路径得到文件名
    输入参数：path——文件路径
    输出参数：name——文件名
    返回值：无
*/
void IGetNameByPath(char* path,char* name)
{
    int i;
    int n=strlen(path);

    for(i=n-1;i>=0;i--)
    {
        if(path[i]=='\\')
            break;
    }
    strcpy(name,path+i+1);
}

/*
    函数功能：判断path2是否为path1的子路径
    输入参数：path1——父路径, path2——子路径
    输出参数：无
    返回值：若path2是否为path1的子路径, 返回1; 否则返回0
*/
int IisChild(char* path1,char* path2)
{
    int n=strlen(path2),i;

    for(i=0;i<n;i++)
    {
        if(path1[i]!=path2[i])
            return 0;
    }
    if(n==strlen(path1))
        return 0;
    return 1;
}

/*
    函数功能：判断是否有name文件
    输入参数：name——文件绝对/相对路径
    输出参数：无
    返回值：若存在改文件返回1; 否则返回0
*/
int ISearchPath(char* name)
{
    struct find_t ft;

    return !_dos_findfirst(name,0xf7,&ft); 
}