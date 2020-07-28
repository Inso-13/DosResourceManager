#ifndef __INIT_H
#define __INIT_H

#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} SVGA_COLOR;

int SVGA_Init(void);
void SVGA_Deinit(void);
void Set_Pal_File(const char * path);

#endif