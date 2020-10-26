/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-10-26
 *   说明：与复制、粘贴、剪切、重命名等操作有关的图标 
 **************************************************
 */
 
#ifndef __IICONU_H
#define __IICONU_H

//库文件
#include<GRAPHICS.H>

//辅助模块
#include"IDefs.h"

//函数原型
void IGrayCopyU(int x,int y)
void IBlueCopyU(int x,int y);
void IGrayPasteU(int x,int y);
void IBrownPasteU(int x,int y);
void IBasicDeleteU(int x,int y);
void IGrayDeleteU(int x,int y);
void IRedDeleteU(int x,int y);
void IGrayClipU(int x,int y);
void IBlueClipU(int x,int y);
void IGrayRenameU(int x,int y);
void IBlueRenameU(int x,int y);
void INewFolderU(int x,int y);
void IAllSelectU(int x,int y);
void INonSelectU(int x,int y);
void INagSelectU(int x,int y);

#endif
