/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：主要定义排序函数
 **************************************************
 */

#ifndef __ISORT_H
#define __ISORT_H

//库文件
#include<STRING.H>

//辅助模块
#include"IUtility.h"
#include"IType.h"


//函数原型
void ISort(IFileNode *parent,int (*fun)(IFileNode*,IFileNode*));
int ISortDateUp(IFileNode *node1,IFileNode *node2);
int ISortDateDown(IFileNode *node1,IFileNode *node2);
int ISortSizeUp(IFileNode *node1,IFileNode *node2);
int ISortSizeDown(IFileNode *node1,IFileNode *node2);
int ISortNameUp(IFileNode *node1,IFileNode *node2);
int ISortNameDown(IFileNode *node1,IFileNode *node2);
int ISortTypeUp(IFileNode *node1,IFileNode *node2);
int ISortTypeDown(IFileNode *node1,IFileNode *node2);
void ISortMenuActive(IFileNode *flag,IFileNode *null);
void ISortActive(IFileNode *parent,IFileNode *pfun);
void IExchangeFileNode(IFileNode *node1,IFileNode *node2);

#endif