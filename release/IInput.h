/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-7
 *   说明：输入函数
 **************************************************
 */

#ifndef __IINPUT_H
#define __IINPUT_H

//库文件
#include<STDIO.H>
#include<GRAPHICS.H>
#include<STRING.H>
#include<CONIO.H>

//辅助模块
#include"IDefs.h"

//调用模块
#include"IType.h"
#include"IBar.h"


//函数原型
char *IGetString(int x,int y,int length,char *string,int flag);

#endif