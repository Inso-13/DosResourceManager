/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：与SVGA图形界面初始化相关的函数
	
	***
	注：本文件代码来源于往届学长，略有修改
	***
*/


#ifndef __INIT_H
#define __INIT_H

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} SVGA_COLOR;

void VGA_Init(void);
int SVGA_Init(void);
void Set_Pal_File(const char * path);

#endif