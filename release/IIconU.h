/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-10-26
 *   ˵�����븴�ơ�ճ�������С��������Ȳ����йص�ͼ�� 
 **************************************************
 */
 
#ifndef __IICONU_H
#define __IICONU_H

//���ļ�
#include<GRAPHICS.H>

//����ģ��
#include"IDefs.h"

//����ԭ��
void IGrayCopyU(int x,int y)
void IBlueCopyU(int x,int y);
void IGrayPasteU(int x,int y);
void IBrownPasteU(int x,int y);
void IBasicDeleteU(int x,int y);
void IGrayDeleteU(int x,int y);
void IRedDeleteU(int x,int y);
void IGrayClipU(int x,int y);
void IBlueClipU(int x,int y);
void IGrayRenameU(int x,int y);
void IBlueRenameU(int x,int y);
void INewFolderU(int x,int y);
void IAllSelectU(int x,int y);
void INonSelectU(int x,int y);
void INagSelectU(int x,int y);

#endif
