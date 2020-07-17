#ifndef __IEVENT_H
#define __IEVENT_H

#include"IType.h"

IEventStackNode far* IInitEventStack(void);
void IEventStackPush(IEventStackNode far* top,IEvent newEvent);
IBool IEventStackPop(IEventStackNode far* top,int n);// n for poped
IBool IEventStackActive(IEventStackNode far* top,int x,int y,int type);// 1 for active
void IDelStack(IEventStackNode far* top);

#endif