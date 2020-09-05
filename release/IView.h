/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：登录界面、视图函数等
*/


#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainLogin(void);
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ);
void IPlainView(FILE* fpHZ);
int IView0(IFileNode* root,IFileNodePointer** curNode,IEventStackNode* top,int beginX,int beginY,char *page,char flag);
int IView1(IFileNodePointer** curNode,IEventStackNode* top,char *page,char* menuFlag,FILE* fpHZ);
void IView1DrawIcon(IFileNode* tempNode,int y);
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem);
void IView2(char* page,FILE* fpHZ);

#endif