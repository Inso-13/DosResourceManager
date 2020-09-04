/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：Active类函数处于中间层，用于将后端（如Diry等）函数的接口统一化，供前端调用栈使用
*/


#ifndef __IACTIVE_H
#define __IACTIVE_H

#include"IType.h"

void IEntreeActive(IFileNode* node,IFileNode* cur);
void IDetreeActive(IFileNode* node,IFileNode* cur);
void ISelect(IFileNode* node,IFileNode* null);
void ICtrlSelect(IFileNode* node,IFileNode* null);
void INOP(IFileNode* null1,IFileNode* null2);
void IGoLeftActive(IFileNode* cur,IFileNode* null);
void IGoRightActive(IFileNode* cur,IFileNode* null);
char* IGetString(int x,int y,int length,char* string,int flag);
void IexeActive(IFileNode* exe,IFileNode* null);
void ItxtActive(IFileNode* txt,IFileNode* null);
void ISortMenuActive(IFileNode* flag,IFileNode* null);
void ISortActive(IFileNode* parent,IFileNode* pfun);
void ISearchActive(IFileNode* cur,IFileNode* null);
void IGetName(IFileNode* nam,IFileNode* null);
void IGetPassword(IFileNode* pass,IFileNode* null);
void ILastPage(IFileNode *pag,IFileNode* null);
void INextPage(IFileNode *pag,IFileNode* null);

#endif