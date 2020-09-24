/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：视图函数等
*/


#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainView(FILE* fpHZ);
int IView0(IFileNode* root,IFileNodePointer** curNode,IFileNodePointer* nodeX,IEventStackNode* top,int beginX,int beginY,char *page,char flag,FILE* fpHZ);
int IView1(IFileNodePointer** curNode,IFileNodePointer* nodeX,IEventStackNode* top,char *page,char* menuFlag,FILE* fpHZ);
void IView10DrawIcon(IFileNode* tempNode,int y);
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem);
void IView2(char* page,FILE* fpHZ,IEventStackNode* top,IFileNodePointer** curNode);
void IView10(IFileNodePointer ** curNode,IFileNodePointer* nodeX,IFileNode* tempNode,FILE* fpHZ,IEventStackNode* top,char* menuFlag);
void IView11(IFileNodePointer ** curNode,IFileNodePointer* nodeX,IFileNode* tempNode,FILE* fpHZ,IEventStackNode* top,char* menuFlag);
void IView11DrawIcon(IFileNode* tempNode,int x,int y);

#endif