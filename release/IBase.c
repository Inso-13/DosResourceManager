#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IBase.h"

void IQuit()
{
    closegraph();   //关闭图形界面
    fcloseall();    //关闭所有文件
    exit(0);    //退出
}