/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：主要定义了异常退出函数
*/


#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IQuit.h"

void IQuit()
{
    closegraph();   //关闭图形界面
    fcloseall();    //关闭所有文件
    exit(0);    //退出
}