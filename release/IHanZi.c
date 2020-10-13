/*
 **************************************************
 *   �汾�ţ�1.0
 *   �޸���/���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵�������������صĺ���
 **************************************************
 */

#include"IHanZi.h"

/*
    �������ܣ��������
    ���������(x,y)�������λ��, str������Ҫ���������, fp�������ֿ��ļ�
    �����������
    ����ֵ����
    ע��������Դ������ѧ�������޸�
*/
void IPutsHZ16(int x,int y,char *str,FILE *fp)
{
    unsigned ZCode,BCode;   //���롢λ��
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
    �������ܣ��Զ��ж���Ӣ�����
    ���������(x,y)�������λ��, str������Ҫ������ı�, fp�������ֿ��ļ�
    �����������
    ����ֵ����
*/
void Iouttextxy(int x,int y,char *str,FILE *fp)
{
    int inc=0;  //��������
    int n,i=0;  //ѭ����������
    char temp[3]={'\0','\0','\0'};  //�����ַ���

    if(!str) return;   //����ַ���Ϊ�գ��򷵻�

    n=strlen(str);  //�ַ����ĳ���
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
        //���������
        else
        {
            temp[0]=str[i];
            temp[1]='\0';
            outtextxy(x+inc,y,temp);
            inc+=8;
            i+=1;
        }
        //�����������
    }
}