#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPointerRight(int x,int y);
void IPointerDown(int x,int y);
void IGoLeft(int x,int y);
void IGoRight(int x,int y);
void IGoUp(int x,int y);
void IRefresh(int centerX,int centerY);
void IMagnifier(int x,int y);
void IDetailOption(int x,int y);
void IPictureOption(int x,int y);
void IExit(int x,int y);
void IPlainView(void);
int IView0(IFileNode* root,IFileNode** curNode,IEventStackNode* top,int beginX,int beginY);
void IView1(IFileNode** curNode,IEventStackNode* top);
void IEntreeActive(IFileNode* node,IFileNode* cur);
void IDetreeActive(IFileNode* node,IFileNode* cur);

#endif