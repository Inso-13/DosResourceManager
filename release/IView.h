#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainLogin(void);
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ);
void IPlainView(FILE* fpHZ);
int IView0(IFileNode* root,IFileNodePointer * curNode,IEventStackNode* top,int beginX,int beginY);
int IView1(IFileNodePointer ** curNode,IEventStackNode* top,char isCtrl,char *page,char* delFlag,FILE* fpHZ);

#endif