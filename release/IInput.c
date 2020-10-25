/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-10-7
 *   ˵�������뺯��
 **************************************************
 */

#include"IInput.h"


/*
    �������ܣ������Եػ�ȡ�ַ���
    ���������x���������λ�õĺ�����, y���������λ�õ�������, length���������ĳ���. flag��������������
    ���������string������ȡ���ַ���
    ����ֵ����ȡ���ַ������׵�ַ
    ע��flag=0 ������;flag=1 ���ؿ�; flag=2 �����û���;flag=3 ��������;flag=4 ���ļ�/���ļ���
*/
char *IGetString(int x,int y,int length,char *string,int flag)
{
    char *org=string;       //��¼��string�ĳ�ʼλ��
    char tempChar='\0';     //���ڽ���������ַ�
    char temp[20];          //�����ַ���
    int n,i,t=0,j;          //ѭ����������

    fflush(stdin);  //ˢ�¼��̻�����

    if(flag==NAME_STR||flag==PASSWORD_STR||flag==GOTO_STR)
        setcolor(DRM_WHITE);
    else
        setcolor(DRM_RED);
    outtextxy(500+DF,754+DF,"Enter or ESC");

    setcolor(DRM_BLACK);
    if(flag==SEARCH_STR||flag==NAME_STR||flag==PASSWORD_STR||flag==GOTO_STR)
    {
        rectangle(x-1,y,x+length+1,y+27);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        IBarInput(x,y+1,x+length,y+26,DRM_BLACK,DRM_WHITE);
    }
    else
    {
        if(flag==NEWFILE_STR)
            strcpy(string,"");
        rectangle(x-1,y+6,x+length+1,y+25);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(x,y+7,x+length,y+24);   
    }
    //��ʼ�������
    n=strlen(string);
    i=n;

    setcolor(DRM_RED);
    if(flag!=PASSWORD_STR)
        outtextxy(x+2,y+9,string);
    else
        for(j=0;j<n;j++)
        {
            outtextxy(x+2+8*j,y+9,"*");
        }
    //���flag==3, ������ʾ��������

    while(1)
    {
        while(!kbhit())
        {
            if(t>0)
                setcolor(DRM_RED);
            else
                setcolor(DRM_WHITE);
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            t++;
        }
        //����t���ڼ�ʱ��ʵ����˸����Ч��

        if(flag==SEARCH_STR||flag==NAME_STR||flag==PASSWORD_STR||flag==GOTO_STR)
            IBarInput(x,y+1,x+length,y+26,DRM_BLACK,DRM_WHITE);
        else
        {
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(x,y+7,x+length,y+24);
        }
        //���ֲ�ͬ�������

        tempChar=getch();

        if(tempChar=='\r')  //�س���
            break;
        else if(tempChar=='\b')  //�˸��
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)  //ESC��
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //�����
                i--;
            else if(tempChar=='M'&&n>i)    //�ҷ����
                i++;
            else
            {
                getch();
                tempChar=getch();
                continue;
            }
        }
        else if((n<12||n<80&&flag==GOTO_STR)&&((tempChar>='0'&&tempChar<='9')||\
        (tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||\
        tempChar=='_'||(flag==SEARCH_STR&&(tempChar=='?'||tempChar=='*'))||(flag==GOTO_STR&&(tempChar==':'||tempChar=='\\'))))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //�Ϸ��ַ�����

        setcolor(DRM_RED);
        if(flag==SEARCH_STR||flag==NAME_STR||flag==PASSWORD_STR||flag==GOTO_STR)
            IBarInput(x,y+1,x+length,y+26,DRM_BLACK,DRM_WHITE);
        else
        {
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(x,y+7,x+length,y+24);   
        }
        //���������

        if(flag!=PASSWORD_STR)
            outtextxy(x+2,y+9,string);
        else
            for(j=0;j<n;j++)
                outtextxy(x+2+8*j,y+9,"*");
        //�Ƿ������ʾ
    }
    if(flag==NAME_STR||flag==PASSWORD_STR)
        setfillstyle(SOLID_FILL,DRM_DARKGRAY);
    else
        setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(500+DF,754+DF,600+DF,764+DF);
    return org;
}
