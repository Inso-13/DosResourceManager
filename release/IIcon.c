/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵�������ļ�/�ļ���ͼ����صĺ���
 **************************************************
 */

#include"IIcon.h"

/*
    �������ܣ�����ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Idisk(int x,int y)
{
   int i;
   int v[]={0,7,6,10,6,13,0,10,0,7};

   setcolor(DRM_LIGHTGRAY);
   for(i=0;i<5;i++)
   {
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
   }
   drawpoly(5,v);
   moveto(x,y+7);
   lineto(x+8,y+3);
   lineto(x+14,y+6);
   lineto(x+14,y+9);
   lineto(x+6,y+13);
   moveto(x+6,y+10);
   lineto(x+14,y+6);
   setfillstyle(INTERLEAVE_FILL,DRM_DARKGRAY);
   floodfill(x+3,y+10,DRM_LIGHTGRAY);
   putpixel(x+5,y+11,DRM_LIGHTGREEN);
}

/*
    �������ܣ�ͨ��ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Igeneral(int x,int y)
{
	setcolor(DRM_LIGHTGRAY);
	line(x,y,x+7,y);
	line(x+7,y,x+7,y+3);
	line(x+10,y+3,x+10,y+14);
	line(x+10,y+14,x,y+14);
	line(x,y+14,x,y);	
	line(x+7,y,x+10,y+3);
}

/*
    �������ܣ��ı��ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Itxt(int x,int y)
{
	int i;

	Igeneral(x,y);
	for(i=1;i<3;i++)
	{
		line(x+2,y+2*i,x+5,y+2*i);
	}
	for(i=3;i<7;i++)
	{
		line(x+2,y+2*i,x+8,y+2*i);
	}
}

/*
    �������ܣ�wordͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Idoc(int x,int y)
{
	Igeneral(x,y);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x-3,y+3,x+6,y+12);
	setcolor(DRM_WHITE);
	line(x-2,y+4,x,y+8);
	line(x,y+8,x+2,y+4);
	line(x+2,y+4,x+4,y+8);
	line(x+4,y+8,x+6,y+4);
}

/*
    �������ܣ��ļ���ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Ifolder(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_ORANGE);
	bar(x,y,x+8,y+11);
	setcolor(DRM_YELLOW);
	line(x,y,x+3,y+3);
	line(x+3,y+3,x+3,y+15);
	line(x+3,y+15,x,y+12);
	line(x,y+12,x,y);
	floodfill(x+1,y+10,DRM_YELLOW);	
	floodfill(x+2,y+13,DRM_YELLOW);	
}

/*
    �������ܣ���ִ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Iexe(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x+4,y+4,x+9,y+11);
	setcolor(DRM_DARKGRAY);
	rectangle(x,y+2,x+15,y+13);
	setfillstyle(SOLID_FILL,DRM_DARKGRAY);
	bar(x,y+2,x+15,y);
	setcolor(DRM_DARKGRAY);
	line(x+11,y+5,x+13,y+5);
	line(x+11,y+7,x+13,y+7);
	line(x+11,y+9,x+13,y+9);
}

/*
    �������ܣ�cԴ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Ic(int x,int y)
{
	setcolor(DRM_LIGHTGRAY);
	rectangle(x,y,x+11,y+12);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x+2,y+8,x+13,y+14);
	setcolor(DRM_WHITE);
	arc(x+9,y+11,60,300,2);
}

/*
    �������ܣ�hԴ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Ih(int x,int y)
{
	setcolor(DRM_LIGHTGRAY);
	rectangle(x,y,x+11,y+12);
	setfillstyle(SOLID_FILL,DRM_RED);
	bar(x+2,y+8,x+13,y+14);
	setcolor(DRM_WHITE);
	line(x+6,y+9,x+6,y+13);
	line(x+8,y+11,x+8,y+13);
	arc(x+7,y+11,0,180,1);
}

/*
    �������ܣ�Ŀ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Iobj(int x,int y)
{
	int i=0;
	int v[]={0,0,7,0,7,3,10,3,10,14,0,14,0,0};
	
	setcolor(DRM_LIGHTGRAY);
	for(i=0;i<7;i++)
	{
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
	}
	drawpoly(7,v);
	moveto(x+7,y);
	lineto(x+10,y+3);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	bar3d(x+3,y+11,x+6,y+7,2,1);
}

/*
    �������ܣ�δ֪�ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Imystery(int x,int y){Igeneral(x,y);}

/*
    �������ܣ�ͼ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void Ipic(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_LIGHTBLUE);
	bar(x,y,x+14,y+7);
    setfillstyle(SOLID_FILL,DRM_DARKBLUE);
	bar(x,y+8,x+14,y+14);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	bar(x+10,y+2,x+12,y+4);
	setcolor(DRM_DARKBLUE);
	line(x+1,y+8,x+8,y+8);
	line(x+2,y+7,x+7,y+7);
	line(x+3,y+6,x+6,y+6);
	line(x+4,y+5,x+5,y+4);
}