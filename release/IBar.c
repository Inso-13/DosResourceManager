/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-16
 *   说明：补充定义几个画矩形函数
 **************************************************
 */
#include"IBar.h"

/*
    函数功能：将矩形内oldColor的像素点改为newColor(包括鼠标)
    输入参数：(x1,y1),(x2,y2)———矩形对角线坐标，oldColor———需要替换的颜色，newColor———目标颜色
    输出参数：无
    返回值：无
*/
void IBar(int x1,int y1,int x2,int y2,int oldColor,int newColor)
{
    int i,j;
    
    for(j=y1;j<=y2;j++)
    {
        for(i=x1;i<=x2;i++) //对于每行每列的每一个点
        {
            if(getpixel(i,j)==oldColor||getpixel(i,j)==DRM_MOUSEBLACK)
            {
                putpixel(i,j,newColor);
            }
        }
    }
}

/*
    函数功能：将矩形内oldColor的像素点改为newColor(包括红色)
    输入参数：(x1,y1),(x2,y2)———矩形对角线坐标，oldColor———需要替换的颜色，newColor———目标颜色
    输出参数：无
    返回值：无
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