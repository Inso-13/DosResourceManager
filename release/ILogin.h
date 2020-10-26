/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：登录界面
 **************************************************
 */

#ifndef __ILOGIN_H
#define __ILOGIN_H

//库文件
#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>

//辅助模块
#include"IHanZi.h"
#include"IType.h"
#include"IEvent.h"
#include"IUtility.h"

//调用模块
#include"ISecret.h"
#include"IInput.h"


//函数原型
void IPlainLogin(FILE *fpHZ);
void ILogin(char *name,char *password,IEventStackNode *top,char id,FILE *fpHZ);
void ILoginConfirm(char *id,char *name,char *password);
void IGetName(IFileNode *nam,IFileNode *null);
void IGetPassword(IFileNode *pass,IFileNode *null);

#endif