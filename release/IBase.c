#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IBase.h"

void IQuit()
{
    closegraph();   //�ر�ͼ�ν���
    fcloseall();    //�ر������ļ�
    exit(0);    //�˳�
}