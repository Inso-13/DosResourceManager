/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：登录界面
*/


#ifndef __ILOGIN_H
#define __ILOGIN_H

#include"IType.h"

void IPlainLogin(void);
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ);
void ILoginConfirm(int* id,char* name,char* password);

#endif