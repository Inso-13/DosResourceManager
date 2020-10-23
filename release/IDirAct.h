/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：将Diry函数的接口统一化，供前端调用栈使用
 **************************************************
 */

#ifndef __IDIRACTIVE_H
#define __IDIRACTIVE_H

//库文件
#include<STDLIB.H>

//辅助模块
#include"IType.h"
#include"IDefs.h"

//调用模块
#include"IDiry.h"

//函数原型
void IDetreeActive(IFileNode *node,IFileNode *cur);
void IEntreeActive(IFileNode *node,IFileNode *cur);
void IAfterEntree(IFileNode *cur,IFileNode *X);
void IGotoFrom(IFileNode *path,IFileNode *cur);

#endif