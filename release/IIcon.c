/*
    版本号：1.0
    作者：郭一菲
    生成日期：2020-9-4
    说明：与文件/文件夹图标相关的函数
*/


#include<GRAPHICS.H>
#include"IIcon.h"

/*
    函数功能：磁盘图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Idisk(int x,int y)
{
   int i;
   int v[]={0,7,6,10,6,13,0,10,0,7};
   setcolor(247);
   for(i=0;i<5;i++)
   {
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
   }
   drawpoly(5,v);
   moveto(x,y+7);
   lineto(x+8,y+3);
   lineto(x+14,y+6);
   lineto(x+14,y+9);
   lineto(x+6,y+13);
   moveto(x+6,y+10);
   lineto(x+14,y+6);
   setfillstyle(9,248);
   floodfill(x+3,y+10,247);
   putpixel(x+5,y+11,140);
}

/*
    函数功能：通用图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Igeneral(int x,int y)
{
	setcolor(247);
	line(x,y,x+7,y);
	line(x+7,y,x+7,y+3);
	line(x+10,y+3,x+10,y+14);
	line(x+10,y+14,x,y+14);
	line(x,y+14,x,y);	
	line(x+7,y,x+10,y+3);
}

/*
    函数功能：文本文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Itxt(int x,int y)
{
	int i;
	Igeneral(x,y);
	for(i=1;i<3;i++)
	{
		line(x+2,y+2*i,x+5,y+2*i);
	}
	for(i=3;i<7;i++)
	{
		line(x+2,y+2*i,x+8,y+2*i);
	}
}

/*
    函数功能：word图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Idoc(int x,int y)
{
	Igeneral(x,y);
	setfillstyle(1,11);
	bar(x-3,y+3,x+6,y+12);
	setcolor(255);
	line(x-2,y+4,x,y+8);
	line(x,y+8,x+2,y+4);
	line(x+2,y+4,x+4,y+8);
	line(x+4,y+8,x+6,y+4);
}

/*
    函数功能：文件夹图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Ifolder(int x,int y)
{
	setfillstyle(1,202);
	bar(x,y,x+8,y+11);
	setcolor(206);
	line(x,y,x+3,y+3);
	line(x+3,y+3,x+3,y+15);
	line(x+3,y+15,x,y+12);
	line(x,y+12,x,y);
	floodfill(x+1,y+10,206);	
	floodfill(x+2,y+13,206);	
}

/*
    函数功能：可执行文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Iexe(int x,int y)
{
	setfillstyle(1,11);
	bar(x+4,y+4,x+9,y+11);
	setcolor(248);
	rectangle(x,y+2,x+15,y+13);
	setfillstyle(1,248);
	bar(x,y+2,x+15,y);
	setcolor(248);
	line(x+11,y+5,x+13,y+5);
	line(x+11,y+7,x+13,y+7);
	line(x+11,y+9,x+13,y+9);
}

/*
    函数功能：c源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Ic(int x,int y)
{
	setcolor(247);
	rectangle(x,y,x+11,y+12);
	setfillstyle(1,11);
	bar(x+2,y+8,x+13,y+14);
	setcolor(255);
	arc(x+9,y+11,60,300,2);
}

/*
    函数功能：h源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Ih(int x,int y)
{
	setcolor(247);
	rectangle(x,y,x+11,y+12);
	setfillstyle(1,180);
	bar(x+2,y+8,x+13,y+14);
	setcolor(255);
	line(x+6,y+9,x+6,y+13);
	line(x+8,y+11,x+8,y+13);
	arc(x+7,y+11,0,180,1);
}

/*
    函数功能：目标文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Iobj(int x,int y)
{
	int i=0;
	int v[]={0,0,7,0,7,3,10,3,10,14,0,14,0,0};
	setcolor(247);
	for(i=0;i<7;i++)
	{
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
	}
	drawpoly(7,v);
	moveto(x+7,y);
	lineto(x+10,y+3);
	setfillstyle(SOLID_FILL,255);
	bar3d(x+3,y+11,x+6,y+7,2,1);
}

/*
    函数功能：未知文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Imystery(int x,int y){Igeneral(x,y);}

/*
    函数功能：图形文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void Ipic(int x,int y)
{
	setfillstyle(SOLID_FILL,23);
	bar(x,y,x+14,y+7);
    setfillstyle(SOLID_FILL,10);
	bar(x,y+8,x+14,y+14);
	setfillstyle(SOLID_FILL,255);
	bar(x+10,y+2,x+12,y+4);
	setcolor(10);
	line(x+1,y+8,x+8,y+8);
	line(x+2,y+7,x+7,y+7);
	line(x+3,y+6,x+6,y+6);
	line(x+4,y+5,x+5,y+4);
}