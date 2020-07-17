#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include "IHanZi.h"

void IPutsHZ16(int x,int y,int wid,int color,char *str,FILE far* fp)
{
    unsigned ZCode,BCode;
    int i,j,k,rec;
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
                            putpixel(x+8*j+k,y+i,color);
                        }
                    }
                }
            }
            x=x+16+wid;
            str+=2;
        }
    }
    return;    
}