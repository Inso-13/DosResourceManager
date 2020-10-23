/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������˵���صĲ��ֺ���
 **************************************************
 */

#ifndef __IMENU_H
#define __IMENU_H

//���ļ�
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<DIR.H>
#include<BIOS.H>
#include<CONIO.H>
#include<GRAPHICS.H>

//����ģ��
#include"IUtility.h"
#include"ISound.h"
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"

//����ģ��
#include"IDiry.h"
#include"ISort.h"
#include"IInput.h"

//����ԭ��
void IMenu(int mouseX,int mouseY,IEventStackNode *top,IFileNodePointer *curNode,IFileNodePointer *nodeX,char *menuFlag,FILE *fpHZ);
void IDrawMenu(int x,int y,IFileNodePointer *curNode,IFileNodePointer *nodeX,char menuFlag,FILE *fpHZ);
void ISetCopy(IFileNode *cur,IFileNode *nodeX);
void ISetDelete(IFileNode *cur,IFileNode *null);
void ISetPaste(IFileNode *cur,IFileNode *X);
void ISetPasteF(IFileNode *cur,IFileNode *X);
void ISetCut(IFileNode *cur,IFileNode *X);
void ISetRename(IFileNode *cur,IFileNode *null);
void ISetNewFile(IFileNode *cur,IFileNode *null);
void ISetNewFolder(IFileNode *cur,IFileNode *null);
void ISetDeleteComfirm(IFileNode *flagx,IFileNode *null);
void ISetPasteComfirm(IFileNode *flagx,IFileNode *null);
void ISetPasteCheck(IFileNode *cur,IFileNode *X);

#endif