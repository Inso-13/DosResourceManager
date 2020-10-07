/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：登录界面
 **************************************************
 */

#include"ILogin.h"

/*
    函数功能：画登录界面的背景
    输入参数：无
    输出参数：无
    返回值：无
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
    函数功能：登录界面功能函数
    输入参数：无
    输出参数：无
    返回值：无
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
    Iouttextxy(370+DF,450+DF,"用户名:",fpHZ);
    Iouttextxy(386+DF,500+DF,"密码:",fpHZ);

    setfillstyle(SOLID_FILL,255);
    bar(440+DF,450-10+DF,660+DF,450-10+27+DF);
    bar(440+DF,500-10+DF,660+DF,500-10+27+DF);

    setfillstyle(SOLID_FILL,247);
    bar(370+DF,550+DF,470+DF,550+27+DF);
    bar(370+190+DF,550+DF,470+190+DF,550+27+DF);

    setcolor(255);
    Iouttextxy(370+2+DF,550+9+DF,"登录(管理员)",fpHZ);
    Iouttextxy(370+10+190+DF,550+9+DF,"取消(游客)",fpHZ);

    if(id==-1)
    {
        setcolor(144);
        Iouttextxy(370+10+190+DF,600+9+DF,"用户名或密码错误，请重新输入",fpHZ);
        strcpy(name,"\0");
        strcpy(password,"\0");
    }
    //登录失败

    setcolor(0);
    outtextxy(440+2+DF,440+9+DF,name);
    
    for(i=0;i<strlen(password);i++)
        outtextxy(440+2+8*i+DF,490+9+DF,"*");

    ISetEvent(&tempEvent,440+DF,450-10+DF,660+DF,450-10+28+DF,2,IGetName,(IFileNode*)name,NULL,1);
    IEventStackPush(top,tempEvent);
    ISetEvent(&tempEvent,440+DF,500-10+DF,660+DF,500-10+28+DF,2,IGetPassword,(IFileNode*)password,NULL,1);
    IEventStackPush(top,tempEvent);
    //设置用户名、密码的激活函数
}

/*
    函数功能：登录界面检查用户名密码
    输入参数：name——输入的用户名, password——输入的密码
    输出参数：id——身份标志
    返回值：无
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
    函数功能：获取用户名
    输入参数：nam——用于存储用户名, null——用于占位
    输出参数：无
    返回值：无
*/
void IGetName(IFileNode* nam,IFileNode* null)
{
    char* name =(char*)nam;

    IGetString(440+DF,440+DF,220,name,2);
    //获取用户名
}

/*
    函数功能：获取用户名
    输入参数：pass——用于存储密码, null——用于占位
    输出参数：无
    返回值：无
*/
void IGetPassword(IFileNode* pass,IFileNode* null)
{
    char* password=(char*)pass;

    IGetString(440+DF,490+DF,220,password,3);
    //获取密码
}