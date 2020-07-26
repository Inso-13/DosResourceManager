#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<BIOS.H>
#include<CONIO.H>
#include<STRING.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
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
    oldCurNode->flag=curNode->flag;
    oldCurNode->pre=curNode->pre;
    curNode->wait=15;
    curNode->flag=0;
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
        if(tempNode->wait<0&&!tempNode->flag)
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
    // if(tempNode->child!=curNode->child&&tempNode->child!=IFindParent(curNode->child)&&tempNode->flag!=1)
    //     IDetree(tempNode->child);
}
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * tempNode=curNode,*lastNode;

    node->file.type[0]='0';

    if(!tempNode->flag)
        IDetree(node);
    // while(tempNode)
    // {
    //     lastNode=tempNode->pre;
    //     if(tempNode->flag==-1)
    //         IDetree(node);
    //     tempNode=lastNode;
    // }
    curNode->child=node;
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
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX)
{
    IEvent tempEvent;
    if(mouseX>590) mouseX=590;
    if(mouseY>380) mouseY=380;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX);
    ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*5,mouseX+54,mouseY+14+15*5,2,ISetNewFile,curNode,nodeX,4);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*6,mouseX+54,mouseY+14+15*6,2,ISetNewFolder,curNode,nodeX,6);
    IEventStackPush(top,tempEvent);
    if(curNode->child->file.type[1]=='\\')
        return;
    if(numOfSelected)
    {
        if(numOfSelected==1)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*4,mouseX+54,mouseY+14+15*4,2,ISetRename,curNode,NULL,4);
            IEventStackPush(top,tempEvent);
        }
        ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+54,mouseY+14,2,ISetCopy,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*1,mouseX+54,mouseY+14+15*1,2,ISetCut,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*2,mouseX+54,mouseY+14+15*2,2,ISetDelete,curNode,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    if(!numOfSelected||(curNode->child==nodeX->child))
    {
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*3,mouseX+54,mouseY+14+15*3,2,ISetPaste,curNode,nodeX,6);
        IEventStackPush(top,tempEvent);
    }
}
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX)
{
    int i;
    char str[7][11]={"copy","cut","delete","paste","rename","new file","new folder"};
    setfillstyle(SOLID_FILL,WHITE);
    bar(x,y,x+95,y+105);
    setcolor(BLUE);
    rectangle(x,y,x+95,y+105);

    for(i=1;i<7;i++)
        line(x+1,y+15*i,x+94,y+15*i);
        
    if(curNode->child->file.type[1]=='\\')
        setcolor(LIGHTGRAY);
    outtextxy(x+3,y+15*5+3,str[5]);
    outtextxy(x+3,y+15*6+3,str[6]);
    for(i=0;i<3;i++)
    {
        if(!numOfSelected)
            setcolor(LIGHTGRAY);
        outtextxy(x+3,y+15*i+3,str[i]);    
    }
    if((!numOfSelected||curNode->child==nodeX->child)&&nodeX->child&&curNode->child->file.type[1]!='\\')
        setcolor(BLUE);
    else
        setcolor(LIGHTGRAY);
    outtextxy(x+3,y+48,str[3]);
    if(numOfSelected==1&&curNode->child->file.type[1]!='\\')
        setcolor(BLUE);
    else
        setcolor(LIGHTGRAY);
    outtextxy(x+3,y+63,str[4]);       

}
void ISetCopy(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=curNode;

    while(tempNode)
    {
        if(tempNode->flag==1)
            tempNode->flag=-1;
        tempNode=tempNode->pre;
    }
    curNode->flag=1;
    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    
    nodeX->child=curNode->child;
}
void ISetCut(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=curNode;

    while(tempNode)
    {
        if(tempNode->flag==1)
            tempNode->flag=-1;
        tempNode=tempNode->pre;
    }
    curNode->flag=1;
    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    nodeX->child=curNode->child;
    nodeX->child->flags|=1;
}
void ISetPaste(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    Icplr(nodeX->child,curNode->child);
    if(nodeX->child->flags&1)
        Irmlr(nodeX->child,NULL);
}
void ISetDelete(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    
    Irmlr(curNode->child,NULL);
}
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
char* IGetString(int x,int y,int length,char* string)
{
    char* org=string;
    char temp[20];
    char tempChar='\0';
    int i=0,n=0,t=0;

    setcolor(DARKGRAY);
    rectangle(x-1,y,x+length+1,y+15);
    strcpy(string,"\0");
    setfillstyle(SOLID_FILL,WHITE);

    while(1)
    {
        bar(x,y+1,x+length,y+14);
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
        else if(n<12&&((tempChar>='0'&&tempChar<='9')||(tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||tempChar=='_'))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        setcolor(RED);
        bar(x,y+1,x+length,y+14);
        outtextxy(x,y+4,string);
        while(!kbhit())
        {
            if(t>0)
                setcolor(RED);
            else
                setcolor(WHITE);
            line(x+8*i,y+3,x+8*i,y+12);
            t++;
        }
    }
    return org;
}
void ISetRename(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(!(tempNode->flags&2))
    {
        i++;
        tempNode=tempNode->next;
    }
    IGetString(156,73+13*i,100,temp);
    if(temp[0])
        Irename(tempNode,temp);
}
void ISetNewFile(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    IGetString(156,73+13*i,100,temp);
    if(temp[0])
        Inew(curNode->child,temp);
}
void ISetNewFolder(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    IGetString(156,73+13*i,100,temp);
    if(temp[0])
        Imkdir(curNode->child,temp);
}