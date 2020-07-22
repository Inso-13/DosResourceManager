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
int IView1(IFileNode** curNode,IEventStackNode* top,char isCtrl);
void IEntreeActive(IFileNode* node,IFileNode* cur);
void IDetreeActive(IFileNode* node,IFileNode* cur);
void ISelect(IFileNode* node,IFileNode* null);
void ICtrlSelect(IFileNode* node,IFileNode* null);
void INOP(IFileNode* null1,IFileNode* null2);
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNode** curNode,IFileNode** nodeX);
void IDrawMenu(int x,int y,int numOfSelected,IFileNode** nodeX);
void ISetCopy(IFileNode* cur,IFileNode* nodeX);
void ISetDelete(IFileNode* cur,IFileNode* null);
void ISetPaste(IFileNode* cur,IFileNode* X);
void ISetCut(IFileNode* cur,IFileNode* X);

#endif