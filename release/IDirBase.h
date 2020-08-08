#ifndef __IDIRBASE_H
#define __IDIRBASE_H

#include"IType.h"

IBool Icopy(IFileNode * inFile,IFileNode * outParent);  //��inFile�ļ����Ƶ�outParent�ļ�����
IBool Irmf(IFileNode * fileNode);   //����ɾ���ļ�
IBool Imkdir(IFileNode * pathNode,char* folderName);//�����ļ��У������½�??
IBool Irmdir(IFileNode * node,int flag); //ɾ�����п��ļ��У������½�??
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild);//��������
void IDelAll(IFileNode * oldChildChild); //ɾ������
void Icpr(IFileNode * oldChild,IFileNode * newParent);//�ݹ鸴�������ļ����ļ�??
void Irmr(IFileNode * oldChild);//�ݹ�ɾ�������ļ����ļ�??
void IEntree(IFileNode * root);//��root??¼�µ��ļ��ӵ��ļ���??

#endif