/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������ͼ����1��
 **************************************************
 */

#ifndef __IVIEW1_H
#define __IVIEW1_H

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
#include"IMenu.h"
#include"IDirAct.h"

//ͼ�ο�
#include"IIcon.h"
#include"IIconL.h"
#include"IDraw.h"


//����ԭ��
void IView1(IFileNodePointer** curNode,IFileNodePointer *nodeX,IEventStackNode *top,\
char *page,char *menuFlag,FILE *fpHZ);
void IView10DrawIcon(IFileNode *tempNode,int y);
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem);
void IView10(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,\
FILE *fpHZ,IEventStackNode *top,char *menuFlag);
void IView11(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,\
FILE *fpHZ,IEventStackNode *top,char *menuFlag);
void IView11DrawIcon(IFileNode *tempNode,int x,int y);
void IView1DelOrCover(int numOfSelected,IFileNodePointer **curNode,\
IFileNodePointer *nodeX,IEventStackNode *top,char *menuFlag,FILE *fpHZ);

#endif