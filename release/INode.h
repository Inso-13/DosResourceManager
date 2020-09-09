/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵�������ļ��ڵ������صĲ��ֺ������Ƚϵײ�
*/


#ifndef __INODE_H
#define __INODE_H

#include"IType.h"

IBool IAddChild(IFileNode * parent,IFileNode * child);
IBool IAddFileNode(IFileNode  *parent,char* name);
IBool IDelFileNode(IFileNode  *parent,char* name);
void IDelFilelist(IFileNode * root);
void IAddFilelist(IFileNode * root);
IFileNode * IGetFileNodeList(char * path);
int IPeek(IFileNode * oldParent,char* path);
void IExchangeFileNode(IFileNode* node1,IFileNode* node2);

#endif