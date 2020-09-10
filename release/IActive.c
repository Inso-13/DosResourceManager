/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：Active类函数处于中间层，用于将后端（如Diry等）函数的接口统一化，供前端调用栈使用
*/


#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<BIOS.H>
#include<DOS.H>
#include<GRAPHICS.H>
#include<CONIO.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"ISort.h"
#include"IInit.h"
#include"IHanZi.h"
#include"IActive.h"
#include"IDebug.h"


/*
    函数功能：在激活IEntree函数后，回收垃圾内存
    输入参数：X——辅助文件节点
    输出参数：cur——当前节点
    返回值：无
*/
void IAfterEntree(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=(*curNode)->pre,*lastNode=tempNode->pre;
    char path1[50],path2[50],path[50];

    IGetAbsolutePath((*curNode)->child,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);
    else
        strcpy(path2,"");

    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path);
        if(strcmp(path,"DOS")&&strcmp(path,path1)&&strcmp(path,path2)&&!IisChild(path1,path)&&!IisChild(path2,path))
        {
            IDetree(tempNode->child);
            if(tempNode->pre)
            {
                tempNode=tempNode->pre;
                tempNode->next=tempNode->next->next;
                free(tempNode->next->pre);
                tempNode->next->pre=tempNode;
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
            }
        }
        tempNode=lastNode;
    }
}

/*
    函数功能：激活IEntree函数，更改当前节点
    输入参数：node——需要IEntree的节点
    输出参数：cur——当前节点
    返回值：无
*/
void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
	IFileNodePointer * newCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));     //新节点
    IFileNodePointer * tempNode=NULL,*nextNode=NULL;

    tempNode=(*curNode)->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    //假如curNode链表有后一项，递归删除后面的所有节点

    newCurNode->child=node;
    newCurNode->next=NULL;
    newCurNode->wait=10;
    newCurNode->pre=*curNode;
    (*curNode)->next=newCurNode;
    *curNode=newCurNode;
    //新节点初始化

    IEntree(node);
    //激活IEntree函数

    tempNode=(*curNode)->pre;
    while(tempNode)
    {
        tempNode->wait--;
        if(tempNode->wait<0)
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        else
            tempNode=tempNode->pre;
    }
    //删除curNode链表中的超时节点，以节约内存
}

/*
    函数功能：根据情况将nodeX置为NULL
    输入参数：node——需要IDetree的节点
    输出参数：X——辅助文件节点
    返回值：无
*/
void ISetXNull(IFileNode* node,IFileNode* X)
{
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    char path1[50],path2[50];

    if(node->file.type[1]=='d'||node->file.type[1]=='\\')
        return;

    IGetAbsolutePath(node,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);   
    if(!strcmp(path1,path2)||IisChild(path2,path1))
        nodeX->child=NULL;
}

/*
    函数功能：激活IDetree函数，更改当前节点
    输入参数：node——需要IDetree的节点
    输出参数：cur——当前节点
    返回值：无
*/
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
    IFileNodePointer * tempNode,*nextNode,*lastNode;
    char path1[50],path2[50];

    if(node->file.type[1]=='\\') return;

    tempNode=(*curNode)->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    //假如curNode链表有后一项，递归删除后面的所有节点

    tempNode=(*curNode);
    IGetAbsolutePath(node,path2);
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);
        if(!strcmp(path1,path2)||IisChild(path1,path2))
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                    (*curNode)=tempNode;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        tempNode=lastNode;
    }
    //如果curNode链表中有node节点，将该节点从链表中除去

    if(node->file.type[1]!='\\')
        (*curNode)->child=IFindParent(node);
    //更改curNode节点

    IDetree(node);
    //激活IDetree函数

    node->file.type[0]='0';
    //关闭文件夹
}

/*
    函数功能：在View1中（单一地）选中文件节点，显示高亮
    输入参数：node——被选中的节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISelect(IFileNode* node,IFileNode* null)
{
    IFileNode* tempNode=IFindParent(node)->child;

    while(tempNode)
    {
        tempNode->flags&=29;
        tempNode=tempNode->next;
    }
    //如果当前路径下已经有被选中的节点，将该节点置为未被选中

    node->flags|=2;
    //选中该节点
}

/*
    函数功能：在View1中（复合地）选中文件节点，显示高亮
    输入参数：node——被选中的节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ICtrlSelect(IFileNode* node,IFileNode* null)
{
    if(!(node->flags&2))
        node->flags|=2;
    else
        node->flags&=5;
    //如果该节点已被选中，则解选中；否则选中该节点
}

/*
    函数功能：空操作，可用于占位/截断/刷新等
    输入参数：null1——用于占位, null2——用于占位
    输出参数：无
    返回值：无
*/
void INOP(IFileNode* null1,IFileNode* null2){}

/*
    函数功能：返回上一目录
    输入参数：null——用于占位
    输出参数：cur——当前节点
    返回值：无
*/
void IGoLeftActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;
    //返回上一目录
}

/*
    函数功能：返回下一目录
    输入参数：null——用于占位
    输出参数：cur——当前节点
    返回值：无
*/
void IGoRightActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;
    //返回下一目录
}

/*
    函数功能：交互性地获取字符串
    输入参数：x——输入框位置的横坐标, y——输入框位置的纵坐标, length——输入框的长度. flag——输入框的类型
    输出参数：string——获取的字符串
    返回值：获取的字符串的首地址
    注：flag=0 重命名;flag=1 搜素框; flag=2 输入用户名;flag=3 输入密码;flag=4 新文件/新文件夹
*/
char* IGetString(int x,int y,int length,char* string,int flag)
{
    char* org=string;       //记录下string的初始位置
    char tempChar='\0';     //用于接收输入的字符
    char temp[20];          //辅助字符串
    int n,i,t=0,j;

    fflush(stdin);
    //刷新键盘缓冲区

    setcolor(0);
    if(flag>=1&&flag<=3)
    {
        rectangle(x-1,y,x+length+1,y+27);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+1,x+length,y+26);
    }
    else
    {
        if(flag==4)
            strcpy(string,"");
        rectangle(x-1,y+6,x+length+1,y+25);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+7,x+length,y+24);   
    }
    //初始化输入框
    n=strlen(string);
    i=n;

    setcolor(144);
    if(flag!=3)
        outtextxy(x+2,y+9,string);
    else
        for(j=0;j<n;j++)
        {
            outtextxy(x+2+8*j,y+9,"*");
        }
    //如果flag==3, 加密显示输入内容

    while(1)
    {
        while(!kbhit())
        {
            if(t>0)
                setcolor(144);
            else
                setcolor(255);
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            t++;
        }
        //变量t用于计时，实现闪烁光标的效果

        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);
        //两种不同的输入框

        tempChar=getch();

        if(tempChar=='\r')  //回车键
            break;
        else if(tempChar=='\b')  //退格键
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)  //ESC键
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //左方向键
                i--;
            else if(tempChar=='M'&&n>i)    //右方向键
                i++;
            else
            {
                getch();
                tempChar=getch();
                continue;
            }
        }
        else if(n<12&&((tempChar>='0'&&tempChar<='9')||(tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||tempChar=='_'||(flag==1&&(tempChar=='?'||tempChar=='*'))))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //合法字符检验

        setcolor(144);
        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   
        //两种输入框

        if(flag!=3)
            outtextxy(x+2,y+9,string);
        else
            for(j=0;j<n;j++)
                outtextxy(x+2+8*j,y+9,"*");
        //是否加密显示
    }
    return org;
}

/*
    函数功能：激活查找函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISearchActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    FILE* fp=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+"); //覆盖的方式打开用于记录的文件
    char temp[20],path[60];     //辅助字符串

    IGetAbsolutePath(curNode->child,path);  //获得需要查找的路径
    strcpy(temp,"\0");
    IGetString(851,51,166,temp,1);  
    //得到查找的pattern

    if(temp[0])
        ISearch(path,temp,fp);
    //激活查找函数

    fclose(fp);
}

/*
    函数功能：打开exe类文件
    输入参数：exe——可执行的文件节点, null——用于占位
    输出参数：无
    返回值：无
*/
void IexeActive(IFileNode* exe,IFileNode* null)
{
    // char temp[50];

    // setfillstyle(SOLID_FILL,0);
    // bar(0,0,1024,768);
    // //营造dos终端环境

    // IGetAbsolutePath(exe,temp);
    // //得到可执行文件的绝对路径

    // system(temp);
    //系统调用，运行exe文件
}

/*
    函数功能：打开txt类文件
    输入参数：txt——可编辑的文件节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ItxtActive(IFileNode* txt,IFileNode* null)
{
    // char temp[50];

    // strcpy(temp,"BC ");
    // IGetAbsolutePath(txt,temp+3);
    // closegraph();
    // //关闭svga模式

    // system(temp);
    //系统调用，借用BC编辑器打开文本文件
}

/*
    函数功能：打开排序菜单
    输入参数：flag——排序菜单打开标志, null——用于占位
    输出参数：无
    返回值：无
*/
void ISortMenuActive(IFileNode* flag,IFileNode* null)
{
    char *n=(char*) flag;
    *n|=1;
    //将打开标志置为1
}

/*
    函数功能：激活排序函数
    输入参数：cur——当前节点, pfun——用于确定顺序的函数指针，类似于lambda
    输出参数：无
    返回值：无
*/
void ISortActive(IFileNode* cur,IFileNode* pfun)
{
    IFileNodePointer* curNode=(IFileNodePointer*)cur;
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;
    
    if(curNode->child->child)
        ISort(curNode->child,fun);
    //激活排序函数
}

/*
    函数功能：获取用户名
    输入参数：nam——用于存储用户名, null——用于占位
    输出参数：无
    返回值：无
*/
void IGetName(IFileNode* nam,IFileNode* null)
{
    char* name =(char*)nam;

    IGetString(440,440,220,name,2);
    //获取用户名
}

/*
    函数功能：获取用户名
    输入参数：pass——用于存储密码, null——用于占位
    输出参数：无
    返回值：无
*/
void IGetPassword(IFileNode* pass,IFileNode* null)
{
    char* password=(char*)pass;

    IGetString(440,490,220,password,3);
    //获取密码
}

/*
    函数功能：View0上一页
    输入参数：pag——View0的页码, null——用于占位
    输出参数：无
    返回值：无
*/
void ILastPage(IFileNode *pag,IFileNode* null)
{
    char* page=(char*)pag;

    *page-=1;
    //翻到上一页
}

/*
    函数功能：View0下一页
    输入参数：pag——View0的页码, null——用于占位
    输出参数：无
    返回值：无
*/
void INextPage(IFileNode *pag,IFileNode* null)
{
    char* page=(char*)pag;

    *page+=1;
    //翻到下一页
}
