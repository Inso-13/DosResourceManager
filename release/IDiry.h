#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root);//将root目录下的文件加到文件树上
void IDetree(IFileNode * root); //将root目录下的文件从文件树上删除
IFileNode * ISearch(IFileNode * node,IFileNode * name);//按文件名查找文件，耗内存，请慎用
void Icplr(IFileNode * oldParent,IFileNode * newParent);//复制oldParent目录下所有被选中的文件
void Irmlr(IFileNode * oldParent,IFileNode * rootR);//删除oldParent目录下所有被选中的文件
IBool Irename(IFileNode * oldName,IFileNode * newName);//重命名oldName文件，并更新节点
IBool Inew(IFileNode * pathNode,IFileNode * fileName); //创建新文件，并添加到文件树
void Imkdir(IFileNode * pathNode,IFileNode * folderName);    //创建文件夹，并更新节点

#endif