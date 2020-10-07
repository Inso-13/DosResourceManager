/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：与菜单相关的部分函数
 **************************************************
 */

#ifndef __IMENU_H
#define __IMENU_H

//库文件
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<BIOS.H>
#include<CONIO.H>
#include<GRAPHICS.H>

//辅助模块
#include"IUtility.h"
#include"ISound.h"
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"

//调用模块
#include"IDiry.h"
#include"ISort.h"
#include"IInput.h"

//函数原型
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX,char *menuFlag,FILE* fpHZ);
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,char menuFlag,FILE* fpHZ);
void ISetCopy(IFileNode* cur,IFileNode* nodeX);
void ISetDelete(IFileNode* cur,IFileNode* null);
void ISetPaste(IFileNode* cur,IFileNode* X);
void ISetCut(IFileNode* cur,IFileNode* X);
void ISetRename(IFileNode* cur,IFileNode* null);
void ISetNewFile(IFileNode* cur,IFileNode* null);
void ISetNewFolder(IFileNode* cur,IFileNode* null);
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null);
void ISetPasteF(IFileNode* cur,IFileNode* X);
void ISetPasteComfirm(IFileNode* flagx,IFileNode* null);
void ISetPasteCheck(IFileNode* cur,IFileNode* X);

#endif