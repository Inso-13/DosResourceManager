#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<BIOS.H>
#include<CONIO.H>
#include<GRAPHICS.H>
#include"IEvent.h"
#include"IView.h"
#include"IUtility.h"
#include"IDiry.h"
#include"ISort.h"
#include"IHanZi.h"
#include"IActive.h"
#include"IMenu.h"

void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX,int *menuFlag,char *delFlag,FILE* fpHZ)
{
    IEvent tempEvent;
    int i;
    int (*lambda[8])(IFileNode*,IFileNode*)={ISortDateUp,ISortDateDown,ISortSizeUp,ISortSizeDown,ISortNameUp,ISortNameDown,ISortTypeUp,ISortTypeDown};

    if(mouseX>944) mouseX=944;
    if(mouseY>608) mouseY=608;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX,*menuFlag,fpHZ);
    if(*menuFlag==0)
    {
        if(curNode->child->file.type[1]=='\\')
            return;
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*5,mouseX+80,mouseY+19+20*5,2,ISetNewFile,(IFileNode*)curNode,(IFileNode*)nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*6,mouseX+80,mouseY+19+20*6,2,ISetNewFolder,(IFileNode*)curNode,(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*7,mouseX+80,mouseY+19+20*7,2,ISortMenuActive,(IFileNode*)menuFlag,NULL,4);
        IEventStackPush(top,tempEvent);
        if(numOfSelected)
        {
            if(numOfSelected==1)
            {
                ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*4,mouseX+80,mouseY+19+20*4,2,ISetRename,(IFileNode*)curNode,NULL,4);
                IEventStackPush(top,tempEvent);
            }
            ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+80,mouseY+19,2,ISetCopy,(IFileNode*)curNode,(IFileNode*)nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*1,mouseX+80,mouseY+19+20*1,2,ISetCut,(IFileNode*)curNode,(IFileNode*)nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*2,mouseX+80,mouseY+19+20*2,2,ISetDeleteComfirm,(IFileNode*)delFlag,NULL,4);
            IEventStackPush(top,tempEvent);
        }
        if(!numOfSelected||(curNode->child==nodeX->child))
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*3,mouseX+80,mouseY+19+20*3,2,ISetPaste,(IFileNode*)curNode,(IFileNode*)nodeX,6);
            IEventStackPush(top,tempEvent);
        }
    }
    else
    {
        for(i=0;i<8;i++)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*i,mouseX+80,mouseY+19+20*i,2,ISortActive,(IFileNode*)curNode,(IFileNode*)lambda[i],4);
            IEventStackPush(top,tempEvent);
        }
        *menuFlag=0;
    }
}
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,int menuFlag,FILE* fpHZ)
{
    int i;
    unsigned char str[2][8][11]={{"复制","剪切","删除","粘贴","重命名","新文件","新文件夹","排序.."},{"按日期升序","按日期降序","按大小升序","按大小降序","按名称升序","按名称降序","按类型升序","按类型降序"}};
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IDrawMenu");
    }
    setfillstyle(SOLID_FILL,255);
    bar(x,y,x+95,y+160);
    setcolor(15);
    rectangle(x,y,x+95,y+160);

    for(i=1;i<8;i++)
        line(x+1,y+20*i,x+94,y+20*i);
    if(!menuFlag)
    { 
        if(curNode->child->file.type[1]=='\\')
            setcolor(247);
        IPutsHZ16(x+3,y+20*5+3,str[0][5],fpHZ);
        IPutsHZ16(x+3,y+20*6+3,str[0][6],fpHZ);
        Iouttextxy(x+3,y+20*7+6,str[0][7],fpHZ);
        for(i=0;i<3;i++)
        {
            if(!numOfSelected)
                setcolor(247);
            IPutsHZ16(x+3,y+20*i+3,str[0][i],fpHZ);    
        }
        if((!numOfSelected||curNode->child==nodeX->child)&&nodeX->child&&curNode->child->file.type[1]!='\\')
            setcolor(15);
        else
            setcolor(247);
        IPutsHZ16(x+3,y+3+20*3,str[0][3],fpHZ);
        if(numOfSelected==1&&curNode->child->file.type[1]!='\\')
            setcolor(15);
        else
            setcolor(247);
        IPutsHZ16(x+3,y+4*20+3,str[0][4],fpHZ);       
    }
    else
    {
        setcolor(15);
        for(i=0;i<8;i++)
        {
            IPutsHZ16(x+3,y+20*i+3,str[1][i],fpHZ);    
        }
    }
}
void ISetCopy(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=curNode;

    while(tempNode)
    {
        if(tempNode->child->del==1)
            tempNode->child->del=-1;
        tempNode=tempNode->pre;
    }
    curNode->child->del=1;
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
        if(tempNode->child->del==1)
            tempNode->child->del=-1;
        tempNode=tempNode->pre;
    }
    curNode->child->del=1;
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
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null)
{
    char* flag=(char*)flagx;
    *flag=1;
}
void ISetRename(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    strcpy(temp,"\0");
    while(!(tempNode->flags&2))
    {
        i++;
        tempNode=tempNode->next;
    }
    IGetString(254,110+20*i,150,temp,0);
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
    IGetString(254,110+20*i,150,temp,0);
    if(temp[0])
        if(!Inew(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            delay(1500);
        }
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
    IGetString(254,110+20*i,150,temp,0);
    if(temp[0])
        if(!Imkdir(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            delay(1500);
        }
}