/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-10-4
 *   ˵��������·������ָ��λ�õĺ���
 **************************************************
 */

#ifndef __IGOTO_H
#define __IGOTO_H

//���ļ�
#include<STDIO.H>

//����ģ��
#include"IType.h"
#include"IDefs.h"

//����ģ��
#include"IDirAct.h"
#include"IUtility.h"


//����ԭ��
char IGoto(char *path,IFileNodePointer **curNode);
void IGotoFrom(IFileNode *path,IFileNode *cur);

#endif