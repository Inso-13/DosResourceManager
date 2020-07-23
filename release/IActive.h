#ifndef __IACTIVE_H
#define __IACTIVE_H

#include"IType.h"

void IEntreeActive(IFileNode* node,IFileNode* cur);
void IDetreeActive(IFileNode* node,IFileNode* cur);
void ISelect(IFileNode* node,IFileNode* null);
void ICtrlSelect(IFileNode* node,IFileNode* null);
void INOP(IFileNode* null1,IFileNode* null2);
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX);
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX);
void ISetCopy(IFileNode* cur,IFileNode* nodeX);
void ISetDelete(IFileNode* cur,IFileNode* null);
void ISetPaste(IFileNode* cur,IFileNode* X);
void ISetCut(IFileNode* cur,IFileNode* X);
void IGoLeftActive(IFileNode* cur,IFileNode* null);
void IGoRightActive(IFileNode* cur,IFileNode* null);

#endif