/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵����DiryBase��ΪDiry��ĵײ�֧�ţ���װ����ೣ�õ��ļ���������
*/


#ifndef __IDIRBASE_H
#define __IDIRBASE_H

#include"IType.h"

int Icopy(IFileNode * inFile,IFileNode * outParent);
int Irmf(IFileNode * fileNode);
int Imkdir(IFileNode * pathNode,char* folderName);
int Irmdir(IFileNode * node);
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild);
void IDelAll(IFileNode * oldChildChild);
void Icpr(IFileNode * oldChild,IFileNode * newParent);
void Irmr(IFileNode * oldChild);
void IEntree(IFileNode * root,char flag);
void IDetree(IFileNode * root);

#endif