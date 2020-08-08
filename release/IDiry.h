#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root);//将root??录下的文件加到文件树??
void IDetree(IFileNode * root); //将root??录下的文件从文件树上删除
void Icplr(IFileNode * oldParent,IFileNode * newParent);//复制oldParent??录下所有???选中的文??
void Irmlr(IFileNode * oldParent,IFileNode * rootR);//删除oldParent??录下所有???选中的文??
IBool Irename(IFileNode * oldName,char * newName);//重命名oldName文件，并更新节点
IBool Inew(IFileNode * pathNode,char* fileName); //创建新文件，并添加到文件??
IBool Imkdir(IFileNode * pathNode,char* folderName);    //创建文件夹，并更新节??
void ISearch(IFileNode * parent,char* name); //按文件名在当前文件夹查找文件

#endif