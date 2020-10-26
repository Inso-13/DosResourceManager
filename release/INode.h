/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵�������ļ��ڵ������صĲ��ֺ������Ƚϵײ�
 **************************************************
 */

#ifndef __INODE_H
#define __INODE_H

//���ļ�
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<STDIO.H>

//����ģ��
#include"IUtility.h"
#include"IQuit.h"
#include"IType.h"
#include"IDefs.h"

//����ԭ��
int IAddChild(IFileNode *parent,IFileNode *child);
int IAddFileNode(IFileNode  *parent,char *name);
int IDelFileNode(IFileNode  *parent,char *name);
void IDelFilelist(IFileNode *root);
void IAddFilelist(IFileNode *root);
IFileNode *IGetFileNodeList(char *path);
int IPeek(IFileNode *oldParent,char *path);
void Icd(char *path);

#endif