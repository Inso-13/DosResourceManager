#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainLogin(void);  //��¼����Ĳ����ͼ��
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ); //��¼����Ĳ��ϱ仯��ͼ��
void IPlainView(FILE* fpHZ);   //����Ĳ����ͼ��
int IView0(IFileNode* root,IFileNodePointer** curNode,IEventStackNode* top,int beginX,int beginY,char *page,char flag);
int IView1(IFileNodePointer** curNode,IEventStackNode* top,char isCtrl,char *page,char* delFlag,FILE* fpHZ);

#endif