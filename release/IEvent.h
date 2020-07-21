#ifndef __IEVENT_H
#define __IEVENT_H

#include"IType.h"

IEventStackNode * IInitEventStack(void);    //返回一个新的事件栈（栈顶）
void IEventStackPush(IEventStackNode * top,IEvent newEvent);    //入栈，top自动改变
IBool IEventStackPop(IEventStackNode * top,int n);      //出栈n个事件，top自动改变
char IEventStackActive(IEventStackNode * top,int x,int y,int type,int key);   //根据事件激活槽函数
void IDelStack(IEventStackNode * top);      //析构栈

#endif