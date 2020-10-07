/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-24
 *   ˵�������ļ�/�ļ����ڴ�ͼ��ģʽ���������ʾͼ����صĺ���
 **************************************************
 */

#include"IIconL.h"

/*
    �������ܣ���ͼ��ģʽ�´���ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IdiskL(int x,int y)
{
   int i;
   int v[]={-10,51,20,65,20,79,-10,65,-10,51};
   setlinestyle(0,0,3);
   setcolor(247);
   for(i=0;i<5;i++)
   {
		v[2*i]=x+v[2*i];
		v[2*i+1]=y+v[2*i+1];
   }
   drawpoly(5,v);
   moveto(x-10,y+51);
   lineto(x+30,y+31);
   lineto(x+60,y+45);
   lineto(x+60,y+59);
   lineto(x+20,y+79);
   moveto(x+20,y+65);
   lineto(x+60,y+45);
   setfillstyle(1,248);
   floodfill(x+5,y+65,247);
   setlinestyle(0,0,1);
   setcolor(140);
   setfillstyle(1,140);
   fillellipse(x+15,y+70,2,2);
}

/*
    �������ܣ���ͼ��ģʽ��ͨ��ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/

void IgeneralL(int x,int y)
{
	setlinestyle(0,0,3);
	setcolor(247);
	line(x,y,x+34,y);
	line(x+34,y,x+34,y+14);
	line(x+34,y+14,x+49,y+14);
	line(x+34,y,x+49,y+14);
	line(x+49,y+14,x+49,y+79);
	line(x+49,y+79,x,y+79);	
	line(x,y+79,x,y);
	setlinestyle(0,0,1); 
}
/*
    �������ܣ���ͼ��ģʽ���ı��ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void ItxtL(int x,int y)
{
	int i;
	IgeneralL(x,y);
	setcolor(248);
	setlinestyle(0,0,1);
	for(i=2;i<=5;i++)
	{
		line(x+5,y+3*i,x+29,y+3*i);
	}
	for(i=6;i<=24;i++)
	{
		line(x+5,y+3*i,x+44,y+3*i);
	}
}

/*
    �������ܣ���ͼ��ģʽ��word�ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/

void IdocL(int x,int y)
{
	int i; 
	IgeneralL(x,y);
	setfillstyle(1,11);
	bar(x-10,y+12,x+30,y+48);
	setcolor(255);
	setlinestyle(0,0,3);
	line(x-8,y+16,x,y+42);
	line(x,y+42,x+8,y+16);
	line(x+8,y+16,x+16,y+42);
	line(x+16,y+42,x+24,y+16);
	setlinestyle(0,0,1); 
	setcolor(247);
	for(i=14;i<=18;i++)
	{
		line(x+5,y+4*i,x+43,y+4*i);
	}
}
/*
    �������ܣ���ͼ��ģʽ���ļ���ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/

void IfolderL(int x,int y)
{
	setfillstyle(1,202);
	bar(x,y,x+43,y+64);
	setcolor(207);
	rectangle(x,y,x+43,y+64);
	setcolor(202);
	line(x,y+64,x+16,y+64);
	setcolor(207);
	line(x,y,x+16,y+16);
	line(x+16,y+16,x+16,y+80);
	line(x+16,y+80,x,y+64);
	line(x,y+64,x,y);
	setcolor(206);
	floodfill(x+5,y+53,207);	
	floodfill(x+11,y+69,207);	
}
/*
    �������ܣ���ͼ��ģʽ�¿�ִ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/

void IexeL(int x,int y)
{
	int i;
	setfillstyle(1,247);
	bar(x-10,y+14,x+60,y+66);
	setcolor(248);
	setlinestyle(0,0,3);
	rectangle(x-10,y+14,x+60,y+66);
	setfillstyle(1,248);
	bar(x-11,y+9,x+61,y+14);
	setfillstyle(1,255);
	bar(x+5,y+17,x+57,y+63);
	setfillstyle(1,11);
	bar(x+7,y+19,x+35,y+55);
	setcolor(248);
	line(x-5,y+20,x+2,y+20);
	line(x-5,y+27,x+2,y+27);
	line(x-5,y+34,x+2,y+34);
	line(x-5,y+41,x+2,y+41);
	setcolor(247);
	setlinestyle(0,0,1);
	for(i=4;i<10;i++)
	{
		line(x+38,y+5*i,x+54,y+5*i);
	}
}

/*
    �������ܣ���ͼ��ģʽ��cԴ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IcL(int x,int y)
{
	int i;
	setlinestyle(0,0,3);
	setcolor(247);
	rectangle(x,y,x+49,y+79);
	setfillstyle(1,11);
	bar(x+10,y+47,x+57,y+74);
	setcolor(0);
	rectangle(x+10,y+48,x+57,y+75);
	setcolor(255);
	arc(x+42,y+60,60,300,7);
	setfillstyle(1,255);
	bar(x+29,y+67,x+33,y+69);
	setlinestyle(0,0,1);
	setcolor(247);
	for(i=2;i<9;i++)
	{
		line(x+5,y+5*i,x+44,y+5*i);
	}
}


/*
    �������ܣ���ͼ��ģʽ��hԴ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/

void IhL(int x,int y)
{
	int i;
	setlinestyle(0,0,3);
	setcolor(247);
	rectangle(x,y,x+49,y+79);
	setfillstyle(1,180);
	bar(x+10,y+47,x+57,y+74);
	setcolor(248);
	rectangle(x+10,y+48,x+57,y+75);
	setfillstyle(1,255);
	bar(x+27,y+67,x+31,y+69);
	setcolor(255);
	line(x+35,y+53,x+35,y+69);
	line(x+43,y+53,x+43,y+69);
	line(x+35,y+61,x+43,y+61);
	setlinestyle(0,0,1);
	setcolor(247);
	for(i=2;i<9;i++)
	{
		line(x+5,y+5*i,x+44,y+5*i);
	}
}

/*
    �������ܣ���ͼ��ģʽ��Ŀ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IobjL(int x,int y)
{
	IgeneralL(x,y);
	setlinestyle(0,0,3);
	setcolor(0);
	moveto(x+24,y+70);
	lineto(x+39,y+59);
	lineto(x+39,y+39);
	lineto(x+24,y+50);
	lineto(x+24,y+70);
	lineto(x+9,y+59);
	lineto(x+9,y+39);
	lineto(x+24,y+28);
	lineto(x+39,y+39);
	line(x+9,y+39,x+20,y+47);
	setlinestyle(0,0,1);
}

/*
    �������ܣ���ͼ��ģʽ��δ֪�ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void ImysteryL(int x,int y){IgeneralL(x,y);}

/*
    �������ܣ���ͼ��ģʽ��ͼ���ļ�ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IpicL(int x,int y)
{
	setfillstyle(1,31);
	bar(x-10,y+9,x+60,y+66);
	setfillstyle(SOLID_FILL,6);
	bar(x-10,y+35,x+60,y+49);
    setfillstyle(SOLID_FILL,23);
	bar(x-10,y+49,x+60,y+66);
	setcolor(202);
	setfillstyle(SOLID_FILL,202);
	fillellipse(x+44,y+23,7,7);
	setlinestyle(0,0,3);
	setcolor(248);
	rectangle(x-10,y+9,x+60,y+66);
	setcolor(6);
	line(x+1,y+35,x+12,y+20);
	line(x+12,y+20,x+23,y+35);
	setfillstyle(1,6);
	floodfill(x+12,y+30,6);
	setlinestyle(0,0,1);
}
