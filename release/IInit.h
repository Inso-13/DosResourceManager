/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������SVGAͼ�ν����ʼ����صĺ���
	
	***
	ע�����ļ�������Դ������ѧ���������޸�
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