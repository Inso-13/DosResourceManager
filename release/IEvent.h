/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵�������¼���صĺ���
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