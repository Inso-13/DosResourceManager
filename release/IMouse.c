#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include"Imouse.h"

void MouseMath(int (*up)[16],int (*down)[16],int (*mouse_draw)[16])/*计算鼠标的样子*/
{
    int i,j,u,k;
    long UpNum[16]={0x3fff,0x1fff,0x0fff,0x07ff,0x03ff,0x01ff,0x00ff,0x007f,0x003f,0x00ff,0x01ff,0x10ff,0x30ff,0xf87f,0xf87f,0xfc3f};
    long DownNum[16]={0x0000,0x7c00,0x6000,0x7000,0x7800,0x7c00,0x7e00,0x7f00,0x7f80,0x7e00,0x7c00,0x4600,0x0600,0x0300,0x0300,0x0180};

    for(i=0;i<16;i++)
    {
        j=u=15;
        while(UpNum[i]!=0)
        {
            up[i][j]=UpNum[i]%2;
            j--;
            UpNum[i]/=2;
        }
        while(DownNum[i]!=0)
        {
            down[i][u--]=DownNum[i]%2;
            DownNum[i]/=2;
        }
        for(k=j;k>=0;k--)
            up[i][k]=0;
        for(k=u;k>=0;k--)
            down[i][k]=0;
        for(k=0;k<16;k++)/*四种组合方式*/
        {
            if(up[i][k]==0&&down[i][k]==0)
                mouse_draw[i][k]=1;
            else if(up[i][k]==0&&down[i][k]==1)
                mouse_draw[i][k]=2;
            else if(up[i][k]==1&&down[i][k]==0)
                mouse_draw[i][k]=3;
            else
                mouse_draw[i][k]=4;
        }
    }
    mouse_draw[1][2]=4;/*特殊点*/
}
/*鼠标光标显示*/
void MouseOn(int x,int y,int (*mouse_draw)[16],int(*pixel_save)[16])
{
    int i,j;
    int color;
    for(i=0;i<16;i++)/*画鼠标*/
    {
        for(j=0;j<16;j++)
        {
            pixel_save[i][j]=getpixel(x+j,y+i);/*保存原来的颜色*/
            if(mouse_draw[i][j]==1)
                putpixel(x+j,y+i,0);
            else if(mouse_draw[i][j]==2)
                putpixel(x+j,y+i,15);
        }
    }
}
/*隐藏鼠标*/
void MouseOff(int* pMouseX,int* pMouseY,int (*mouse_draw)[16],int (*pixel_save)[16])
{
    int i,j,x,y,color;
    x=*pMouseX;
    y=*pMouseY;
    for(i=0;i<16;i++)/*原位置异或消去*/
        for(j=0;j<16;j++)
        {
            if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
            continue;
            color=getpixel(x+j,y+i);
            putpixel(x+j,y+i,color^color);
            putpixel(x+j,y+i,pixel_save[i][j]);
        }
}
/*鼠标是否加载
 MouseExist:1=加载
     0=未加载
 MouseButton:鼠标按键数目*/
void MouseLoad(int *MouseExist,int *MouseButton)
{
    _AX=0x00;
    geninterrupt(0x33);
    *MouseExist=_AX;
    *MouseButton=_BX;
}

/*鼠标状态值初始化*/
void MouseReset()
{
    _AX=0x00;
    geninterrupt(0x33);
}

/*设置鼠标左右边界
lx:左边界
rx:右边界       */
void MouseSetX(int lx,int rx)
{
    _CX=lx;
    _DX=rx;
    _AX=0x07;
    geninterrupt(0x33);
}

/*设置鼠标上下边界
uy:上边界
dy:下边界      */
void MouseSetY(int uy,int dy)
{
    _CX=uy;
    _DX=dy;
    _AX=0x08;
    geninterrupt(0x33);
}

/*设置鼠标当前位置
 x:横向坐标
 y:纵向坐标       */
void MouseSetXY(int x,int y)
{
    _CX=x;
    _DX=y;
    _AX=0x04;
    geninterrupt(0x33);
}

/*设置鼠标速度(缺省值:vx=8,vy=1)
 值越大速度越慢                */
void MouseSpeed(int vx,int vy)
{
    _CX=vx;
    _DX=vy;
    _AX=0x0f;
    geninterrupt(0x33);
}
/*获取鼠标按下键的信息*/
/*是否按下左键
 返回值:1=按下0=释放*/
int LeftPress()
{
    _AX=0x03;
    geninterrupt(0x33);
    return(_BX&1);
}
/*是否按下右键
 返回值同上   */
int RightPress()
{
    _AX=0x03;
    geninterrupt(0x33);
    return(_BX&2);
}

/*获取鼠标当前位置*/
void MouseGetXY(int *pMouseX,int *pMouseY)
{
    _AX=0x03;
    geninterrupt(0x33);
    *pMouseX=_CX;
    *pMouseY=_DX;
}

int MouseStatus(int *pMouseX,int *pMouseY,int (*mouse_draw)[16],int(*pixel_save)[16])/*鼠标按键情况*/
{
    int status;
    int press=0;
    
    int i,j,color;
    int x=*pMouseX;
    int y=*pMouseY;/*默认鼠标没有移动*/
    long t;

    status=0;
    
    while(x==*pMouseX&&y==*pMouseY&&status==0&&press==0)
    {
        if(LeftPress())
        {
            press=1;
            for(t=0;t<3000000;t++);
            if(!LeftPress())
            {
                for(t=0;t<3000000;t++);
                if(LeftPress())
                    press=3;
            }
        }
        else if(RightPress())
            press=2;
        MouseGetXY(pMouseX,pMouseY);
        if(*pMouseX!=x||*pMouseY!=y)
            status=1;
    }
    if(status)/*移动情况才重新显示鼠标*/
    {
        for(i=0;i<16;i++)/*原位置异或消去*/
            for(j=0;j<16;j++)
            {
                if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
                    continue;
                color=getpixel(x+j,y+i);
                putpixel(x+j,y+i,color^color);
                putpixel(x+j,y+i,pixel_save[i][j]);
            }
            MouseOn(*pMouseX,*pMouseY,mouse_draw,pixel_save);/*新位置显示*/
    }
    if(press!=0)/*有按键*/
        return press;
    return 0;/*只移动*/
}