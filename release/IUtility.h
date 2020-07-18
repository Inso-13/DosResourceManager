#ifndef __IUTILITY_H
#define __IUTILITY_H

#include"IType.h"

void IFileNodeSetNull(IFileNode * node);    //初始化文件节点
IFileNode * IFindParent(IFileNode * child);     //返回文件节点的父节点
IFileNode * IDiskInit(void);    //初始化文件根节点
IBool IGetPath(IFileNode * node,char* temp);    //返回文件节点目录的路径，不包括文件名
IBool IMatch(char* src,char* pattern);      //通配符匹配
void Icd(char *); //更换磁盘并进入目录
IBool IisFolder(IFileNode * node);  //是否为目录
IFileNode * IFindNodeByPath(char * path,IFileNode * root);  //根据路径得到文件节点
IFileNode * IFindNodeByName(char * name,IFileNode * root);  //根据文件名得到文件节点

#endif