/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：DiryBase作为Diry库的底层支撑，封装了许多常用的文件操作函数
 **************************************************
 */

#ifndef __IDIRBASE_H
#define __IDIRBASE_H

//库文件
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<GRAPHICS.H>

//辅助模块
#include"IUtility.h"
#include"INode.h"
#include"IType.h"


//函数原型
int Icopy(IFileNode * inFile,IFileNode * outParent,char flag);
int Irmf(IFileNode * fileNode);
int Imkdir(IFileNode * pathNode,char *folderName);
int Irmdir(IFileNode * node);
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild);
void IDelAll(IFileNode * oldChildChild);
void Icpr(IFileNode * oldChild,IFileNode * newParent,char flag);
void Irmr(IFileNode * oldChild);
void IEntree(IFileNode * root,char flag);
void IDetree(IFileNode * root);
int ISearchPath(char *name);

#endif