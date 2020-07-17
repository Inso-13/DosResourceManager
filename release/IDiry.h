#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IDetree(IFileNode far* root); // delete the filetree
IFileNode far* ISearch(IFileNode far* node,IFileNode far* name);
void Icplr(IFileNode far* oldParent,IFileNode far* newParent);
void Irmlr(IFileNode far* oldParent,IFileNode far* rootR);
IBool Irename(IFileNode far* oldName,IFileNode far* newName);

#endif