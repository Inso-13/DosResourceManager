/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：主要定义了一些常用的函数
 **************************************************
 */

#ifndef __IUTILITY_H
#define __IUTILITY_H

//库文件
#include<STRING.H>

//辅助模块
#include"IType.h"
#include"IDefs.h"


//函数原型
int IisFolder(IFileNode * node);
int IisChild(char *path1,char *path2);
IFileNode * IFindParent(IFileNode * child);
IFileNode * IFindNodeByPath(char * path,IFileNode * root);
IFileNode * IFindNodeByName(char * name,IFileNode * root); 
void IGetNameByPath(char *path,char *name);
void IGetAbsolutePath(IFileNode * node,char *temp);
void IFileNodeSetNull(IFileNode * node);
char IStartWith(char *str,char *pattern);
char IEndWith(char *str,char *pattern);

#endif