/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：与文件节点操作相关的部分函数，比较底层
 **************************************************
 */

#ifndef __INODE_H
#define __INODE_H

//库文件
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<STDIO.H>

//辅助模块
#include"IUtility.h"
#include"IQuit.h"
#include"IType.h"


//函数原型
int IAddChild(IFileNode * parent,IFileNode * child);
int IAddFileNode(IFileNode  *parent,char* name);
int IDelFileNode(IFileNode  *parent,char* name);
void IDelFilelist(IFileNode * root);
void IAddFilelist(IFileNode * root);
IFileNode * IGetFileNodeList(char * path);
int IPeek(IFileNode * oldParent,char* path);
void Icd(char * path);

#endif