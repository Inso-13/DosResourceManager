/*
    �汾�ţ�1.0
    ���ߣ���һ��
    �������ڣ�2020-9-4
    ˵������Ҫ������һЩ���õĺ���
*/


#ifndef __IUTILITY_H
#define __IUTILITY_H

#include"IType.h"

void IFileNodeSetNull(IFileNode * node);
IFileNode * IFindParent(IFileNode * child);
IFileNode * IDiskInit(int id);
void IGetAbsolutePath(IFileNode * node,char* temp);
int IMatch(char* src,char* pattern);
int IMatchi(char a,char b);
void Icd(char *);
int IisFolder(IFileNode * node);
IFileNode * IFindNodeByPath(char * path,IFileNode * root);
IFileNode * IFindNodeByName(char * name,IFileNode * root); 
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change);
void IDelPointer(IFileNodePointer* pointer);
void IGetNameByPath(char* path,char* name);
int IisChild(char* path1,char* path2);
int ISearchPath(char* name);

#endif