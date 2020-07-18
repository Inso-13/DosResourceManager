#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <STRING.H>
#include <graphics.h>
#include <dos.h>
#include "IHanZi.h"

void IPutsHZ16(int x,int y,int wid,int color,int size,char *str,FILE * fp) //中文输出
{
    unsigned ZCode,BCode;
    int i,j,k,s,rec;
    long len;
    char buf[32];
    while(*str)
    {
        if((*str&0x80)&&(*(str+1)&0x80))
        {
            ZCode=(*str-0xa1)&0x7f;
            BCode=(*(str+1)-0xa1)&0x7f;
            rec=ZCode*94+BCode;
            len=rec*32L;
            fseek(fp,len,SEEK_SET);
            fread(buf,32,1,fp);
            for(i=0;i<16;i++)
            {
                for(j=0;j<2;j++)
                {
                    for(k=0;k<8;k++)
                    {
                        if(buf[2*i+j]>>(7-k)&1)
                        {
                            for(s=0;s<size;s++)
                                putpixel(x+(8*j+k)*size+s,y+i*size+s,color);
                        }
                    }
                }
            }
            x=x+16*size+wid;
            str+=2;
        }
    }
    return;    
}
void Iouttextxy(int x,int y,int wid,int color,int size,char *str,FILE * fp) //自动判断中英文输出，未测试
{
    if(!str) return;
    if(*str>=0xa0)
    {
        IPutsHZ16(x,y,wid,color,size,str,fp);
    }
    else
    {
        outtextxy(x,y,str);
    }
}