/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵����Active�ຯ�������м�㣬���ڽ���˺����Ľӿ�ͳһ������ǰ�˵���ջʹ��
 **************************************************
 */

#ifndef __IACTIVE_H
#define __IACTIVE_H

//���ļ�
#include<BIOS.H>
#include<DOS.H>
#include<GRAPHICS.H>

//����ģ��
#include"IQuit.h"
#include"IUtility.h"
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"
#include"IDefs.h"
#include"ISound.h"

//����ģ��
#include"IDiry.h"
#include"IInput.h"
#include"IBar.h"
#include"IGoto.h"


//����ԭ��
void ISelect(IFileNode *node,IFileNode *null);
void ICtrlSelect(IFileNode *node,IFileNode *null);
void INOP(IFileNode *null1,IFileNode *null2);
void IGoLeftActive(IFileNode *cur,IFileNode *null);
void IGoRightActive(IFileNode *cur,IFileNode *null);
void IexeActive(IFileNode *exe,IFileNode *null);
void ItxtActive(IFileNode *txt,IFileNode *null);
void ISearchActive(IFileNode *cur,IFileNode *null);
void ILastPage(IFileNode *pag,IFileNode *null);
void INextPage(IFileNode *pag,IFileNode *null);
void ISetXNull(IFileNode *node,IFileNode *X);
void ISetView10(IFileNode *flag,IFileNode *null);
void ISetView11(IFileNode *flag,IFileNode *null);
void IGotoActive(IFileNode *cur,IFileNode *null);

#endif