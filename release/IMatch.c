/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵����ͨ���ƥ�亯��
 **************************************************
 */

#include"IMatch.h"

/*
    �������ܣ�ͨ���ƥ��
    ���������s������ƥ����ַ���, p����ͨ���
    �����������
    ����ֵ��ƥ���򷵻�1�����򷵻�0
*/
int IMatch(char *s,char *p)
{
    int flag;
    char *src=s,*pattern=p;

    while(*src)
    {
        if(*pattern=='*')
        {
            while((*pattern=='*')||(*pattern)=='?')
                pattern++;
            if(!*pattern)
                return 1;
            while(*src && !IMatchi(*src,*pattern))
                src++;
            if(!*src) 
                return 0;
            flag=IMatch(src,pattern);
            while((!flag)&&*(src+1)&&IMatchi(*(src+1),*pattern))
                flag=IMatch(++src,pattern);
            return flag;
        }
        else
        {
            if(IMatchi(*src,*pattern)||('?'==*pattern))
                return IMatch(++src,++pattern);
            else
                return 0;
        }
    }
    if(*pattern)
    {
        if((*pattern=='*')&&(*(pattern+1)==0))
            return 1;
        else
            return 0;
    }
    else
        return 1;
}

/*
    �������ܣ�ͨ���ƥ�䲻���ִ�Сд��������
    ���������(a,b)������ƥ��������ַ�
    �����������
    ����ֵ��ƥ���򷵻�1�����򷵻�0
*/
int IMatchi(char a,char b)
{
    if(a>='a'&&a<='z')
        a+='A'-'a';
    if(b>='a'&&b<='z')
        b+='A'-'a';
    if(a==b)
        return 1;
    else
        return 0;
}