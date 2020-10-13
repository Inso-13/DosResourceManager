/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：Diry以DirBase为基础，提供了基本可以被前端直接使用的文件操作函数
 **************************************************
 */


#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

//库文件
#include<STRING.H>
#include<STDLIB.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<DOS.H>
#include<IO.H>
#include<STDIO.H>

//辅助模块
#include"IType.h"
#include"IUtility.h"
#include"IDefs.h"

//调用模块
#include"INode.h"
#include"IDirBase.h"
#include"IMatch.h"


//函数原型
void Icplr(IFileNode * oldParent,IFileNode * newParent,char flag);
void Irmlr(IFileNode * oldParent);
void Irename(IFileNode * oldName,char * newName);
int Inew(IFileNode * pathNode,char *fileName);
void ISearch(char *path,char *name,FILE* fp);
void IDelFilelist(IFileNode * root);

#endif