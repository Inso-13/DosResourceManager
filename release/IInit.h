/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ�����ѧ��
 *   �������ڣ�2020-9-4
 *   ˵�������ļ�/�ļ����ڴ�ͼ��ģʽ���������ʾͼ����صĺ���
 * 	 
 *   *****
 *	 ע�����ļ�������Դ������ѧ���������޸�
 *	 *****
 **************************************************
 */


#ifndef __INIT_H
#define __INIT_H

//���ļ�
#include<GRAPHICS.H>
#include<DOS.H>
#include<STDLIB.H>
#include<STDIO.H>

//�ṹ��
typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} SVGA_COLOR;


//����ԭ��
void VGA_Init(void);
int SVGA_Init(void);
void Set_Pal_File(const char *path);

#endif