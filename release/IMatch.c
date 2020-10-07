/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：通配符匹配函数
 **************************************************
 */

#include"IMatch.h"

/*
    函数功能：通配符匹配
    输入参数：s——待匹配的字符串, p——通配符
    输出参数：无
    返回值：匹配则返回1，否则返回0
*/
int IMatch(char* s,char* p)
{
    int flag;
    char* src=s,*pattern=p;

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
    函数功能：通配符匹配不区分大小写辅助函数
    输入参数：(a,b)——待匹配的两个字符
    输出参数：无
    返回值：匹配则返回1，否则返回0
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