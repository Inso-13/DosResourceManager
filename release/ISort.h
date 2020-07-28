#ifndef __ISORT_H
#define __ISORT_H

#include"IType.h"

void ISort(IFileNode* parent,int (*fun)(IFileNode*,IFileNode*));
int ISortDateUp(IFileNode* node1,IFileNode* node2);
int ISortDateDown(IFileNode* node1,IFileNode* node2);
int ISortSizeUp(IFileNode* node1,IFileNode* node2);
int ISortSizeDown(IFileNode* node1,IFileNode* node2);
int ISortNameUp(IFileNode* node1,IFileNode* node2);
int ISortNameDown(IFileNode* node1,IFileNode* node2);
int ISortTypeUp(IFileNode* node1,IFileNode* node2);
int ISortTypeDown(IFileNode* node1,IFileNode* node2);

#endif