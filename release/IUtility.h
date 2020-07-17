#ifndef __IUTILITY_H
#define __IUTILITY_H

#include"IType.h"

int Istrcmp(char *s,char *t);
void IFileNodeSetNull(IFileNode far* node);
IFileNode far* IFindParent(IFileNode far* child);
IFileNode far* IDiskInit(void);
IBool IGetPath(IFileNode far* node,char* temp);
IBool IMatch(char* src,char* pattern);
IBool IAddFileNode(IFileNode far *parent,char* name);
void Icd(char far*); // setdisk & cd
IBool IisFolder(IFileNode far* node);
IFileNode far* IFindNodeByPath(char far* path,IFileNode far* root);
IFileNode far* IFindNodeByName(char far* name,IFileNode far* root);

#endif