/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：Diry以DirBase为基础，提供了基本可以被前端直接使用的文件操作函数
*/


#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root,char flag);
void IDetree(IFileNode * root);
void Icplr(IFileNode * oldParent,IFileNode * newParent);
void Irmlr(IFileNode * oldParent);
void Irename(IFileNode * oldName,char * newName);
int Inew(IFileNode * pathNode,char* fileName);
int Imkdir(IFileNode * pathNode,char* folderName);
void ISearch(char* path,char* name,FILE* fp);

#endif