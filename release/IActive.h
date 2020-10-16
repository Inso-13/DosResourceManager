/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：Active类函数处于中间层，用于将后端函数的接口统一化，供前端调用栈使用
 **************************************************
 */

#ifndef __IACTIVE_H
#define __IACTIVE_H

//库文件
#include<BIOS.H>
#include<DOS.H>
#include<GRAPHICS.H>

//辅助模块
#include"IQuit.h"
#include"IUtility.h"
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"
#include"IDefs.h"

//调用模块
#include"IDiry.h"
#include"IInput.h"
#include"IBar.h"


//函数原型
void ISelect(IFileNode *node,IFileNode *null);
void ICtrlSelect(IFileNode *node,IFileNode *null);
void INOP(IFileNode *null1,IFileNode *null2);
void IGoLeftActive(IFileNode *cur,IFileNode *null);
void IGoRightActive(IFileNode *cur,IFileNode *null);
void IexeActive(IFileNode *exe,IFileNode *null);
void ItxtActive(IFileNode *txt,IFileNode *null);
void ISearchActive(IFileNode *cur,IFileNode *null);
void ILastPage(IFileNode *pag,IFileNode *null);
void INextPage(IFileNode *pag,IFileNode *null);
void ISetXNull(IFileNode *node,IFileNode *X);
void ISetView10(IFileNode *flag,IFileNode *null);
void ISetView11(IFileNode *flag,IFileNode *null);

#endif