/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-5
    ˵������¼����
*/


#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IActive.h"
#include"IUtility.h"
#include"IHanZi.h"

/*
    �������ܣ�����¼����ı���
    �����������
    �����������
    ����ֵ����
*/
void IPlainLogin()
{
    int i;
    
    setfillstyle(SOLID_FILL,248);
    bar(0,0,1024,768);
    setcolor(255);
    for(i=0;i<10;i++)
    {
        circle(512,250,i+100);
        circle(512,230,i+30);
        arc(512+40,340,125,180,i+90);
        arc(512-40,340,0,55,i+90);
        settextstyle(3,0,3);
    }
}

/*
    �������ܣ���¼���湦�ܺ���
    �����������
    �����������
    ����ֵ����
*/
void ILogin(char* name,char* password,IEventStackNode* top,int id,FILE* fpHZ)
{
    int i;
    IEvent tempEvent;

    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in ILogin");
    }
    setcolor(255);
    Iouttextxy(370,450,"�û���:",fpHZ);
    Iouttextxy(370+16,500,"����:",fpHZ);

    setfillstyle(SOLID_FILL,255);
    bar(440,450-10,660,450-10+27);
    bar(440,500-10,660,500-10+27);

    setfillstyle(SOLID_FILL,247);
    bar(370,550,470,550+27);
    bar(370+190,550,470+190,550+27);

    setcolor(255);
    Iouttextxy(370+2,550+9,"��¼(����Ա)",fpHZ);
    Iouttextxy(370+10+190,550+9,"ȡ��(�ο�)",fpHZ);

    if(id==-1)
    {
        setcolor(144);
        Iouttextxy(370+10+190,600+9,"�û����������������������",fpHZ);
        strcpy(name,"\0");
        strcpy(password,"\0");
    }
    //��¼ʧ��

    setcolor(0);
    outtextxy(440+2,440+9,name);
    
    for(i=0;i<strlen(password);i++)
        outtextxy(440+2+8*i,490+9,"*");

    ISetEvent(&tempEvent,440,450-10,660,450-10+28,2,IGetName,(IFileNode*)name,NULL,1);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,440,500-10,660,500-10+28,2,IGetPassword,(IFileNode*)password,NULL,1);
    IEventStackPush(top,tempEvent);
    //�����û���������ļ����
}