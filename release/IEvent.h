#ifndef __IEVENT_H
#define __IEVENT_H

#include"IType.h"

IEventStackNode * IInitEventStack(void);    //����һ���µ��¼�ջ��ջ����
void IEventStackPush(IEventStackNode * top,IEvent newEvent);    //��ջ��top�Զ��ı�
IBool IEventStackPop(IEventStackNode * top,int n);      //��ջn���¼���top�Զ��ı�
char IEventStackActive(IEventStackNode * top,int x,int y,int type);   //�����¼�����ۺ���
void IDelStack(IEventStackNode * top);      //����ջ

#endif