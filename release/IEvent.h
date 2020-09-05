/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：与事件相关的函数
*/


#ifndef __IEVENT_H
#define __IEVENT_H

#include"IType.h"

IEventStackNode * IInitEventStack(void);
void IEventStackPush(IEventStackNode * top,IEvent newEvent);
IBool IEventStackPop(IEventStackNode * top,int n);
char IEventStackActive(IEventStackNode * top,int x,int y,int type);
void IDelStack(IEventStackNode * top);

#endif