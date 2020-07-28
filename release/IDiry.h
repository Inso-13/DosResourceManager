#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root);//将root目录下的文件加到文件树上
void IDetree(IFileNode * root); //将root目录下的文件从文件树上删除
void Icplr(IFileNode * oldParent,IFileNode * newParent);//复制oldParent目录下所有被选中的文件
void Irmlr(IFileNode * oldParent,IFileNode * rootR);//删除oldParent目录下所有被选中的文件
IBool Irename(IFileNode * oldName,char * newName);//重命名oldName文件，并更新节点
IBool Inew(IFileNode * pathNode,char* fileName); //创建新文件，并添加到文件树
void Imkdir(IFileNode * pathNode,char* folderName);    //创建文件夹，并更新节点
void ISort(IFileNode* parent,int (*fun)(IFileNode*,IFileNode*));
int ISortDateUp(IFileNode* node1,IFileNode* node2);
int ISortDateDown(IFileNode* node1,IFileNode* node2);
int ISortSizeUp(IFileNode* node1,IFileNode* node2);
int ISortSizeDown(IFileNode* node1,IFileNode* node2);
int ISortNameUp(IFileNode* node1,IFileNode* node2);
int ISortNameDown(IFileNode* node1,IFileNode* node2);
int ISortTypeUp(IFileNode* node1,IFileNode* node2);
int ISortTypeDown(IFileNode* node1,IFileNode* node2);
void ISearch(IFileNode * parent,char* name); //按文件名在当前文件夹查找文件

#endif