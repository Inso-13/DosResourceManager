/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-7
 *   说明：磁盘初始化函数
 **************************************************
 */

#ifndef __IDISK_H
#define __IDISK_H

//库文件
#include<STDLIB.H>
#include<STRING.H>
#include<DIR.H>

//辅助模块
#include"IDefs.h"
#include"IType.h"
#include"IUtility.h"


//函数原型
IFileNode * IDiskInit(int id);

#endif