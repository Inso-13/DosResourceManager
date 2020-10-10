/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������¼����
 **************************************************
 */

#ifndef __ILOGIN_H
#define __ILOGIN_H

//���ļ�
#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>

//����ģ��
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"

//����ģ��
#include"ISecret.h"
#include"IInput.h"

//����ԭ��
void IPlainLogin(void);
void ILogin(char *name,char *password,IEventStackNode* top,int id,FILE* fpHZ);
void ILoginConfirm(int* id,char *name,char *password);
void IGetName(IFileNode *nam,IFileNode *null);
void IGetPassword(IFileNode *pass,IFileNode *null);

#endif