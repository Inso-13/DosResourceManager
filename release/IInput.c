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

    setcolor(DRM_BLACK);
    if(flag>=1&&flag<=3)
    {
        rectangle(x-1,y,x+length+1,y+27);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(x,y+1,x+length,y+26);
    }
    else
    {
        if(flag==4)
            strcpy(string,"");
        rectangle(x-1,y+6,x+length+1,y+25);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(x,y+7,x+length,y+24);   
    }
    //��ʼ�������
    n=strlen(string);
    i=n;

    setcolor(DRM_RED);
    if(flag!=3)
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

        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);
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
        else if(n<12&&((tempChar>='0'&&tempChar<='9')||(tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||tempChar=='_'||(flag==1&&(tempChar=='?'||tempChar=='*'))))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //�Ϸ��ַ�����

        setcolor(DRM_RED);
        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   
        //���������

        if(flag!=3)
            outtextxy(x+2,y+9,string);
        else
            for(j=0;j<n;j++)
                outtextxy(x+2+8*j,y+9,"*");
        //�Ƿ������ʾ
    }
    if(flag==1)
    {
        setcolor(DRM_DARKGRAY);
        line(0+DF,84+DF,1024+DF,84+DF);
        line(0+DF,85+DF,1024+DF,85+DF);
        rectangle(832+DF,51+DF,1017+DF,78+DF);
    }
    return org;
}
