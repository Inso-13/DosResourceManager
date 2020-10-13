/*
 **************************************************
 *   版本号：1.0
 *   修改者/作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：汉字输出相关的函数
 **************************************************
 */

#include"IHanZi.h"

/*
    函数功能：中文输出
    输入参数：(x,y)——输出位置, str——需要输出的中文, fp——汉字库文件
    输出参数：无
    返回值：无
    注：本函数源于往届学长，有修改
*/
void IPutsHZ16(int x,int y,char *str,FILE *fp)
{
    unsigned ZCode,BCode;   //区码、位码
    int i,j,k,rec;
    long len;
    char buf[32];
    int color=getcolor();

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
            x=x+16;
            str+=2;
        }
    }
    return;    
}

/*
    函数功能：自动判断中英文输出
    输入参数：(x,y)——输出位置, str——需要输出的文本, fp——汉字库文件
    输出参数：无
    返回值：无
*/
void Iouttextxy(int x,int y,char *str,FILE *fp)
{
    int inc=0;  //横轴增量
    int n,i=0;  //循环辅助变量
    char temp[3]={'\0','\0','\0'};  //辅助字符串

    if(!str) return;   //如果字符串为空，则返回

    n=strlen(str);  //字符串的长度
    while(i<n)
    {
        if((unsigned char)str[i]>=0xa0)
        {
            temp[0]=str[i];
            temp[1]=str[i+1];
            temp[2]='\0';
            IPutsHZ16(x+inc,y-5,temp,fp);
            inc+=16;
            i+=2;
        }
        //如果是中文
        else
        {
            temp[0]=str[i];
            temp[1]='\0';
            outtextxy(x+inc,y,temp);
            inc+=8;
            i+=1;
        }
        //如果不是中文
    }
}