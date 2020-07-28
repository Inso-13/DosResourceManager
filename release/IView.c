#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IHanZi.h"
#include"IDraw.h"
#include"IActive.h"
#include"IView.h"

void IPlainView()
{
    FILE *fpHZ=NULL;

    fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb");
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    settextstyle(1,0,2);

    setfillstyle(SOLID_FILL,255);
    bar(0,0,1024,768);
    setfillstyle(SOLID_FILL,84);
    bar(0,0,1024,22);
    setcolor(0);
    Iouttextxy(10,5,"DOS×ÊÔ´¹ÜÀíÆ÷",fpHZ);

    setcolor(7);
    line(0,44,1024,44);
    line(0,45,1024,45);
    IPointerDown(1000,32);
    rectangle(152,51,824,78);
    line(803,52,803,76);
    rectangle(832,51,1017,78);
    line(851,51,851,78);
    line(0,84,1024,84);
    line(0,85,1024,85);
    IPointerRight(172,62);
    IRefresh(814,64);
    IMagnifier(841,61);
    IDetailOption(995,752);
    IPictureOption(1009,752);
    IExit(1004,8);

    setcolor(7);
    line(240,88,240,742);
    line(0,744,1024,744);
    fclose(fpHZ);
}
int IView0(IFileNode* root,IFileNodePointer * curNode,IEventStackNode* top,int beginX,int beginY)
{
    int increaceY=0,temp,n;
    IEvent tempEvent;

    if(!root) return 0;         //ï¿½ï¿½ï¿½ï¿½?ï¿½ï¿½Ö¸ï¿½ï¿½
    if(!IisFolder(root)) return 0;      //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿??
    if(beginY>720) return 0;
    if(curNode->child==root)
    {
        setfillstyle(SOLID_FILL,139);
        bar(0,beginY,238,beginY+22);
    }
    if(root->hasFolder==0&&root->hasFile==0)         //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½Ðºï¿½ï¿½ï¿½ï¿½Ä¼ï¿??
    {
        outtextxy(beginX+25,beginY+7,root->file.name);
        increaceY+=24;
    }
    else if(root->file.type[0]=='0')   //ï¿½ï¿½ï¿½ï¿½ï¿½Î´ï¿½ï¿??ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½
    {
        IPointerRight(beginX+1,beginY+8);
        outtextxy(beginX+25,beginY+7,root->file.name);
        increaceY+=24;
        ISetEvent(&tempEvent,beginX,beginY+6,beginX+16,beginY+14,2,IEntreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,238,beginY+22,8,IEntreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
    }
    else        //ï¿½ï¿½ï¿½ï¿½Ç´ï¿??ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½
    {
        IPointerDown(beginX,beginY+9);
        outtextxy(beginX+25,beginY+7,root->file.name);
        increaceY+=24;
        ISetEvent(&tempEvent,beginX,beginY+6,beginX+16,beginY+14,2,IDetreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,238,beginY+22,8,IDetreeActive,root,(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
        if(root->child)
        {
            increaceY+=IView0(root->child,curNode,top,beginX+8,beginY+increaceY);
        }
    }
    if(root->next)
    {
        increaceY+=IView0(root->next,curNode,top,beginX,beginY+increaceY);
    }
    return increaceY;
}
int IView1(IFileNodePointer ** curNode,IEventStackNode* top,char isCtrl,char* page,char* delFlag)
{
    static int lastpage;
    static IFileNode* lastCurNode;
    int i,y,numOfItem=0,numOfSelected=0;
    IFileNode* tempNode;
    IEvent tempEvent;
    char temp[50];
    FILE* fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb");


    setcolor(0);
    tempNode=(*curNode)->child;
    IGetAbsolutePath(tempNode,temp);
    outtextxy(192,61,temp);
    ISetEvent(&tempEvent,884,51,1016,78,2,INOP,NULL,NULL,6);
    IEventStackPush(top,tempEvent);


    if(IFindParent((*curNode)->child))
    {
        setcolor(0);
        ISetEvent(&tempEvent,108,57,120,76,2,IEntreeActive,IFindParent((*curNode)->child),(IFileNode*)(*curNode),6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoUp(108,57);
    if((*curNode)->pre)
    {
        setcolor(0);
        ISetEvent(&tempEvent,25,59,40,76,2,IGoLeftActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoLeft(25,60);
    if((*curNode)->next)
    {
        setcolor(0);
        ISetEvent(&tempEvent,62,59,92,76,2,IGoRightActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoRight(62,60);
    setcolor(0);

    setfillstyle(SOLID_FILL,255);
    bar(853,52,1016,77);
    if(!tempNode->child)
    {
        Iouttextxy(853,61,"ÎÞÎÄ¼þ",fpHZ);
        outtextxy(560,240,"Nothing detected");
        return 0;
    }
    else
    {
        Iouttextxy(853,61,"ËÑË÷µ±Ç°ÎÄ¼þ¼Ð",fpHZ);
        ISetEvent(&tempEvent,853,52,1016,77,2,ISearchActive,(IFileNode*)(*curNode),NULL,4);
        IEventStackPush(top,tempEvent);
    }
    setcolor(50);
    IPutsHZ16(254,94,"Ãû³Æ",fpHZ);
    IPutsHZ16(430,94,"ÐÞ¸ÄÈÕÆÚ",fpHZ);
    IPutsHZ16(686,94,"ÀàÐÍ",fpHZ);
    IPutsHZ16(830,94,"´óÐ¡",fpHZ);

    setcolor(247);
    line(424,88,424,112);
    line(680,88,680,112);
    line(824,88,824,112);
    line(936,88,936,112);
    setcolor(0);


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
    else if((numOfItem-1)/(43)+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    lastCurNode=(*curNode)->child;

    tempNode=(*curNode)->child->child;
    for(i=0;i<(*page-1)*(43);i++)
        tempNode=tempNode->next;

    y=116;
    while(tempNode)
    {
        if(tempNode->flags&2)
        {
            setfillstyle(SOLID_FILL,139);
            bar(248,y,936,y+19);
        }

        Iouttextxy(256,y+6,tempNode->file.name,fpHZ);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,(tempNode->file.date%512)/32,tempNode->file.date%32,tempNode->file.time/2048,(tempNode->file.time%2048)/32);
        outtextxy(432,y+6,temp);

        if(isCtrl)
            ISetEvent(&tempEvent,248,y,936,y+19,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,248,y,936,y+19,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,248,y,936,y+19,8,IEntreeActive,tempNode,(IFileNode*)(*curNode),6);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                Iouttextxy(688,y+6+3,"´ÅÅÌ",fpHZ);
            else
                Iouttextxy(688,y+6+3,"ÎÄ¼þ¼Ð",fpHZ);
        }
        else
        {
            outtextxy(688,y+6,tempNode->file.type);
            if(!strcmp(tempNode->file.type,"EXE")||!strcmp(tempNode->file.type,"BAT"))
            {
                ISetEvent(&tempEvent,248,y,936,y+19,8,IexeActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
            if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"ASM"))
            {
                ISetEvent(&tempEvent,248,y,936,y+19,8,ItxtActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
        }
        if(!IisFolder(tempNode))
        {
            settextjustify(2,2);
            sprintf(temp,"%d KB",tempNode->file.size);
            outtextxy(928,y+6,temp);
            settextjustify(0,2);
        }
        if(y>662) break;
        y+=20;
        tempNode=tempNode->next;
    }
    sprintf(temp,"%d¸öÏîÄ¿",numOfItem);
    Iouttextxy(16,752+3,temp,fpHZ);
    if(numOfSelected)
    {
        sprintf(temp,"Ñ¡ÖÐ%d¸öÏîÄ¿",numOfSelected);
        Iouttextxy(160,752+3,temp,fpHZ);
    }
    if(isCtrl)
    {
        setcolor(144);
        outtextxy(320,752,"CTRL");
    }
    if(tempNode)
        setcolor(0);
    else
        setcolor(LIGHTGRAY);
    IGoRight(992,720);
    if(*page>1)
        setcolor(0);
    else
        setcolor(LIGHTGRAY);
    IGoLeft(928,720);
    sprintf(temp,"%d",*page);
    setcolor(0);
    outtextxy(962,722,temp);
    
    lastpage=*page;

    if(*delFlag)
    {
        *delFlag=0;
        setcolor(84);
        rectangle(412,334,662,434);
        setfillstyle(SOLID_FILL,84);
        bar(412,334,662,356);
        setfillstyle(SOLID_FILL,255);
        bar(413,357,661,433);
        rectangle(591,403,641,423);
        rectangle(521,403,571,423);

        setcolor(0);
        sprintf(temp,"%s%d%s","È·¶¨ÒªÉ¾³ýÑ¡ÖÐµÄ",numOfSelected,"¸ö¶ÔÏó£¿");
        Iouttextxy(433,377,temp,fpHZ);
        IPutsHZ16(530,406,"È·¶¨",fpHZ);
        IPutsHZ16(600,406,"È¡Ïû",fpHZ);

        ISetEvent(&tempEvent,0,0,1024,768,2,INOP,NULL,NULL,0);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521,403,571,423,2,ISetDelete,(IFileNode*)(*curNode),NULL,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591,403,641,423,2,INOP,NULL,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    fclose(fpHZ);
    return numOfSelected;
}
