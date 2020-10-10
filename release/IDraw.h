/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵�����������ļ�ͼ���С����ͼ��
 **************************************************
*/

#ifndef __IDRAW_H
#define __IDRAW_H

//���ļ�
#include<GRAPHICS.H>

//����ģ��
#include"IDefs.h"


//����ԭ��
void IPointerRight(int x,int y);
void IPointerDown(int x,int y);
void IGoLeft(int x,int y);
void IGoRight(int x,int y);
void IGoUp(int x,int y);
void IRefresh(int centerX,int centerY);
void IMagnifier(int x,int y);
void IExit(int x,int y);
void IDetailOption(int x,int y);
void IPictureOption(int x,int y);

#endif