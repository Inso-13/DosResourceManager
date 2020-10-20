/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵�������¼���صĺ���
 **************************************************
 */


#ifndef __IEVENT_H
#define __IEVENT_H

//���ļ�
#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>

//����ģ��
#include"IQuit.h"
#include"IType.h"


//����ԭ��
IEventStackNode *IInitEventStack(void);
void IEventStackPush(IEventStackNode *top,IEvent newEvent);
int IEventStackPop(IEventStackNode *top,int n);
char IEventStackActive(IEventStackNode *top,int x,int y,int type);
void IDelStack(IEventStackNode *top);
void ISetEvent(IEvent *event,int x1,int y1,int x2,int y2,int type,\
void (*pfun)(IFileNode *,IFileNode *),IFileNode *node0,IFileNode *node1,char change);

#endif