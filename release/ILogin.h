/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������¼����
*/


#ifndef __ILOGIN_H
#define __ILOGIN_H

#include"IType.h"

void IPlainLogin(void);
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ);
void ILoginConfirm(int* id,char* name,char* password);

#endif