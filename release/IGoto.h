#ifndef __IGOTO_H
#define __IGOTO_H

//���ļ�
#include<STDIO.H>

//����ģ��
#include"IType.h"
#include"IDefs.h"

//����ģ��
#include"IDirAct.h"
#include"IUtility.h"


//����ԭ��
char IGoto(char *path,IFileNodePointer **curNode);
void IGotoFrom(IFileNode *path,IFileNode *cur);

#endif