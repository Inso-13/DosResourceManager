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
void IPlainLogin()
{
    int i;
    
    setfillstyle(SOLID_FILL,248);
    bar(0+DF,0+DF,1024+DF,768+DF);
    setcolor(255);
    for(i=0;i<10;i++)
    {
        circle(512+DF,250+DF,i+100);
        circle(512+DF,230+DF,i+30);
        arc(512+40+DF,340+DF,125,180,i+90);
        arc(512-40+DF,340+DF,0,55,i+90);
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
    Iouttextxy(370+DF,450+DF,"�û���:",fpHZ);
    Iouttextxy(386+DF,500+DF,"����:",fpHZ);

    setfillstyle(SOLID_FILL,255);
    bar(440+DF,450-10+DF,660+DF,450-10+27+DF);
    bar(440+DF,500-10+DF,660+DF,500-10+27+DF);

    setfillstyle(SOLID_FILL,247);
    bar(370+DF,550+DF,470+DF,550+27+DF);
    bar(370+190+DF,550+DF,470+190+DF,550+27+DF);

    setcolor(255);
    Iouttextxy(370+2+DF,550+9+DF,"��¼(����Ա)",fpHZ);
    Iouttextxy(370+10+190+DF,550+9+DF,"ȡ��(�ο�)",fpHZ);

    if(id==-1)
    {
        setcolor(144);
        Iouttextxy(370+10+190+DF,600+9+DF,"�û����������������������",fpHZ);
        strcpy(name,"\0");
        strcpy(password,"\0");
    }
    //��¼ʧ��

    setcolor(0);
    outtextxy(440+2+DF,440+9+DF,name);
    
    for(i=0;i<strlen(password);i++)
        outtextxy(440+2+8*i+DF,490+9+DF,"*");

    ISetEvent(&tempEvent,440+DF,450-10+DF,660+DF,450-10+28+DF,2,IGetName,(IFileNode*)name,NULL,1);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,440+DF,500-10+DF,660+DF,500-10+28+DF,2,IGetPassword,(IFileNode*)password,NULL,1);
    IEventStackPush(top,tempEvent);
    //�����û���������ļ����
}

/*
    �������ܣ���¼�������û�������
    ���������name����������û���, password�������������
    ���������id������ݱ�־
    ����ֵ����
*/
void ILoginConfirm(int* id,char* name,char* password)
{
    FILE* fp=NULL;
    char nameC[13],passwordC[13],passwordP[13],temp[150];
    int i;

    fp=fopen("C:\\DOSRES\\ETC\\ADMIN.TXT","rb");
    if(fp==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fp is NULL in main");
    }
    while(fgets(temp,150,fp))
    {
        for(i=0;i<strlen(temp);i++)
        {
            if(temp[i]==':')
                break;
        }
        strcpy(passwordC,temp+i+1);
        strcpy(temp+i,"\0");
        strcpy(nameC,temp);
        if(passwordC[strlen(passwordC)-1]=='\n')
            passwordC[strlen(passwordC)-2]='\0';
        IEncrypt(password,passwordP);
        if(!strcmp(nameC,name)&&!strcmp(passwordC,passwordP))
        {
            *id=1;
            break;
        }
    }
    fclose(fp);
    fp=NULL;
}

/*
    �������ܣ���ȡ�û���
    ���������nam�������ڴ洢�û���, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetName(IFileNode* nam,IFileNode* null)
{
    char* name =(char*)nam;

    IGetString(440+DF,440+DF,220,name,2);
    //��ȡ�û���
}

/*
    �������ܣ���ȡ�û���
    ���������pass�������ڴ洢����, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetPassword(IFileNode* pass,IFileNode* null)
{
    char* password=(char*)pass;

    IGetString(440+DF,490+DF,220,password,3);
    //��ȡ����
}