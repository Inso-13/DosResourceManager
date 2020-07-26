#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IDraw.h"
#include"IActive.h"
#include"IView.h"

void IPlainView()
{
    FILE *fpHZ;

    fpHZ=fopen("HZ16","rb");

    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    setbkcolor(WHITE);
    settextstyle(0,0,1);

    cleardevice();
    setfillstyle(1,DARKGRAY);
    bar(0,0,640,14);
    setcolor(LIGHTGRAY);
    line(0,28,640,28);
    line(0,29,640,29);
    IPointerDown(625,20);
    rectangle(95,32,515,49);
    line(502,33,502,48);
    rectangle(520,32,636,49);
    // IPointerDown(544,40);
    line(0,53,640,53);
    line(0,54,640,54);
    IPointerRight(108,39);
    IRefresh(509,40);
    // IMagnifier(526,37);
    outtextxy(530,37,"Made by Inso");
    IDetailOption(622,470);
    IPictureOption(631,470);
    IExit(628,5);

    setcolor(LIGHTGRAY);
    line(150,55,150,464);
    line(0,465,640,465);
    fclose(fpHZ);
}
int IView0(IFileNode* root,IFileNodePointer * curNode,IEventStackNode* top,int beginX,int beginY)
{
    int increaceY=0,temp,n;
    IEvent tempEvent;

    if(!root) return 0;         //如果为空指针
    if(!IisFolder(root)) return 0;      //如果不是文件夹
    if(beginY>450) return 0;
    if(curNode->child==root)
    {
        setfillstyle(SOLID_FILL,LIGHTGRAY);
        bar(0,beginY,149,beginY+14);
    }
    if(root->hasFolder==0&&root->hasFile==0)         //如果无子文件夹和子文件
    {
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
    }
    else if(root->file.type[0]=='0')   //如果是未打开的文件夹
    {
        IPointerRight(beginX+1,beginY+5);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,beginX,beginY+4,beginX+10,beginY+9,2,IEntreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,149,beginY+14,8,IEntreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
    }
    else        //如果是打开的文件夹
    {
        IPointerDown(beginX,beginY+6);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,beginX,beginY+4,beginX+10,beginY+9,2,IDetreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,149,beginY+14,8,IDetreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        if(root->child)
        {
            increaceY+=IView0(root->child,curNode,top,beginX+5,beginY+increaceY);
        }
    }
    if(root->next)
    {
        increaceY+=IView0(root->next,curNode,top,beginX,beginY+increaceY);
    }
    return increaceY;
}
int IView1(IFileNodePointer ** curNode,IEventStackNode* top,char isCtrl,char* page)
{
    static int lastpage;
    static IFileNode* lastCurNode;
    int i,y,numOfItem=0,numOfSelected=0;
    IFileNode* tempNode;
    IEvent tempEvent;
    char temp[50];

    setcolor(DARKGRAY);
    tempNode=(*curNode)->child;
    IGetAbsolutePath(tempNode,temp);
    outtextxy(120,38,temp);
    ISetEvent(&tempEvent,553,32,635,49,2,INOP,NULL,NULL,6);
    IEventStackPush(top,tempEvent);


    if(IFindParent((*curNode)->child))
    {
        setcolor(DARKGRAY);
        ISetEvent(&tempEvent,68,37,75,48,2,IEntreeActive,IFindParent((*curNode)->child),(IFileNode*)(*curNode),6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoUp(68,38);
    if((*curNode)->pre)
    {
        setcolor(DARKGRAY);
        ISetEvent(&tempEvent,16,37,25,48,2,IGoLeftActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoLeft(16,38);
    if((*curNode)->next)
    {
        setcolor(DARKGRAY);
        ISetEvent(&tempEvent,39,37,58,48,2,IGoRightActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoRight(39,38);
    setcolor(DARKGRAY);


    if(!tempNode->child)
    {
        outtextxy(350,150,"Nothing detected");
        return 0;
    }

    setcolor(BLUE);
    outtextxy(160,60,"Name");
    outtextxy(270,60,"Mod Time");
    outtextxy(430,60,"Type");
    outtextxy(520,60,"Size");
    setcolor(LIGHTGRAY);
    line(265,55,265,70);
    line(425,55,425,70);
    line(515,55,515,70);
    line(585,55,585,70);
    setcolor(DARKGRAY);


    tempNode=(*curNode)->child->child;
    while(tempNode)
    {
        numOfItem++;
        if(tempNode->flags&2)
            numOfSelected++;
        tempNode=tempNode->next;
    }
    if(lastCurNode!=(*curNode)->child)
        *page=1;
    else if((numOfItem-1)/27+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    lastCurNode=(*curNode)->child;

    tempNode=(*curNode)->child->child;
    for(i=0;i<(*page-1)*27;i++)
        tempNode=tempNode->next;

    y=73;
    while(tempNode)
    {
        if(tempNode->flags&2)
        {
            setfillstyle(SOLID_FILL,LIGHTGRAY);
            bar(155,y,585,y+12);
        }

        outtextxy(160,y+4,tempNode->file.name);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,(tempNode->file.date%512)/32,tempNode->file.date%32,tempNode->file.time/2048,(tempNode->file.time%2048)/32);
        outtextxy(270,y+4,temp);

        if(isCtrl)
            ISetEvent(&tempEvent,155,y,585,y+12,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,155,y,585,y+12,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,155,y,585,y+12,8,IEntreeActive,tempNode,(IFileNode*)(*curNode),6);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                outtextxy(430,y+4,"Disk");
            else
                outtextxy(430,y+4,"Folder");
        }
        else outtextxy(430,y+4,tempNode->file.type);
        if(!IisFolder(tempNode))
        {
            settextjustify(2,2);
            sprintf(temp,"%d KB",tempNode->file.size);
            outtextxy(580,y+4,temp);
            settextjustify(0,2);
        }
        if(y>414) break;
        y+=13;
        tempNode=tempNode->next;
    }
    sprintf(temp,"%d items",numOfItem);
    outtextxy(10,470,temp);
    if(numOfSelected)
    {
        sprintf(temp,"%d selected",numOfSelected);
        outtextxy(100,470,temp);
    }
    if(isCtrl)
    {
        setcolor(RED);
        outtextxy(200,470,"CTRL");
    }
    if(tempNode)
        setcolor(DARKGRAY);
    else
        setcolor(LIGHTGRAY);
    IGoRight(620,450);
    if(*page>1)
        setcolor(DARKGRAY);
    else
        setcolor(LIGHTGRAY);
    IGoLeft(580,450);
    sprintf(temp,"%d",*page);
    setcolor(DARKGRAY);
    outtextxy(600,450,temp);
    
    lastpage=*page;
    return numOfSelected;
}
