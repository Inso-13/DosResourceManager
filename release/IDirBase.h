#ifndef __IDIRBASE_H
#define __IDIRBASE_H

#include"IType.h"

IBool Icopy(IFileNode far* inFile,IFileNode far* outParent);
IBool Irmf(IFileNode far* fileNode);
IBool Inew(IFileNode far* pathNode,IFileNode far* fileName);
void Imkdir(IFileNode far* pathNode,IFileNode far* folderName);
void Imvdir(IFileNode far* oldChild,IFileNode far* newParent);
IBool Irmdir(IFileNode far* node);
void ICopyAll(IFileNode far* oldChildChild,IFileNode far* newChild);
void IDelAll(IFileNode far* oldChildChild);
void Icpr(IFileNode far* oldChild,IFileNode far* newParent);
void Irmr(IFileNode far* oldChild);

#endif