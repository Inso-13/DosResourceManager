#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<conio.h>
#include"IType.h"
#include"IUtility.h"
#define regs.x.flags _FS
char IgetDisk()
{
    int t1=_AX,ans;
    _AH = 0x19;
    geninterrupt(0x21);
    ans = _AL;
    _AX = t1;
    return ans+'A';
}
void IsetDisk(char disk)
{
    int t1=_AX,t2=_DX;
    _AH = 0x0e;
    _DL = disk - 'A';
    geninterrupt(0x21);
    _AX = t1;
    _DX = t2;
}
void Ishutdown()
{
    int t1 = _AX;
    _AH = 0x4c;
    geninterrupt(0x21);
    _AX = t1;
}
void Ipwd()
{
    int t1 = _AX, t2 = _DX, t3 = _SI;
    _AH = 0x47;
    _DL = IgetDisk()-'A'+1;
    geninterrupt(0x21);
    printf("%c:\\%s",IgetDisk(),_SI);
    _AX = t1;
    _DX = t2;
    _SI = t3;
}
void Icd(char* path)
{
    int t1 = _AX, t2 = _DX;
    if(path[1]==':')
    {
        IsetDisk(path[0]);
        strcpy(path,path+3);
    }
    _AH = 0x3b;
    _DX = (int)path;
    geninterrupt(0x21);
    _AX = t1;
    _DX = t2;
}
int Idir(char* name)
{
    int num=0,pta;
    char over[36];
    int temp1=_AX,temp2=_BX,temp3=_CX,temp4=_DX;
    _AH=0x1a;
    pta=_BX;
    geninterrupt(0x21);
    _AH=0x4e;
    _CX=0x16;
    _DX=(int)name;
    geninterrupt(0x21);
    strcpy(over,(char*)(pta+0x1e));
    printf("%s\n",over);
    while(1)
    {
        _AH=0x4f;
        geninterrupt(0x21);
        if(strcmp(over,(char*)(pta+0x1e)))
        {
            printf("%s\n",pta+0x1e);
            strcpy(over,(char*)(pta+0x1e));
        }
        else
            break;
    }
    _DX=temp4;
    _CX=temp3;
    _BX=temp2;
    _AX=temp1;
    return num;
}