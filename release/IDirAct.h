/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������Diry�����Ľӿ�ͳһ������ǰ�˵���ջʹ��
 **************************************************
 */

#ifndef __IDIRACTIVE_H
#define __IDIRACTIVE_H

//���ļ�
#include<STDLIB.H>

//����ģ��
#include"IType.h"
#include"IDefs.h"

//����ģ��
#include"IDiry.h"

//����ԭ��
void IDetreeActive(IFileNode *node,IFileNode *cur);
void IEntreeActive(IFileNode *node,IFileNode *cur);
void IAfterEntree(IFileNode *cur,IFileNode *X);

#endif