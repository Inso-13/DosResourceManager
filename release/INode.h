#ifndef __INODE_H
#define __INODE_H

#include"IType.h"

IBool IAddChild(IFileNode far* parent,IFileNode far* child);// 1 for added
IBool IAddSibling(IFileNode far* pre,IFileNode far* next);// 1 for added
IBool IDelFileNode(IFileNode far *parent,char* name);
void IDelFilelist(IFileNode far* root);
void IAddFilelist(IFileNode far* root);
IFileNode far* IGetFileNodeList(char far* path);// enlarge the filetree
void IPeek(IFileNode far* oldParent);

#endif