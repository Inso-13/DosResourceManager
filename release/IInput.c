/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-7
 *   说明：输入函数
 **************************************************
 */

#include"IInput.h"


/*
    函数功能：交互性地获取字符串
    输入参数：x——输入框位置的横坐标, y——输入框位置的纵坐标, length——输入框的长度. flag——输入框的类型
    输出参数：string——获取的字符串
    返回值：获取的字符串的首地址
    注：flag=0 重命名;flag=1 搜素框; flag=2 输入用户名;flag=3 输入密码;flag=4 新文件/新文件夹
*/
char *IGetString(int x,int y,int length,char *string,int flag)
{
    char *org=string;       //记录下string的初始位置
    char tempChar='\0';     //用于接收输入的字符
    char temp[20];          //辅助字符串
    int n,i,t=0,j;          //循环辅助变量

    fflush(stdin);  //刷新键盘缓冲区

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
    //初始化输入框
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
    //如果flag==3, 加密显示输入内容

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
        //变量t用于计时，实现闪烁光标的效果

        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);
        //两种不同的输入框

        tempChar=getch();

        if(tempChar=='\r')  //回车键
            break;
        else if(tempChar=='\b')  //退格键
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)  //ESC键
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //左方向键
                i--;
            else if(tempChar=='M'&&n>i)    //右方向键
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
        //合法字符检验

        setcolor(DRM_RED);
        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   
        //两种输入框

        if(flag!=3)
            outtextxy(x+2,y+9,string);
        else
            for(j=0;j<n;j++)
                outtextxy(x+2+8*j,y+9,"*");
        //是否加密显示
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
