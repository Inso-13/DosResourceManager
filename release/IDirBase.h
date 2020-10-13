/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵����DiryBase��ΪDiry��ĵײ�֧�ţ���װ����ೣ�õ��ļ���������
 **************************************************
 */

#ifndef __IDIRBASE_H
#define __IDIRBASE_H

//���ļ�
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include<GRAPHICS.H>

//����ģ��
#include"IUtility.h"
#include"INode.h"
#include"IType.h"
#include"IDefs.h"


//����ԭ��
int Icopy(IFileNode *inFile,IFileNode *outParent,char flag);
int Irmf(IFileNode *fileNode);
int Imkdir(IFileNode *pathNode,char *folderName);
int Irmdir(IFileNode *node);
int ISearchPath(char *name);
void ICopyAll(IFileNode *oldChildChild,IFileNode *newChild);
void IDelAll(IFileNode *oldChildChild);
void Icpr(IFileNode *oldChild,IFileNode *newParent,char flag);
void Irmr(IFileNode *oldChild);
void IEntree(IFileNode *root,char flag);
void IDetree(IFileNode *root);

#endif