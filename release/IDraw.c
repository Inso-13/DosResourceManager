/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：不包括文件图标的小部件图形
 **************************************************
*/

#include"IDraw.h"

/*
    函数功能：文件未打开时的指示箭头
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IPointerRight(int x,int y)
{
    setcolor(0);
    line(x,y,x+2,y+2);
    line(x+1,y,x+3,y+2);
    line(x,y+4,x+1,y+3);
    line(x+1,y+4,x+2,y+3);
}

/*
    函数功能：文件打开时的指示箭头
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IPointerDown(int x,int y)
{
    setcolor(0);
    line(x,y,x+2,y+2);
    line(x,y+1,x+2,y+3);
    line(x+4,y,x+3,y+1);
    line(x+4,y+1,x+3,y+2);
}

/*
    函数功能：左箭头
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IGoLeft(int x,int y)
{
    line(x+4,y,x,y+4);
    line(x+5,y,x+1,y+4);
    line(x+4,y+10,x,y+6);
    line(x+5,y+10,x+1,y+6);
    line(x,y+4,x+10,y+4);
    line(x,y+5,x+10,y+5);
    line(x,y+6,x+10,y+6);
}

/*
    函数功能：右箭头
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IGoRight(int x,int y)
{
    line(x+6,y,x+10,y+4);
    line(x+5,y,x+9,y+4);
    line(x+6,y+10,x+10,y+6);
    line(x+5,y+10,x+9,y+6);
    line(x,y+4,x+10,y+4);
    line(x,y+5,x+10,y+5);
    line(x,y+6,x+10,y+6);
}

/*
    函数功能：上箭头
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IGoUp(int x,int y)
{
    line(x+4,y+2,x,y+6);
    line(x+4,y+3,x,y+7);
    line(x+6,y+2,x+10,y+6);
    line(x+6,y+3,x+10,y+7);
    line(x+4,y+2,x+4,y+14);
    line(x+5,y+2,x+5,y+14);
    line(x+6,y+2,x+6,y+14);
}

/*
    函数功能：刷新图案
    输入参数：centerX——图形的中心横坐标, centerY——图形的中心纵坐标
    输出参数：无
    返回值：无
*/
void IRefresh(int centerX,int centerY)
{
    setcolor(0);
    arc(centerX,centerY,0,45,3);
    arc(centerX,centerY,110,180,3);
    arc(centerX,centerY+1,180,360,3);
    line(centerX-2,centerY-3,centerX-3,centerY-3);
    putpixel(centerX-1,centerY-1,0);
}

/*
    函数功能：放大镜图案
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IMagnifier(int x,int y)
{
    setcolor(0);
    circle(x+2,y+2,2);
    circle(x+2,y+2,3);
    line(x,y+4,x-2,y+6);
    line(x,y+5,x-2,y+7);
}

/*
    函数功能：退出图案
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IExit(int x,int y)
{
    setcolor(255);
    line(x,y,x+4,y+4);
    line(x,y+1,x+4,y+5);
    line(x,y+4,x+4,y);
    line(x,y+5,x+4,y+1);
}

/*
    函数功能：详细视图
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IDetailOption(int x,int y)
{
    setcolor(0);
    line(x,y,x+11,y);
    line(x,y+1,x+11,y+1);
    line(x,y+4,x+11,y+4);
    line(x,y+6,x+11,y+6);
    line(x,y+8,x+11,y+8);
    line(x,y+10,x+11,y+10);
    line(x,y+11,x+11,y+11);
    putpixel(x+1,y+3,15);
    putpixel(x+1,y+6,14);
    putpixel(x+1,y+9,144);
}

/*
    函数功能：大图标视图
    输入参数：x——图形的左上角横坐标, y——图形的左上角纵坐标
    输出参数：无
    返回值：无
*/
void IPictureOption(int x,int y)
{
    setcolor(0);
    rectangle(x,y,x+11,y+11);
    setcolor(15);
    line(x+1,y+1,x+10,y+1);

    setfillstyle(SOLID_FILL,GREEN);
    bar(x+1,y+5,x+10,y+10);
}