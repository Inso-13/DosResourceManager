/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：与事件相关的函数
 **************************************************
 */


#ifndef __IEVENT_H
#define __IEVENT_H

//库文件
#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>

//辅助模块
#include"IQuit.h"
#include"IType.h"


//函数原型
IEventStackNode * IInitEventStack(void);
void IEventStackPush(IEventStackNode * top,IEvent newEvent);
int IEventStackPop(IEventStackNode * top,int n);
char IEventStackActive(IEventStackNode * top,int x,int y,int type);
void IDelStack(IEventStackNode * top);
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change);

#endif