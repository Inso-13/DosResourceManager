#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainLogin(void);  //登录界面的不变的图形
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ); //登录界面的不断变化的图形
void IPlainView(FILE* fpHZ);   //界面的不变的图形
int IView0(IFileNode* root,IFileNodePointer** curNode,IEventStackNode* top,int beginX,int beginY,char *page,char flag);
int IView1(IFileNodePointer** curNode,IEventStackNode* top,char isCtrl,char *page,char* delFlag,FILE* fpHZ);

#endif