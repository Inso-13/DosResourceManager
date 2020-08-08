#ifndef __IUTILITY_H
#define __IUTILITY_H

#include"IType.h"

void IFileNodeSetNull(IFileNode * node);    //��ʼ���ļ��ڵ�
IFileNode * IFindParent(IFileNode * child);     //�����ļ��ڵ�ĸ��ڵ�
IFileNode * IDiskInit(int id);    //��ʼ���ļ����ڵ�
void IGetAbsolutePath(IFileNode * node,char* temp);
IBool IMatch(char* src,char* pattern);      //ͨ���ƥ��
int IMatchi(char a,char b);
void Icd(char *); //�������̲�����Ŀ¼
IBool IisFolder(IFileNode * node);  //�Ƿ�ΪĿ¼
IFileNode * IFindNodeByPath(char * path,IFileNode * root);  //����·���õ��ļ��ڵ�
IFileNode * IFindNodeByName(char * name,IFileNode * root);  //�����ļ����õ��ļ��ڵ�
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change);
void IDelPointer(IFileNodePointer* pointer);

#endif