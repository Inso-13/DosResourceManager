#ifndef __IUTILITY_H
#define __IUTILITY_H

#include"IType.h"

void IFileNodeSetNull(IFileNode * node);    //初始化文件节点
IFileNode * IFindParent(IFileNode * child);     //返回文件节点的父节点
IFileNode * IDiskInit(int id);    //初始化文件根节点
void IGetAbsolutePath(IFileNode * node,char* temp);
IBool IMatch(char* src,char* pattern);      //通配符匹配
int IMatchi(char a,char b);
void Icd(char *); //更换磁盘并进入目录
IBool IisFolder(IFileNode * node);  //是否为目录
IFileNode * IFindNodeByPath(char * path,IFileNode * root);  //根据路径得到文件节点
IFileNode * IFindNodeByName(char * name,IFileNode * root);  //根据文件名得到文件节点
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change);
void IDelPointer(IFileNodePointer* pointer);

#endif