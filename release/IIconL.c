/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-24
 *   说明：与文件/文件夹在大图标模式下情况下显示图标相关的函数
 **************************************************
 */

#include"IIconL.h"

/*
    函数功能：大图标模式下磁盘图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IdiskL(int x,int y)
{
   int i;
   int v[]={-10,51,20,65,20,79,-10,65,-10,51};

   setlinestyle(SOLID_LINE,0,THICK_WIDTH);
   setcolor(DRM_LIGHTGRAY);
   for(i=0;i<5;i++)
   {
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
   }
   drawpoly(5,v);
   moveto(x-10,y+51);
   lineto(x+30,y+31);
   lineto(x+60,y+45);
   lineto(x+60,y+59);
   lineto(x+20,y+79);
   moveto(x+20,y+65);
   lineto(x+60,y+45);
   setfillstyle(SOLID_FILL,DRM_DARKGRAY);
   floodfill(x+5,y+65,DRM_LIGHTGRAY);
   setlinestyle(SOLID_LINE,0,NORM_WIDTH);
   setcolor(DRM_LIGHTGREEN);
   setfillstyle(SOLID_FILL,DRM_LIGHTGREEN);
   fillellipse(x+15,y+70,2,2);
}

/*
    函数功能：大图标模式下通用图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IgeneralL(int x,int y)
{
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	line(x,y,x+34,y);
	line(x+34,y,x+34,y+14);
	line(x+34,y+14,x+49,y+14);
	line(x+34,y,x+49,y+14);
	line(x+49,y+14,x+49,y+79);
	line(x+49,y+79,x,y+79);	
	line(x,y+79,x,y);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH); 
}

/*
    函数功能：大图标模式下文本文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void ItxtL(int x,int y)
{
	int i;

	IgeneralL(x,y);
	setcolor(DRM_DARKGRAY);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	for(i=2;i<=5;i++)
	{
		line(x+5,y+3*i,x+29,y+3*i);
	}
	for(i=6;i<=24;i++)
	{
		line(x+5,y+3*i,x+44,y+3*i);
	}
}

/*
    函数功能：大图标模式下word文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IdocL(int x,int y)
{
	int i; 

	IgeneralL(x,y);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x-10,y+12,x+30,y+48);
	setcolor(DRM_WHITE);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	line(x-8,y+16,x,y+42);
	line(x,y+42,x+8,y+16);
	line(x+8,y+16,x+16,y+42);
	line(x+16,y+42,x+24,y+16);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH); 
	setcolor(DRM_LIGHTGRAY);
	for(i=14;i<=18;i++)
	{
		line(x+5,y+4*i,x+43,y+4*i);
	}
}

/*
    函数功能：大图标模式下文件夹图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IfolderL(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_ORANGE);
	bar(x,y,x+43,y+64);
	setcolor(DRM_LIGHTYELLOW);
	rectangle(x,y,x+43,y+64);
	setcolor(DRM_ORANGE);
	line(x,y+64,x+16,y+64);
	setcolor(DRM_LIGHTYELLOW);
	line(x,y,x+16,y+16);
	line(x+16,y+16,x+16,y+80);
	line(x+16,y+80,x,y+64);
	line(x,y+64,x,y);
	setcolor(DRM_YELLOW);
	floodfill(x+5,y+53,DRM_LIGHTYELLOW);	
	floodfill(x+11,y+69,DRM_LIGHTYELLOW);	
}

/*
    函数功能：大图标模式下可执行文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IexeL(int x,int y)
{
	int i;

	setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
	bar(x-10,y+14,x+60,y+66);
	setcolor(DRM_DARKGRAY);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	rectangle(x-10,y+14,x+60,y+66);
	setfillstyle(SOLID_FILL,DRM_DARKGRAY);
	bar(x-11,y+9,x+61,y+14);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	bar(x+5,y+17,x+57,y+63);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x+7,y+19,x+35,y+55);
	setcolor(DRM_DARKGRAY);
	line(x-5,y+20,x+2,y+20);
	line(x-5,y+27,x+2,y+27);
	line(x-5,y+34,x+2,y+34);
	line(x-5,y+41,x+2,y+41);
	setcolor(DRM_LIGHTGRAY);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	for(i=4;i<10;i++)
	{
		line(x+38,y+5*i,x+54,y+5*i);
	}
}

/*
    函数功能：大图标模式下c源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IcL(int x,int y)
{
	int i;

	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	rectangle(x,y,x+49,y+79);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x+10,y+47,x+57,y+74);
	setcolor(DRM_BLACK);
	rectangle(x+10,y+48,x+57,y+75);
	setcolor(DRM_WHITE);
	arc(x+42,y+60,60,300,7);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	bar(x+29,y+67,x+33,y+69);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	for(i=2;i<9;i++)
	{
		line(x+5,y+5*i,x+44,y+5*i);
	}
}

/*
    函数功能：大图标模式下h源码文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IhL(int x,int y)
{
	int i;
	
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	rectangle(x,y,x+49,y+79);
	setfillstyle(SOLID_FILL,DRM_RED);
	bar(x+10,y+47,x+57,y+74);
	setcolor(DRM_DARKGRAY);
	rectangle(x+10,y+48,x+57,y+75);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	bar(x+27,y+67,x+31,y+69);
	setcolor(DRM_WHITE);
	line(x+35,y+53,x+35,y+69);
	line(x+43,y+53,x+43,y+69);
	line(x+35,y+61,x+43,y+61);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	for(i=2;i<9;i++)
	{
		line(x+5,y+5*i,x+44,y+5*i);
	}
}

/*
    函数功能：大图标模式下目标文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IobjL(int x,int y)
{
	IgeneralL(x,y);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_BLACK);
	moveto(x+24,y+70);
	lineto(x+39,y+59);
	lineto(x+39,y+39);
	lineto(x+24,y+50);
	lineto(x+24,y+70);
	lineto(x+9,y+59);
	lineto(x+9,y+39);
	lineto(x+24,y+28);
	lineto(x+39,y+39);
	line(x+9,y+39,x+20,y+47);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
}

/*
    函数功能：大图标模式下未知文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void ImysteryL(int x,int y){IgeneralL(x,y);}

/*
    函数功能：大图标模式下图形文件图标
    输入参数：(x,y)——图形左上角位置
    输出参数：无
    返回值：无
*/
void IpicL(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_BRIGHTBLUE);
	bar(x-10,y+9,x+60,y+66);
	setfillstyle(SOLID_FILL,DRM_LIGHTGREEN);
	bar(x-10,y+35,x+60,y+49);
    setfillstyle(SOLID_FILL,DRM_LIGHTBLUE);
	bar(x-10,y+49,x+60,y+66);
	setcolor(DRM_ORANGE);
	setfillstyle(SOLID_FILL,DRM_ORANGE);
	fillellipse(x+44,y+23,7,7);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_DARKGRAY);
	rectangle(x-10,y+9,x+60,y+66);
	setcolor(DRM_LIGHTGREEN);
	line(x+1,y+35,x+12,y+20);
	line(x+12,y+20,x+23,y+35);
	setfillstyle(SOLID_FILL,DRM_LIGHTGREEN);
	floodfill(x+12,y+30,DRM_LIGHTGREEN);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
}
