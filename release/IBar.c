/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-10-16
 *   ˵�������䶨�弸�������κ���
 **************************************************
 */
#include"IBar.h"

/*
    �������ܣ���������oldColor�����ص��ΪnewColor(�������)
    ���������(x1,y1),(x2,y2)���������ζԽ������꣬oldColor��������Ҫ�滻����ɫ��newColor������Ŀ����ɫ
    �����������
    ����ֵ����
*/
void IBar(int x1,int y1,int x2,int y2,int oldColor,int newColor)
{
    int i,j;
    
    for(j=y1;j<=y2;j++)
    {
        for(i=x1;i<=x2;i++) //����ÿ��ÿ�е�ÿһ����
        {
            if(getpixel(i,j)==oldColor||getpixel(i,j)==DRM_MOUSEBLACK)
            {
                putpixel(i,j,newColor);
            }
        }
    }
}

/*
    �������ܣ���������oldColor�����ص��ΪnewColor(������ɫ)
    ���������(x1,y1),(x2,y2)���������ζԽ������꣬oldColor��������Ҫ�滻����ɫ��newColor������Ŀ����ɫ
    �����������
    ����ֵ����
*/
void IBarInput(int x1,int y1,int x2,int y2,int oldColor,int newColer)
{
    int i,j;
    
    for(j=y1;j<=y2;j++)
    {
        for(i=x1;i<=x2;i++)
        {
            if(getpixel(i,j)==oldColor||getpixel(i,j)==DRM_RED)
            {
                putpixel(i,j,newColer);
            }
        }
    }
}