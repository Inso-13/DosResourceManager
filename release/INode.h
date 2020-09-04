#ifndef __INODE_H
#define __INODE_H

#include"IType.h"

IBool IAddChild(IFileNode * parent,IFileNode * child); //����ӽڵ�
IBool IAddFileNode(IFileNode  *parent,char* name);   //��parent�ļ��������name�ļ��ڵ�
IBool IDelFileNode(IFileNode  *parent,char* name); //��parent�ļ�����ɾ��name�ļ��ڵ�
void IDelFilelist(IFileNode * root);    //�ݹ�ɾ����������
void IAddFilelist(IFileNode * root);    //�ݹ����������
IFileNode * IGetFileNodeList(char * path);  //�õ�·���µ������ļ������������ʽ����
void IPeek(IFileNode * oldParent,char* path);  //�����ļ����е��ļ��������ļ�����
void IExchangeFileNode(IFileNode* node1,IFileNode* node2); //����ʱ����

#endif