/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵����Diry��DirBaseΪ�������ṩ�˻������Ա�ǰ��ֱ��ʹ�õ��ļ���������
 **************************************************
 */


#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

//���ļ�
#include<STRING.H>
#include<STDLIB.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<DOS.H>
#include<IO.H>
#include<STDIO.H>

//����ģ��
#include"IType.h"
#include"IUtility.h"
#include"IDefs.h"

//����ģ��
#include"INode.h"
#include"IDirBase.h"
#include"IMatch.h"


//����ԭ��
void Icplr(IFileNode *oldParent,IFileNode *newParent,char flag);
void Irmlr(IFileNode *oldParent);
void Irename(IFileNode *oldName,char *newName);
int Inew(IFileNode *pathNode,char *fileName);
void ISearch(char *path,char *name,FILE *fp);
void IDelFilelist(IFileNode *root);

#endif