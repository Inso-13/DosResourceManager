#ifndef __IVIEW_H
#define __IVIEW_H

#include"IType.h"

void IPlainView(void);
int IView0(IFileNode* root,IFileNodePointer * curNode,IEventStackNode* top,int beginX,int beginY);
int IView1(IFileNodePointer ** curNode,IEventStackNode* top,char isCtrl,char *page);

#endif