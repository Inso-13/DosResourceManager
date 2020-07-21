#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IView.h"
#include"IUtility.h"
#include"IDiry.h"

void IPointerRight(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+2,y+2);
    line(x+1,y,x+3,y+2);
    line(x,y+4,x+1,y+3);
    line(x+1,y+4,x+2,y+3);
}
void IPointerDown(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+2,y+2);
    line(x,y+1,x+2,y+3);
    line(x+4,y,x+3,y+1);
    line(x+4,y+1,x+3,y+2);
}
void IGoLeft(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+2,y,x,y+2);
    line(x+2,y+5,x,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoRight(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+3,y,x+5,y+2);
    line(x+3,y+5,x+5,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoUp(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+2,y,x,y+2);
    line(x+2,y+1,x,y+3);
    line(x+3,y+1,x+4,y+2);
    line(x+3,y+2,x+4,y+3);
    line(x+2,y+2,x+2,y+7);
}
void IRefresh(int centerX,int centerY)
{
    setcolor(DARKGRAY);
    arc(centerX,centerY,0,45,3);
    arc(centerX,centerY,110,180,3);
    arc(centerX,centerY+1,180,360,3);
    line(centerX-2,centerY-3,centerX-3,centerY-3);
    putpixel(centerX-1,centerY-1,DARKGRAY);
}
void IMagnifier(int x,int y)
{
    setcolor(DARKGRAY);
    circle(x+2,y+2,2);
    circle(x+2,y+2,3);
    line(x,y+4,x-2,y+6);
    line(x,y+5,x-2,y+7);
}
void IDetailOption(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+6,y);
    line(x,y+1,x+6,y+1);
    line(x,y+3,x+6,y+3);
    line(x,y+5,x+6,y+5);
    line(x,y+6,x+6,y+6);
    putpixel(x+1,y+1,BLUE);
    putpixel(x+1,y+3,YELLOW);
    putpixel(x+1,y+5,RED);
}
void IPictureOption(int x,int y)
{
    setcolor(DARKGRAY);
    rectangle(x,y,x+6,y+6);
    setcolor(BLUE);
    line(x+1,y+1,x+5,y+1);
    line(x+3,y+1,x+5,y+1);
    setcolor(GREEN);
    line(x+1,y+3,x+2,y+3);
    line(x+1,y+4,x+5,y+4);
    line(x+1,y+5,x+5,y+5);
}
void IExit(int x,int y)
{
    setcolor(WHITE);
    line(x,y,x+4,y+4);
    line(x,y+4,x+4,y);
}
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
    rectangle(45,32,565,49);
    line(552,33,552,48);
    rectangle(570,32,636,49);
    IPointerDown(544,40);
    line(0,53,640,53);
    line(0,54,640,54);
    IPointerRight(58,39);
    IGoLeft(6,38);
    IGoRight(19,38);
    IPointerDown(29,39);
    IGoUp(38,37);
    IRefresh(559,40);
    IMagnifier(576,37);
    outtextxy(585,37,"search");
    IDetailOption(622,470);
    IPictureOption(631,470);
    IExit(628,5);

    setcolor(LIGHTGRAY);
    line(150,55,150,464);
    line(0,465,640,465);
    fclose(fpHZ);
}
int IView0(IFileNode* root,IFileNode** curNode,IEventStackNode* top,int beginX,int beginY)
{
    int increaceY=0,temp;
    IEvent tempEvent;

    if(!root) return 0;         //如果为空指针
    if(!IisFolder(root)) return 0;      //如果不是文件夹
    if(beginY>450) return 0;
    if(*curNode==root)
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
        if(root->flags&1)
        {
            setfillstyle(SOLID_FILL,LIGHTBLUE);
            pieslice(140,beginY+7,0,360,5);
        }
        IPointerRight(beginX+1,beginY+5);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,0,beginX,beginY+4,beginX+10,beginY+9,2,IEntreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,0,beginY,149,beginY+14,8,IEntreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
    }
    else        //如果是打开的文件夹
    {
        if(root->flags&1)
        {
            setfillstyle(SOLID_FILL,LIGHTBLUE);
            pieslice(140,beginY+7,0,360,5);
        }
        IPointerDown(beginX,beginY+6);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,0,beginX,beginY+4,beginX+10,beginY+9,2,IDetreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,0,beginY,149,beginY+14,8,IDetreeActive,root,curNode,6);
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
void IView1(IFileNode** curNode,IEventStackNode* top)
{
    int y;
    IFileNode* tempNode;
    char temp[20];

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

    tempNode=(*curNode);
    outtextxy(70,38,tempNode->file.path);

    if(!tempNode->child)
    {
        outtextxy(350,150,"Nothing detected");
        return;
    }
    tempNode=tempNode->child;
    y=73;
    while(tempNode)
    {
        outtextxy(160,y+4,tempNode->file.name);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date.year,tempNode->file.date.month,tempNode->file.date.day,tempNode->file.date.hour,tempNode->file.date.minute);
        outtextxy(270,y+4,temp);
        if(IisFolder(tempNode))
        {
            if(tempNode->file.type[1]=='d')
                outtextxy(430,y+4,"Disk");
            else
                outtextxy(430,y+4,"Folder");
        }
        else outtextxy(430,y+4,tempNode->file.type);
        if(!IisFolder(tempNode))
        {
            settextjustify(2,2);
            sprintf(temp,"%ld KB",tempNode->file.size);
            outtextxy(580,y+4,temp);
            settextjustify(0,2);
        }
        if(y>440) return;
        y+=13;
        tempNode=tempNode->next;
    }
}
void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNode** curNode=(IFileNode**)cur;
    IEntree(node,0);
    
    *curNode=node;
}
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNode** curNode=(IFileNode**)cur;
    IDetree(node,0);   

    *curNode=node;
}