#ifndef __INODE_H
#define __INODE_H

#include"IType.h"

IBool IAddChild(IFileNode * parent,IFileNode * child);//添加子节点
IBool IAddFileNode(IFileNode  *parent,char* name);  //在parent文件夹中添加name文件节点
IBool IDelFileNode(IFileNode  *parent,char* name);//在parent文件夹中删除name文件节点
void IDelFilelist(IFileNode * root);    //递归删除整个链表
void IAddFilelist(IFileNode * root);    //递归添加整个树
IFileNode * IGetFileNodeList(char * path);  //得到路径下的所有文件，以链表的形式返回
void IPeek(IFileNode * oldParent,char* path);  //查找文件夹中的文件数和子文件夹数
void IExchangeFileNode(IFileNode* node1,IFileNode* node2);

#endif