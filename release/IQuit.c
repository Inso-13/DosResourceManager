/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������Ҫ�������쳣�˳�����
*/


#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IQuit.h"

void IQuit()
{
    closegraph();   //�ر�ͼ�ν���
    fcloseall();    //�ر������ļ�
    exit(0);    //�˳�
}