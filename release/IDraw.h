/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：不包括文件图标的小部件图形
 **************************************************
*/

#ifndef __IDRAW_H
#define __IDRAW_H

//库文件
#include<GRAPHICS.H>

//辅助模块
#include"IDefs.h"


//函数原型
void IPointerRight(int x,int y);
void IPointerDown(int x,int y);
void IGoLeft(int x,int y);
void IGoRight(int x,int y);
void IGoUp(int x,int y);
void IRefresh(int centerX,int centerY);
void IMagnifier(int x,int y);
void IExit(int x,int y);
void IDetailOption(int x,int y);
void IPictureOption(int x,int y);

#endif