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


#include"IInit.h"

/*
    �������ܣ�VGAͼ�ν���ĳ�ʼ��
    �����������
    �����������
    ����ֵ����
*/
void VGA_Init(void)
{
	int GraphDriver=VGA, GraphMode=DETECT;
	initgraph(&GraphDriver, &GraphMode,"C:\\BORLANDC\\BGI");
}

/*
    �������ܣ�SVGAͼ�ν���ĳ�ʼ��
    �����������
    �����������
    ����ֵ���ɹ��򷵻�0, ʧ���򷵻�-1
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
    �������ܣ�SVGAͼ�ν���ĳ�ʼ����غ���
    ���������col����SVGA��ɫ
    �����������
    ����ֵ����
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
    �������ܣ�SVGAͼ�ν���ĳ�ʼ����غ���
    ���������path����SVGA��ɫ��·��
    �����������
    ����ֵ����
*/
void Set_Pal_File(const char *path)
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