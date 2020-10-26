/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ������һЩ���õĺ���
 **************************************************
 */

#ifndef __IUTILITY_H
#define __IUTILITY_H

//���ļ�
#include<STRING.H>
#include<STDIO.H>

//����ģ��
#include"IType.h"
#include"IDefs.h"


//����ԭ��
int IisFolder(IFileNode *node);
int IisChild(char *path1,char *path2);
IFileNode *IFindParent(IFileNode *child);
IFileNode *IFindNodeByPath(char *path,IFileNode *root);
IFileNode *IFindNodeByName(char *name,IFileNode *root); 
void IGetNameByPath(char *path,char *name);
void IGetAbsolutePath(IFileNode *node,char *temp);
void IFileNodeSetNull(IFileNode *node);
char IStartWith(char *str,char *pattern);
char IEndWith(char *str,char *pattern);
char ICheckNull(void* ptr);

#endif