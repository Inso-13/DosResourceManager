#include<GRAPHICS.H>
#include"IDraw.h"

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
    line(x+2,y,x,y+2);
    line(x+2,y+5,x,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoRight(int x,int y)
{
    line(x+3,y,x+5,y+2);
    line(x+3,y+5,x+5,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoUp(int x,int y)
{
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