/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ������ܺ���
 **************************************************
 */

#include"ISecret.h"

/*
    �������ܣ��������������
    ���������plain������������
    ���������cipher������������
    ����ֵ����
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
