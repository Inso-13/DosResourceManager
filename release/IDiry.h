/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵����Diry��DirBaseΪ�������ṩ�˻������Ա�ǰ��ֱ��ʹ�õ��ļ���������
*/


#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root);
void IDetree(IFileNode * root);
void Icplr(IFileNode * oldParent,IFileNode * newParent);
void Irmlr(IFileNode * oldParent);
void Irename(IFileNode * oldName,char * newName);
IBool Inew(IFileNode * pathNode,char* fileName);
IBool Imkdir(IFileNode * pathNode,char* folderName);
void ISearch(char* path,char* name,FILE* fp);

#endif