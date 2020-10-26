/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������¼����
 **************************************************
 */

#include"ILogin.h"

/*
    �������ܣ�����¼����ı���
    �����������
    �����������
    ����ֵ����
*/
void IPlainLogin(FILE *fpHZ)
{
    int i;  //ѭ����������

    if(fpHZ==NULL)
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fpHZ is NULL in ILogin");
    }
    setfillstyle(SOLID_FILL,DRM_DARKGRAY);
    bar(0+DF,0+DF,1024+DF,768+DF);
    setcolor(DRM_WHITE);
    for(i=0;i<10;i++)
    {
        circle(512+DF,250+DF,i+100);
        circle(512+DF,230+DF,i+30);
        arc(512+40+DF,340+DF,125,180,i+90);
        arc(512-40+DF,340+DF,0,55,i+90);
        settextstyle(3,0,3);
    }

    setcolor(DRM_WHITE);
    Iouttextxy(370+DF,450+DF,"�û���:",fpHZ);
    Iouttextxy(386+DF,500+DF,"����:",fpHZ);

    setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
    bar(370+DF,550+DF,470+DF,550+27+DF);
    bar(370+190+DF,550+DF,470+190+DF,550+27+DF);
    //��ť
    setcolor(DRM_WHITE);
    Iouttextxy(370+2+DF,550+9+DF,"��¼(����Ա)",fpHZ);
    Iouttextxy(370+10+190+DF,550+9+DF,"ȡ��(�ο�)",fpHZ);
    //��ť�ϵĺ���
    Iouttextxy(70+DF,750+DF,"��Windows��Դ������",fpHZ);
    Iouttextxy(800+DF,750+DF,"���ߣ�����껡���һ��",fpHZ);
}

/*
    �������ܣ���¼���湦�ܺ���
    ���������name����������û���, password�������������, top�����¼�ջ, fpHZ�������ֿ�ָ��
    �����������
    ����ֵ����
*/
void ILogin(char *name,char *password,IEventStackNode *top,char id,FILE *fpHZ)
{
    int i;  //ѭ����������
    IEvent tempEvent;

    if(fpHZ==NULL)
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fpHZ is NULL in ILogin");
    }
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(440+DF,450-10+DF,660+DF,450-10+27+DF);
    bar(440+DF,500-10+DF,660+DF,500-10+27+DF);
    //�����


    if(id==-1)
    {
        setcolor(DRM_RED);
        Iouttextxy(370+10+190+DF,600+9+DF,"�û����������������������",fpHZ);
        strcpy(name,"\0");
        strcpy(password,"\0");
    }
    //��¼ʧ��
    setcolor(DRM_BLACK);
    outtextxy(440+2+DF,440+9+DF,name);
    for(i=0;i<strlen(password);i++)
        outtextxy(440+2+8*i+DF,490+9+DF,"*");

    ISetEvent(&tempEvent,440+DF,450-10+DF,660+DF,450-10+28+DF,MOUSE_LEFT_PRESS,\
    IGetName,(IFileNode*)name,NULL,REACT_LOGIN);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,440+DF,500-10+DF,660+DF,500-10+28+DF,MOUSE_LEFT_PRESS,\
    IGetPassword,(IFileNode*)password,NULL,REACT_LOGIN);
    IEventStackPush(top,tempEvent);
    //�����û���������ļ����
}

/*
    �������ܣ���¼�������û�������
    ���������name����������û���, password�������������
    ���������id������ݱ�־
    ����ֵ����
*/
void ILoginConfirm(char *id,char *name,char *password)
{
    FILE *fp=fopen("C:\\DOSRES\\ETC\\ADMIN.TXT","rb");  //�򿪴����û�����������ļ�
    char nameC[13],passwordC[13],passwordP[13],temp[27];  //�����ַ���
    int i;  //ѭ����������

    if(fp==NULL)
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fp is NULL in main");
    }
    while(fgets(temp,27,fp))
    {
        for(i=0;i<strlen(temp);i++)
        {
            if(temp[i]==':')    //�ҵ��ָ���
                break;
        }
        strcpy(passwordC,temp+i+1);
        strcpy(temp+i,"\0");
        strcpy(nameC,temp);
        if(passwordC[strlen(passwordC)-1]=='\n')
            passwordC[strlen(passwordC)-2]='\0';   //΢��
        IEncrypt(password,passwordP);
        if(!strcmp(nameC,name)&&!strcmp(passwordC,passwordP))
        {
            *id=1;  //����Ա��¼�ɹ�
            break;
        }
    }
    fclose(fp); //�ر��ļ�
    fp=NULL;
}

/*
    �������ܣ���ȡ�û���
    ���������nam�������ڴ洢�û���, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetName(IFileNode *nam,IFileNode *null)
{
    char *name =(char*)nam;

    ICheckNull(null);
    IGetString(440+DF,440+DF,220,name,NAME_STR);
    //��ȡ�û���
}

/*
    �������ܣ���ȡ�û���
    ���������pass�������ڴ洢����, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetPassword(IFileNode *pass,IFileNode *null)
{
    char *password=(char*)pass;

    ICheckNull(null);
    IGetString(440+DF,490+DF,220,password,PASSWORD_STR);
    //��ȡ����
}