/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������ͼ����02��
 **************************************************
 */

#ifndef __IVIEW02_H
#define __IVIEW02_H

//���ļ�
#include<GRAPHICS.H>
#include<CONIO.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>

//����ģ��
#include"IHanZi.h"
#include"IType.h"
#include"ISound.h"
#include"IEvent.h"

//����ģ��
#include"IActive.h"
#include"IDirAct.h"

//ͼ�ο�
#include"IIcon.h"
#include"IIconL.h"
#include"IDraw.h"


//����ԭ��
void IPlainView(FILE *fpHZ);
int IView0(IFileNode *root,IFileNodePointer** curNode,IFileNodePointer *nodeX,\
IEventStackNode *top,int beginX,int beginY,char *page,char flag,FILE *fpHZ);
void IView2(char *page,FILE *fpHZ,IEventStackNode *top,IFileNodePointer** curNode);

#endif