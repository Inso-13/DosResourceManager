#ifndef __IDIRBASE_H
#define __IDIRBASE_H

#include"IType.h"

IBool Icopy(IFileNode * inFile,IFileNode * outParent);  //将inFile文件复制到outParent文件夹内
IBool Irmf(IFileNode * fileNode);   //彻底删除文件
void Imkdir(IFileNode * pathNode,IFileNode * folderName);//创建文件夹，并更新节点
IBool Irmdir(IFileNode * node); //删除所有空文件夹，并更新节点
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild);//复制链表
void IDelAll(IFileNode * oldChildChild); //删除链表
void Icpr(IFileNode * oldChild,IFileNode * newParent);//递归复制所有文件和文件夹
void Irmr(IFileNode * oldChild);//递归删除所有文件和文件夹

#endif