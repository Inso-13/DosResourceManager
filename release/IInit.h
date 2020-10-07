/*
 **************************************************
 *   版本号：1.0
 *   作者：往届学长
 *   生成日期：2020-9-4
 *   说明：与文件/文件夹在大图标模式下情况下显示图标相关的函数
 * 	 
 *   *****
 *	 注：本文件代码来源于往届学长，略有修改
 *	 *****
 **************************************************
 */


#ifndef __INIT_H
#define __INIT_H

//库文件
#include<GRAPHICS.H>
#include<DOS.H>
#include<STDLIB.H>
#include<STDIO.H>

//结构体
typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} SVGA_COLOR;


//函数原型
void VGA_Init(void);
int SVGA_Init(void);
void Set_Pal_File(const char * path);

#endif