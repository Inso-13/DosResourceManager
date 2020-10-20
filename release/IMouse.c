/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵�����������صĲ��ֺ���
 **************************************************
 */

#include"IMouse.h"

/*
    �������ܣ�����������״
    �����������
    ���������mouseDraw�������ڼ�¼������״
    ����ֵ����
*/
void IMouseMath(int (*mouseDraw)[16])
{
    int i,j,u,k;
    int up[16][16],down[16][16];
    long upNum[16]={0x3fff,0x1fff,0x0fff,0x07ff,0x03ff,0x01ff,0x00ff,0x007f,0x003f,\
    0x00ff,0x01ff,0x10ff,0x30ff,0xf87f,0xf87f,0xfc3f};
    long downNum[16]={0x0000,0x7c00,0x6000,0x7000,0x7800,0x7c00,0x7e00,0x7f00,0x7f80,\
    0x7e00,0x7c00,0x4600,0x0600,0x0300,0x0300,0x0180};

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

/*
    �������ܣ��������ʾ
    ���������(x,y)�������Ҫ��ʾ��λ��, mouseDraw�������ڼ�¼������״
    ���������pixelSave�������ڼ�¼��������ǵ�������ɫ
    ����ֵ����
*/
void IMouseOn(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16])
{
    int i,j;
    int color;

    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            pixelSave[i][j]=getpixel(x+j,y+i);
            //����ԭ������ɫ

            if(mouseDraw[i][j]==1)
                putpixel(x+j,y+i,DRM_MOUSEBLACK);
            else if(mouseDraw[i][j]==2)
                putpixel(x+j,y+i,DRM_MOUSEBLACK);
            //�����
        }
    }
}

/*
    �������ܣ��������
    ���������(x,y)��������λ��, mouseDraw�������ڼ�¼������״, pixelSave�������ڼ�¼��������ǵ�������ɫ
    �����������
    ����ֵ����
*/
void IMouseOff(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16])
{
    int i,j;

    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
        {
            if(mouseDraw[i][j]==3||mouseDraw[i][j]==4)
                continue;
            putpixel(x+j,y+i,DRM_MOUSEBLACK);
            putpixel(x+j,y+i,pixelSave[i][j]);
            //ԭλ�������ȥ
        }
}

/*
    �������ܣ��������״̬
    ���������(pMouseX,pMouseY)�������λ������ָ��, mouseDraw������¼������״, pixelSave�������ڼ�¼��������ǵ�������ɫ
    �����������
    ����ֵ����
*/
int IMouseStatus(int *pMouseX,int *pMouseY,int (*mouseDraw)[16],int (*pixelSave)[16])
{
    int status=0,i,j,color,t=0;
    int x=*pMouseX;
    int y=*pMouseY;
    
    while(x==*pMouseX&&y==*pMouseY&&status==0)
    {
        t++;
        if(t>100)
            break;
            
        IMouseGetXY(pMouseX,pMouseY);
        if(*pMouseX!=x||*pMouseY!=y)    //����ƶ���status bit0 ��1
        {
            status+=MOUSE_MOVE;
            IMouseOff(x,y,mouseDraw,pixelSave);
            IMouseOn(*pMouseX,*pMouseY,mouseDraw,pixelSave);
        }
        if(ILeftPress())    //������������status bit1 ��1
        {
            status+=MOUSE_LEFT_PRESS;
            delay(100);
            if(!ILeftPress())   //������˫����status bit3 ��1
            {
                delay(100);
                if(ILeftPress())
                    status+=MOUSE_DOUBLE_LEFT_PRESS;
            }
        }
        if(IRightPress())   //����Ҽ�������status bit2 ��1
        {
            delay(18);
            if(IRightPress())    //������
               status+=MOUSE_RIGHT_PRESS;
        }
        if(IMouseLeftRelease()) //�������ͷţ�status bit4 ��1
            status+=MOUSE_LEFT_RELEASE;
    }
    return status;
} 

/*
**
***
    ���ϴ����������磬�����޸�
***
**
*/


/*
    �������ܣ���ȡ��굱ǰλ��
    ���������(pMouseX,pMouseY)�������λ������ָ��
    �����������
    ����ֵ����
*/
void IMouseGetXY(int *pMouseX,int *pMouseY)    
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    *pMouseX=regs.x.cx;
    *pMouseY=regs.x.dx;
}

/*
    �������ܣ��ж�����Ƿ��������
    �����������
    �����������
    ����ֵ������������أ����򷵻�0
*/
int ILeftPress()
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    return(regs.x.bx&1);
}

/*
    �������ܣ��ж�����Ƿ��Ҽ�����
    �����������
    �����������
    ����ֵ���Ҽ��������أ����򷵻�0
*/
int IRightPress()
{
    union REGS regs; 
    regs.x.ax=3;
    int86(0x33,&regs,&regs);
    return(regs.x.bx&2);
}

/*
    �������ܣ������������ƶ���Χ
    ���������xMax��������ƶ��������, yMax��������ƶ��������
    �����������
    ����ֵ����
*/
void IMouseSetLimit(int xMax,int yMax)
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

/*
    �������ܣ��ж�����Ƿ�����ͷ�
    �����������
    �����������
    ����ֵ������ͷŷ��أ����򷵻�0
*/
int IMouseLeftRelease()
{
    union REGS regs; 
    regs.x.ax=6;
    regs.x.bx=0;
    int86(0x33,&regs,&regs);
    return(regs.x.ax&1);
}
