/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：主要定义了异常退出函数
 **************************************************
 */

#ifndef __IQUIT_H
#define __IQUIT_H

//库文件
#include<STDIO.H>
#include<STDLIB.H>
#include<GRAPHICS.H>

//辅助模块
#include"IType.h"


//函数原型
void IQuit(void);   //异常退出函数
void IDelPointer(IFileNodePointer* pointer);

#endif