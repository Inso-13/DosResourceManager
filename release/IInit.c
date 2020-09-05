/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：与SVGA图形界面初始化相关的函数

	***
	注：本文件代码来源于往届学长，略有修改
	***
*/


#include<GRAPHICS.H>
#include<DOS.H>
#include<STDLIB.H>
#include<STDIO.H>
#include"IInit.h"

/*
    函数功能：VGA图形界面的初始化
    输入参数：无
    输出参数：无
    返回值：无
*/
void VGA_Init(void)
{
	int GraphDriver, GraphMode=DETECT;
	initgraph(&GraphDriver, &GraphMode,"C:\\BORLANDC\\BGI");
}

/*
    函数功能：SVGA图形界面的初始化
    输入参数：无
    输出参数：无
    返回值：成功则返回0, 失败则返回-1
*/
int SVGA_Init(void)
{
    extern void _Cdecl SVGA_driver(void);

    int GraphDriver, GraphMode = 1;
    if ((GraphDriver = installuserdriver("SVGA", NULL)) < 0) {
		printf("InstallUserDriver Fail\n");
		return -1;
	}
	if (registerbgidriver(SVGA_driver) < 0) {
		printf("RegisterBGIDriver Fail\n");
		return -1;
    }
	initgraph(&GraphDriver, &GraphMode, "");
    return 0;
}

/*
    函数功能：SVGA图形界面的初始化相关函数
    输入参数：col——SVGA颜色
    输出参数：无
    返回值：无
*/
static void Set_Pal(const SVGA_COLOR * col)
{
	int i = 0;

	for (; i < 256; i++) {
		outportb(0x3C8, i);
		outportb(0x3C9, (col[i].R) >> 2);
		outportb(0x3C9, (col[i].G) >> 2);
		outportb(0x3C9, (col[i].B) >> 2);
	}
}

/*
    函数功能：SVGA图形界面的初始化相关函数
    输入参数：path——SVGA颜色板路径
    输出参数：无
    返回值：无
*/
void Set_Pal_File(const char * path)
{
	SVGA_COLOR     col[256];
	FILE           *fpcol = NULL;

	if ((fpcol = fopen(path,"rb")) == NULL)	{
		printf("Can't open file: %s\n", path);
		return;
	}

	if (fread((char*)&col, sizeof(col), 1, fpcol) != 1)	{
		fprintf(stderr, "Invalid file type\n");
		return;
	}

	Set_Pal(col);
}
