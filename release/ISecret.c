/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：主要定义加密函数
 **************************************************
 */

#include"ISecret.h"

/*
    函数功能：将明文密码加密
    输入参数：plain——明文密码
    输出参数：cipher——密文密码
    返回值：无
*/
void IEncrypt(char *plain,char *cipher)
{
    int i,n;
    unsigned long num;
    char temp[2]={0};

    n=strlen(plain);
    strcpy(cipher,"");
    for(i=0;i<n-1;i++)
    {
        num=plain[i]*i+plain[i+1]*(i+1);
        num%=36;
        if(num<26)
        {
            temp[0]='a'+num;
            strcat(cipher+i,temp);
        }
        else
        {
            temp[0]='0'+num-26;
            strcat(cipher+i,temp);
        }
    }
    temp[0]=plain[n-1]+1;
    strcat(cipher+n-1,temp);
}
