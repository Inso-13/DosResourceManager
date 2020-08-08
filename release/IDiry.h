#ifndef __IDIRECTORY_H
#define __IDIRECTORY_H

#include"IType.h"

void IEntree(IFileNode * root);//��root??¼�µ��ļ��ӵ��ļ���??
void IDetree(IFileNode * root); //��root??¼�µ��ļ����ļ�����ɾ��
void Icplr(IFileNode * oldParent,IFileNode * newParent);//����oldParent??¼������???ѡ�е���??
void Irmlr(IFileNode * oldParent,IFileNode * rootR);//ɾ��oldParent??¼������???ѡ�е���??
IBool Irename(IFileNode * oldName,char * newName);//������oldName�ļ��������½ڵ�
IBool Inew(IFileNode * pathNode,char* fileName); //�������ļ�������ӵ��ļ�??
IBool Imkdir(IFileNode * pathNode,char* folderName);    //�����ļ��У������½�??
void ISearch(IFileNode * parent,char* name); //���ļ����ڵ�ǰ�ļ��в����ļ�

#endif