#include<stdlib.h>
#include<graphics.h>
#include<DOS.H>
#include<conio.h>
#include"IMouse.h"


void IMouseMath(int (*mouseDraw)[16])   //计算鼠标的形状
{
    int i,j,u,k;
    int up[16][16],down[16][16];
    long upNum[16]={0x3fff,0x1fff,0x0fff,0x07ff,0x03ff,0x01ff,0x00ff,0x007f,0x003f,0x00ff,0x01ff,0x10ff,0x30ff,0xf87f,0xf87f,0xfc3f};
    long downNum[16]={0x0000,0x7c00,0x6000,0x7000,0x7800,0x7c00,0x7e00,0x7f00,0x7f80,0x7e00,0x7c00,0x4600,0x0600,0x0300,0x0300,0x0180};

    for(i=0;i<16;i++)
    {
        j=u=15;
        while(upNum[i]!=0)
        {
            up[i][j]=upNum[i]%2;
            j--;
            upNum[i]/=2;
        }
        while(downNum[i]!=0)
        {
            down[i][u--]=downNum[i]%2;
            downNum[i]/=2;
        }
        for(k=j;k>=0;k--)
            up[i][k]=0;
        for(k=u;k>=0;k--)
            down[i][k]=0;
        for(k=0;k<16;k++)
        {
            if(up[i][k]==0&&down[i][k]==0)
                mouseDraw[i][k]=1;
            else if(up[i][k]==0&&down[i][k]==1)
                mouseDraw[i][k]=2;
            else if(up[i][k]==1&&down[i][k]==0)
                mouseDraw[i][k]=3;
            else
                mouseDraw[i][k]=4;
        }
    }
    mouseDraw[1][2]=4;
}
/*鼠标光标显示*/
void IMouseOn(int x,int y,int (*mouseDraw)[16],int(*pixelSave)[16])
{
    int i,j;
    int color;
    for(i=0;i<16;i++)/*画鼠标*/
    {
        for(j=0;j<16;j++)
        {
            pixelSave[i][j]=getpixel(x+j,y+i);/*保存原来的颜色*/
            if(mouseDraw[i][j]==1)
                putpixel(x+j,y+i,0);
            else if(mouseDraw[i][j]==2)
                putpixel(x+j,y+i,0);
        }
    }
}
/*隐藏鼠标*/
void IMouseOff(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16])
{
    int i,j;
    for(i=0;i<16;i++)/*原位置异或消去*/
        for(j=0;j<16;j++)
        {
            if(mouseDraw[i][j]==3||mouseDraw[i][j]==4)
                continue;
            putpixel(x+j,y+i,0);
            putpixel(x+j,y+i,pixelSave[i][j]);
        }
}
int IMouseStatus(int *pMouseX,int *pMouseY,int (*mouseDraw)[16],int(*pixelSave)[16])/*鼠标按键情况*/
{
    int status=0,i,j,color;
    int x=*pMouseX;
    int y=*pMouseY;/*默认鼠标没有移动*/
    
    while(x==*pMouseX&&y==*pMouseY&&status==0)
    {
        IMouseGetXY(pMouseX,pMouseY);
        if(*pMouseX!=x||*pMouseY!=y)    /*鼠标移动，status bit0 置1*/
        {
            status+=1;
            IMouseOff(x,y,mouseDraw,pixelSave);
            IMouseOn(*pMouseX,*pMouseY,mouseDraw,pixelSave);/*新位置显示*/
        }
        if(ILeftPress())    /*鼠标左键单击，status bit1 置1*/
        {
            delay(18);
            if(ILeftPress())    /*防抖动*/
                status+=2;
            delay(82);
            if(!ILeftPress())   /*鼠标左键双击，status bit4 置1*/
            {
                delay(100);
                if(ILeftPress())
                    status+=8;
            }
        }
        if(IRightPress())   /*鼠标右键单击，status bit3 置1*/
        {
            delay(18);
            if(IRightPress())    /*防抖动*/
               status+=4;
        }
        if(IMouseLeftRelease()) /*鼠标左键释放，status bit5 置1*/
            status+=16;
    }
    return status;
} 

/*
**
***
    以上代码来自网络，略有修改
***
**
*/

void IMouseGetXY(int *pMouseX,int *pMouseY)     //获取鼠标当前位置
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    *pMouseX=regs.x.cx;
    *pMouseY=regs.x.dx;
}
int ILeftPress()
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    return(regs.x.bx&1);
}
int IRightPress()
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    return(regs.x.bx&2);
}
void IMouseSetLimit(int xMax,int yMax)  //请使用640*480或800*600
{
    union REGS regs; 
    regs.x.ax=7;
    regs.x.cx=0;
    regs.x.dx=xMax;
    int86(0x33,&regs,&regs);
    regs.x.ax=8;
    regs.x.cx=0;
    regs.x.dx=yMax;
    int86(0x33,&regs,&regs);
}
int IMouseLeftRelease()
{
    union REGS regs; 
    regs.x.ax=6;
    regs.x.bx=0;
    int86(0x33,&regs,&regs);
    return(regs.x.ax&1);
}
void IMouseSetXY(int x,int y)
{
    union REGS regs;
    regs.x.ax=4;
    regs.x.cx=x;
    regs.x.dx=y;
    int86(0x33,&regs,&regs);
}
void IMouseReset()
{
    union REGS regs;
    regs.x.ax=0;
    int86(0x33,&regs,&regs);
}