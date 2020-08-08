#ifndef __IMENU_H
#define __IMENU_H

#include"IType.h"

void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX,int *menuFlag,char *delFlag,FILE* fpHZ);
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,int menuFlag,FILE* fpHZ);
void ISetCopy(IFileNode* cur,IFileNode* nodeX);
void ISetDelete(IFileNode* cur,IFileNode* null);
void ISetPaste(IFileNode* cur,IFileNode* X);
void ISetCut(IFileNode* cur,IFileNode* X);
void ISetRename(IFileNode* cur,IFileNode* null);
void ISetNewFile(IFileNode* cur,IFileNode* null);
void ISetNewFolder(IFileNode* cur,IFileNode* null);
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null);

#endif