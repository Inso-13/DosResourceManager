/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ����������
 **************************************************
 */

#ifndef __ISORT_H
#define __ISORT_H

//���ļ�
#include<STRING.H>

//����ģ��
#include"IUtility.h"
#include"IType.h"


//����ԭ��
void ISort(IFileNode *parent,int(*fun)(IFileNode*,IFileNode*));
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