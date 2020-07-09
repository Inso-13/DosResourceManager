#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include "IUtility.h"
#include "IHanZi.h"

void IPutsHZ16(int x,int y,int Wid,int Color,char *str,FILE *fp)
{
    unsigned Zcode,Bcode;
    int i,j,k,Rec;
    long Len;
    char Buf[32];
    while(*str)
    {
        if((*str&0x80)&&(*(str+1)&0x80))
        {
            Zcode=(*str-0xa1)&0x7f;
            Bcode=(*(str+1)-0xa1)&0x7f;
            Rec=Zcode*94+Bcode;
            Len=Rec*32L;
            fseek(fp,Len,SEEK_SET);
            fread(Buf,32,1,fp);
            for(i=0;i<16;i++)
            {
                for(j=0;j<2;j++)
                {
                    for(k=0;k<8;k++)
                    {
                        if(Buf[2*i+j]>>(7-k)&1)
                        {
                            putpixel(x+8*j+k,y+i,Color);
                        }
                    }
                }
            }
            x=x+16+Wid;
            str+=2;
        }
    }
    return;    
}