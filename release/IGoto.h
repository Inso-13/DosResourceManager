#ifndef __IGOTO_H
#define __IGOTO_H

//库文件
#include<STDIO.H>

//辅助模块
#include"IType.h"
#include"IDefs.h"

//调用模块
#include"IDirAct.h"
#include"IUtility.h"


//函数原型
char IGoto(char *path,IFileNodePointer **curNode);
void IGotoFrom(IFileNode *path,IFileNode *cur);

#endif