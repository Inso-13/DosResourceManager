/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵�����������ļ�ͼ���С����ͼ��
 **************************************************
*/

#include"IDraw.h"

/*
    �������ܣ��ļ�δ��ʱ��ָʾ��ͷ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IPointerRight(int x,int y)
{
    setcolor(DRM_BLACK);
    line(x,y,x+2,y+2);
    line(x+1,y,x+3,y+2);
    line(x,y+4,x+1,y+3);
    line(x+1,y+4,x+2,y+3);
}

/*
    �������ܣ��ļ���ʱ��ָʾ��ͷ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IPointerDown(int x,int y)
{
    setcolor(DRM_BLACK);
    line(x,y,x+2,y+2);
    line(x,y+1,x+2,y+3);
    line(x+4,y,x+3,y+1);
    line(x+4,y+1,x+3,y+2);
}

/*
    �������ܣ����ͷ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IGoLeft(int x,int y)
{
    line(x+4,y,x,y+4);
    line(x+5,y,x+1,y+4);
    line(x+4,y+10,x,y+6);
    line(x+5,y+10,x+1,y+6);
    line(x,y+4,x+10,y+4);
    line(x,y+5,x+10,y+5);
    line(x,y+6,x+10,y+6);
}

/*
    �������ܣ��Ҽ�ͷ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IGoRight(int x,int y)
{
    line(x+6,y,x+10,y+4);
    line(x+5,y,x+9,y+4);
    line(x+6,y+10,x+10,y+6);
    line(x+5,y+10,x+9,y+6);
    line(x,y+4,x+10,y+4);
    line(x,y+5,x+10,y+5);
    line(x,y+6,x+10,y+6);
}

/*
    �������ܣ��ϼ�ͷ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IGoUp(int x,int y)
{
    line(x+4,y+2,x,y+6);
    line(x+4,y+3,x,y+7);
    line(x+6,y+2,x+10,y+6);
    line(x+6,y+3,x+10,y+7);
    line(x+4,y+2,x+4,y+14);
    line(x+5,y+2,x+5,y+14);
    line(x+6,y+2,x+6,y+14);
}

/*
    �������ܣ�ˢ��ͼ��
    ���������centerX����ͼ�ε����ĺ�����, centerY����ͼ�ε�����������
    �����������
    ����ֵ����
*/
void IRefresh(int centerX,int centerY)
{
    setcolor(DRM_BLACK);
    arc(centerX,centerY,0,45,3);
    arc(centerX,centerY,110,180,3);
    arc(centerX,centerY+1,180,360,3);
    line(centerX-2,centerY-3,centerX-3,centerY-3);
    putpixel(centerX-1,centerY-1,DRM_BLACK);
}

/*
    �������ܣ��Ŵ�ͼ��
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IMagnifier(int x,int y)
{
    setcolor(DRM_BLACK);
    circle(x+2,y+2,2);
    circle(x+2,y+2,3);
    line(x,y+4,x-2,y+6);
    line(x,y+5,x-2,y+7);
}

/*
    �������ܣ��˳�ͼ��
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IExit(int x,int y)
{
    setcolor(DRM_WHITE);
    line(x,y,x+4,y+4);
    line(x,y+1,x+4,y+5);
    line(x,y+4,x+4,y);
    line(x,y+5,x+4,y+1);
}

/*
    �������ܣ���ϸ��ͼ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IDetailOption(int x,int y)
{
    setcolor(DRM_BLACK);
    line(x,y,x+11,y);
    line(x,y+1,x+11,y+1);
    line(x,y+4,x+11,y+4);
    line(x,y+6,x+11,y+6);
    line(x,y+8,x+11,y+8);
    line(x,y+10,x+11,y+10);
    line(x,y+11,x+11,y+11);
    putpixel(x+1,y+3,DRM_BLUE);
    putpixel(x+1,y+6,DRM_DARKBLUE);
    putpixel(x+1,y+9,DRM_ORANGE);
}

/*
    �������ܣ���ͼ����ͼ
    ���������x����ͼ�ε����ϽǺ�����, y����ͼ�ε����Ͻ�������
    �����������
    ����ֵ����
*/
void IPictureOption(int x,int y)
{
    setcolor(DRM_BLACK);
    rectangle(x,y,x+11,y+11);
    setcolor(DRM_BLUE);
    line(x+1,y+1,x+10,y+1);
    setfillstyle(SOLID_FILL,DRM_GREEN);
    bar(x+1,y+5,x+10,y+10);
}