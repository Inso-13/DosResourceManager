#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include"IEvent.h"
#include"IType.h"
#include"IMouse.h"

void bgice(IFileNode far*,IFileNode far*);
void outice(IFileNode far*,IFileNode far*);
void inice(IFileNode far*,IFileNode far*);
int main()
{
    IEventStackNode* top = (IEventStackNode*)malloc(sizeof(IEventStackNode));
    int MouseX,MouseY;
    int mouseDraw[16][16],mouseSave[16][16];
    int gd=DETECT,gm,i;
    
    IEvent ice[3]={{0,0,0,640,480,2,bgice,0,0},{0,100,100,500,500,4,outice,0,0},{0,200,200,300,300,8,inice,0,0}};

    initgraph(&gd,&gm,"c:\\Borlandc\\bgi");
    IMouseMath(mouseDraw);
    IMouseSetXY(100,100);
    IMouseOn(MouseX,MouseY,mouseDraw,mouseSave);


    top->next=NULL;
    for(i=0;i<3;i++) IEventStackPush(top,ice[i]);
    rectangle(100,100,500,500);
    setcolor(BLUE);
    rectangle(200,200,300,300);
    setcolor(RED);
    while(!kbhit())
    {
        IEventStackActive(top,MouseX,MouseY,IMouseStatus(&MouseX,&MouseY,mouseDraw,mouseSave));
    }
    IDelStack(top);
    return 0;
}
void bgice(IFileNode far* a,IFileNode far* b)
{
    outtextxy(100,100,"bg is clicked");
}
void outice(IFileNode far* a,IFileNode far* b)
{
    outtextxy(200,200,"outdiv is clicked");
}
void inice(IFileNode far* a,IFileNode far* b)
{
    outtextxy(300,300,"indiv is clicked");
}