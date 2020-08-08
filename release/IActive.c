#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<BIOS.H>
#include<CONIO.H>
#include"IEvent.h"
#include"IView.h"
#include"IUtility.h"
#include"IDiry.h"
#include"ISort.h"
#include"IInit.h"
#include"IHanZi.h"
#include"ISort.h"
#include"IActive.h"

void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * oldCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));
    IFileNodePointer * tempNode,*nextNode;

    tempNode=curNode->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }

    oldCurNode->child=curNode->child;
    oldCurNode->wait=curNode->wait;
    oldCurNode->child->del=curNode->child->del;
    oldCurNode->pre=curNode->pre;
    curNode->wait=15;
    if(curNode->pre)
    {
        curNode->pre->next=oldCurNode;
    }
    curNode->pre=oldCurNode;
    oldCurNode->next=curNode;

    IEntree(node);
    
    curNode->child=node;
    tempNode=curNode->pre;
    while(tempNode)
    {
        tempNode->wait--;
        if(tempNode->wait<0&&!tempNode->child->del)
        {
            if(tempNode->pre)
            {
                tempNode=tempNode->pre;
                tempNode->next=tempNode->next->next;
                free(tempNode->next);
                tempNode->next->pre=tempNode;
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
    tempNode=curNode->pre;
}
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer * oldCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * tempNode,*lastNode,*nextNode;

    tempNode=curNode->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    oldCurNode->child=curNode->child;
    oldCurNode->wait=curNode->wait;
    oldCurNode->child->del=curNode->child->del;
    oldCurNode->pre=curNode->pre;
    curNode->wait=15;
    if(curNode->pre)
    {
        curNode->pre->next=oldCurNode;
    }
    curNode->pre=oldCurNode;
    oldCurNode->next=curNode;    
    curNode->child=node;

    node->file.type[0]='0';
    tempNode=curNode;
    if(!tempNode->child->del)
    {
        tempNode->child->file.type[0]='1';
        IDetree(node);
    }
    while(tempNode)
    {
        lastNode=tempNode->pre;
        if(tempNode->child->del==-1&&tempNode->child->file.type[0]=='0')
        {
            tempNode->child->file.type[0]='1';
            IDetree(tempNode->child);
        }
        tempNode=lastNode;
    }
}
void ISelect(IFileNode* node,IFileNode* null)
{
    IFileNode* tempNode=IFindParent(node)->child;
    while(tempNode)
    {
        tempNode->flags&=29;
        tempNode=tempNode->next;
    }
    node->flags|=2;
}
void ICtrlSelect(IFileNode* node,IFileNode* null)
{
    if(!(node->flags&2))
        node->flags|=2;
    else
        node->flags&=5;
}
void INOP(IFileNode* null1,IFileNode* null2){}
void IGoLeftActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;
}
void IGoRightActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;
}
char* IGetString(int x,int y,int length,char* string,int flag)
{
    char* org=string;
    char temp[20];
    char tempChar='\0';
    int i,n,t=0,j;

    fflush(stdin);
    setcolor(0);
    if(flag)
    {
        rectangle(x-1,y,x+length+1,y+27);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+1,x+length,y+26);
    }
    else
    {
        string[0]='\0';
        rectangle(x-1,y+6,x+length+1,y+25);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+7,x+length,y+24);   
    }

    i=strlen(string);
    n=i;

    if(flag!=3)
        outtextxy(x+2,y+9,string);
    else
        for(j=0;j<n;j++)
        {
            outtextxy(x+2+8*j,y+9,"*");
        }

    while(1)
    {
        while(!kbhit())
        {
            if(t>0)
            {
                setcolor(144);
            }
            else
            {
                setcolor(255);
            }
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            t++;
        }
        if(flag)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   
        tempChar=getch();

        if(tempChar=='\r')
            break;
        else if(tempChar=='\b')
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //????????
                i--;
            else if(tempChar=='M'&&n>i)    //?????????
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
        setcolor(144);
        
        if(flag)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   

        if(flag!=3)
            outtextxy(x+2,y+9,string);
        else
        {
            for(j=0;j<n;j++)
            {
                outtextxy(x+2+8*j,y+9,"*");
            }
        }
    }
    return org;
}
void ISearchActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    char temp[20];

    strcpy(temp,"\0");
    IGetString(851,51,166,temp,1);
    if(temp[0])
        ISearch(curNode->child,temp);
}
void IexeActive(IFileNode* exe,IFileNode* null)
{
    char temp[50];
    setfillstyle(SOLID_FILL,0);
    bar(0,0,1024,768);
    IGetAbsolutePath(exe,temp);
    system(temp);
}
void ItxtActive(IFileNode* txt,IFileNode* null)
{
    char temp[50];
    strcpy(temp,"BC ");
    IGetAbsolutePath(txt,temp+3);
    SVGA_Deinit();
    system(temp);
}
void ISortMenuActive(IFileNode* flag,IFileNode* null)
{
    int *n=(int*) flag;
    *n=1;
}
void ISortActive(IFileNode* cur,IFileNode* pfun)
{
    IFileNodePointer* curNode=(IFileNodePointer*)cur;
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;
    if(curNode->child->child)
        ISort(curNode->child,fun);
}
void IGetName(IFileNode* nam,IFileNode* null)
{
    char* name =(char*)nam;
    IGetString(440,440,220,name,2);
}
void IGetPassword(IFileNode* pass,IFileNode* null)
{
    char* password=(char*)pass;
    IGetString(440,490,220,password,3);
}