/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������ͼ������
*/


#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainView(FILE* fpHZ);
int IView0(IFileNode* root,IFileNodePointer** curNode,IEventStackNode* top,int beginX,int beginY,char *page,char flag);
int IView1(IFileNodePointer** curNode,IEventStackNode* top,char *page,char* menuFlag,FILE* fpHZ);
void IView1DrawIcon(IFileNode* tempNode,int y);
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem);
void IView2(char* page,FILE* fpHZ);

#endif