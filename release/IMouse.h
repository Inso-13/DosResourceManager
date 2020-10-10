/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵�����������صĲ��ֺ���
 **************************************************
 */

#ifndef __IMOUSE_H
#define __IMOUSE_H

//���ļ�
#include<STDLIB.H>
#include<GRAPHICS.H>
#include<DOS.H>
#include<CONIO.H>

//����ģ��
#include"IDefs.h"


//����ԭ��
void IMouseMath(int (*mouseDraw)[16]);
void IMouseOn(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);
void IMouseOff(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);
void IMouseSetLimit(int xMax,int yMax);
void IMouseGetXY(int*,int*);
int IMouseLeftRelease(void);
int ILeftPress(void);
int IRightPress(void);
int IMouseStatus(int*,int*,int (*mouseDraw)[16],int (*pixelSave)[16]);

#endif