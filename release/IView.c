#include<GRAPHICS.H>
#include<CONIO.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IHanZi.h"
#include"IDraw.h"
#include"IIcon.h"
#include"IActive.h"
#include"IMenu.h"
#include"IView.h"
void IPlainLogin()
{
    int i;
    
    setfillstyle(SOLID_FILL,248);
    bar(0,0,1024,768);
    setcolor(255);
    for(i=0;i<10;i++)
    {
        circle(512,250,i+100);
        circle(512,230,i+30);
        arc(512+40,340,125,180,i+90);
        arc(512-40,340,0,55,i+90);
        settextstyle(3,0,3);
    }
}
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ)
{
    int i;
    IEvent tempEvent;

    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in ILogin");
    }
    setcolor(255);
    Iouttextxy(370,450,"用户名:",fpHZ);
    Iouttextxy(370+16,500,"密码:",fpHZ);

    setfillstyle(SOLID_FILL,255);
    bar(440,450-10,660,450-10+27);
    bar(440,500-10,660,500-10+27);

    setfillstyle(SOLID_FILL,247);
    bar(370,550,470,550+27);
    bar(370+190,550,470+190,550+27);

    setcolor(255);
    Iouttextxy(370+2,550+9,"登录(管理员)",fpHZ);
    Iouttextxy(370+10+190,550+9,"取消(游客)",fpHZ);

    if(id==-1)
    {
        setcolor(144);
        Iouttextxy(370+10+190,600+9,"用户名或密码错误，请重新输入",fpHZ);
        strcpy(name,"\0");
        strcpy(password,"\0");
    }

    setcolor(0);
    outtextxy(440+2,440+9,name);
    
    for(i=0;i<strlen(password);i++)
    {
        outtextxy(440+2+8*i,490+9,"*");
    }

    ISetEvent(&tempEvent,440,450-10,660,450-10+28,2,IGetName,(IFileNode*)name,NULL,1);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,440,500-10,660,500-10+28,2,IGetPassword,(IFileNode*)password,NULL,1);
    IEventStackPush(top,tempEvent);
}
void IPlainView(FILE* fpHZ)
{
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IPlainView");
    }
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    settextstyle(1,0,2);

    setfillstyle(SOLID_FILL,255);
    bar(0,0,1024,768);
    setfillstyle(SOLID_FILL,84);
    bar(0,0,1024,22);
    setcolor(0);
    Iouttextxy(10,5,"DOS资源管理器",fpHZ);

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
    IExit(1004,8);

    setcolor(7);
    line(240,88,240,742);
    line(0,744,1024,744);
}
int IView0(IFileNode* root,IFileNodePointer ** curNode,IEventStackNode* top,int beginX,int beginY,char* page,char flag)
{
    int increaceY=0,temp,n;
    char thisPage=1;
    char tempStr[3];
    IEvent tempEvent;

    if(!root) return 0;         
    if(!IisFolder(root)) return 0;  //合法性检验

    // if(beginY>110+590*(*page)) return 0;
    if(beginY<110+590*(*page-1)||beginY>110+590*(*page))
        thisPage=0;

    if(thisPage&&(*curNode)->child==root)
    {
        setfillstyle(SOLID_FILL,139);
        bar(0,beginY-(*page-1)*590,238,beginY-(*page-1)*590+22);
    }
    if(root->hasFolder==0&&root->hasFile==0)         //空文件夹
    {
        if(thisPage)
        {
            Ifolder(beginX+11,beginY-(*page-1)*590+4);
            setcolor(0);
            outtextxy(beginX+25+10,beginY-(*page-1)*590+7,root->file.name);
            ISetEvent(&tempEvent,0,beginY-(*page-1)*590,238,beginY-(*page-1)*590+22,8,IEntreeActive,root,(IFileNode*)curNode,6);
            IEventStackPush(top,tempEvent);
        }
        increaceY+=24;
    }
    else if(root->file.type[0]=='0')   //未打开
    {
        if(thisPage)
        {
            IPointerRight(beginX+1,beginY-(*page-1)*590+8);
            if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                Idisk(beginX+11,beginY-(*page-1)*590+4);
            else
                Ifolder(beginX+11,beginY-(*page-1)*590+4);
            setcolor(0);
            outtextxy(beginX+25+10,beginY-(*page-1)*590+7,root->file.name);
            ISetEvent(&tempEvent,beginX,beginY-(*page-1)*590+6,beginX+16,beginY-(*page-1)*590+14,2,IEntreeActive,root,(IFileNode*)curNode,6);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,0,beginY-(*page-1)*590,238,beginY-(*page-1)*590+22,8,IEntreeActive,root,(IFileNode*)curNode,6);
            IEventStackPush(top,tempEvent);
        }
        increaceY+=24;
    }
    else        //打开的文件夹
    {
        if(thisPage)
        {
            IPointerDown(beginX,beginY+9);
            if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                Idisk(beginX+11,beginY-(*page-1)*590+4);
            else
                Ifolder(beginX+11,beginY-(*page-1)*590+4);
            setcolor(0);
            outtextxy(beginX+25+10,beginY-(*page-1)*590+7,root->file.name);
            ISetEvent(&tempEvent,beginX,beginY-(*page-1)*590+6,beginX+16,beginY-(*page-1)*590+14,2,IDetreeActive,root,(IFileNode*)(*curNode),6);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,0,beginY-(*page-1)*590,238,beginY-(*page-1)*590+22,8,IDetreeActive,root,(IFileNode*)(*curNode),6);
            IEventStackPush(top,tempEvent);
        }
        increaceY+=24;
        if(root->child)
        {
            increaceY+=IView0(root->child,curNode,top,beginX+8,beginY+increaceY,page,0);
        }
    }
    if(root->next)
    {
        increaceY+=IView0(root->next,curNode,top,beginX,beginY+increaceY,page,0);
    }

    if(flag)
    {
        if(*page>1)
        {
            ISetEvent(&tempEvent,150,720,168,738,2,ILastPage,page,NULL,2);
            IEventStackPush(top,tempEvent);
            setcolor(0);
        }
        else
            setcolor(LIGHTGRAY);
        IGoLeft(150,720);
        if(*page<=(increaceY/590))
        {
            ISetEvent(&tempEvent,210,720,228,738,2,INextPage,page,NULL,2);
            IEventStackPush(top,tempEvent);
            setcolor(0);
        }
        else
            setcolor(LIGHTGRAY);
        IGoRight(210,720);
        sprintf(tempStr,"%d",*page);
        setcolor(0);
        outtextxy(182,722,tempStr);
    }
    return increaceY;
}
int IView1(IFileNodePointer ** curNode,IEventStackNode* top,char isCtrl,char* page,char* delFlag,FILE* fpHZ)
{
    static int lastpage;
    static IFileNode* lastCurNode;
    int i,y,numOfItem=0,numOfSelected=0;
    IFileNode* tempNode;
    IEvent tempEvent;
    char temp[50];

    settextstyle(0,0,0);
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IView1");
    }

    setcolor(0);
    tempNode=(*curNode)->child;
    IGetAbsolutePath(tempNode,temp);
    outtextxy(192,61,temp);
    ISetEvent(&tempEvent,803,51,824,78,2,INOP,NULL,NULL,6);
    IEventStackPush(top,tempEvent);

    if(IFindParent((*curNode)->child))
    {
        setcolor(0);
        ISetEvent(&tempEvent,108,57,120,76,2,IEntreeActive,IFindParent((*curNode)->child),(IFileNode*)curNode,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoUp(108,57);
    if((*curNode)->pre&&(*curNode)->pre->child)
    {
        setcolor(0);
        ISetEvent(&tempEvent,25,59,40,76,2,IGoLeftActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoLeft(25,60);
    if((*curNode)->next&&(*curNode)->next->child)
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
        Iouttextxy(853,61,"无内容",fpHZ);
        if(!strcmp(tempNode->file.type,"0ds"))
            Iouttextxy(560,240,"仅管理员可见",fpHZ);
        else
            Iouttextxy(530,240,"未打开文件夹或未检索到内容",fpHZ);
        return 0;
    }
    else
    {
        Iouttextxy(853,61,"在本文件夹中搜索",fpHZ);
        ISetEvent(&tempEvent,853,52,1016,77,2,ISearchActive,(IFileNode*)(*curNode),NULL,4);
        IEventStackPush(top,tempEvent);
    }
    setcolor(50);
    IPutsHZ16(254,94,"文件名",fpHZ);
    IPutsHZ16(430,94,"修改日期",fpHZ);
    IPutsHZ16(686,94,"类型",fpHZ);
    IPutsHZ16(830,94,"大小",fpHZ);

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
    else if((numOfItem-1)/(30)+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    lastCurNode=(*curNode)->child;

    tempNode=(*curNode)->child->child;
    for(i=0;i<(*page-1)*(30);i++)
        tempNode=tempNode->next;

    y=116;
    while(tempNode)
    {
        if(tempNode->flags&2)
        {
            setfillstyle(SOLID_FILL,139);
            bar(248,y,936,y+19);
        }
        if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"txt"))
            Itxt(256,y+2);
        else if(!strcmp(tempNode->file.type,"DOC")||!strcmp(tempNode->file.type,"doc"))
            Idoc(256,y+2);
        else if(!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"c")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"cpp"))
            Ic(256,y+2);
        else if(!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"h")||!strcmp(tempNode->file.type,"HPP")||!strcmp(tempNode->file.type,"hpp"))
            Ih(256,y+2);
        else if(!strcmp(tempNode->file.type,"obj")||!strcmp(tempNode->file.type,"OBJ"))
            Iobj(256,y+2);
        else if(!strcmp(tempNode->file.type,"exe")||!strcmp(tempNode->file.type,"EXE"))
            Iexe(256,y+2);
        else if(!strcmp(tempNode->file.type,"jpg")||!strcmp(tempNode->file.type,"JPG")||!strcmp(tempNode->file.type,"bmp")||!strcmp(tempNode->file.type,"BMP"))
            Ipic(256,y+2);
        else if(IisFolder(tempNode))
        {
            if(tempNode->file.type[1]=='d')
                Idisk(256,y+2);
            else
                Ifolder(256,y+2);
        }
        else
            Imystery(256,y+2);

        setcolor(0);
        Iouttextxy(256+20,y+6,tempNode->file.name,fpHZ);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,(tempNode->file.date%512)/32,tempNode->file.date%32,tempNode->file.time/2048,(tempNode->file.time%2048)/32);
        outtextxy(432,y+6,temp);

        if(isCtrl)  //ctrl
            ISetEvent(&tempEvent,248,y,936,y+19,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,248,y,936,y+19,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,248,y,936,y+19,8,IEntreeActive,tempNode,(IFileNode*)curNode,6);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                Iouttextxy(688,y+6+3,"磁盘",fpHZ);
            else
                Iouttextxy(688,y+6+3,"文件夹",fpHZ);
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
    sprintf(temp,"%d个项目",numOfItem);
    Iouttextxy(16,752+3,temp,fpHZ);
    if(numOfSelected)
    {
        sprintf(temp,"选中%d个项目",numOfSelected);
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
        sprintf(temp,"%s%d%s","确定要删除选中的",numOfSelected,"个项目吗？");
        Iouttextxy(433,377,temp,fpHZ);
        IPutsHZ16(530,406,"确定",fpHZ);
        IPutsHZ16(600,406,"取消",fpHZ);

        ISetEvent(&tempEvent,0,0,1024,768,2,INOP,NULL,NULL,0);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521,403,571,423,2,ISetDelete,(IFileNode*)(*curNode),NULL,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591,403,641,423,2,INOP,NULL,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    return numOfSelected;
}
