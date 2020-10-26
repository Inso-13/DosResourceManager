/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-10-26
 *   ˵�����븴�ơ�ճ�������С��������Ȳ����йص�ͼ�� 
 **************************************************
 */
 
 #include"IIconU.h"

/*
    �������ܣ���ɫ����ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IGrayCopyU(int x,int y)
{
	int i;
	setcolor(DRM_LIGHTGRAY);
	line(x,y,x+12,y);
	line(x+12,y,x+12,y+5);
	line(x+12,y+5,x+18,y+5);
	line(x+12,y,x+18,y+5);
	line(x+18,y+5,x+18,y+11);
	line(x+11,y+29,x,y+29);
	line(x,y+29,x,y);
	line(x+11,y+11,x+23,y+11);
	line(x+23,y+11,x+23,y+16);
	line(x+23,y+16,x+29,y+16);
	line(x+23,y+11,x+29,y+16);
	line(x+29,y+16,x+29,y+40);
	line(x+29,y+40,x+11,y+40);
	line(x+11,y+40,x+11,y+11);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+7,y+14,DRM_LIGHTGRAY);
	floodfill(x+15,y+4,DRM_LIGHTGRAY);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+16,y+20,DRM_LIGHTGRAY);
	floodfill(x+26,y+15,DRM_LIGHTGRAY);
	setcolor(DRM_LIGHTGRAY);
	for(i=1;i<=1;i++)
	{
		line(x+2,y+3*i,x+10,y+3*i);
		line(x+13,y+11+3*i,x+21,y+11+3*i);
	}
	for(i=2;i<=3;i++)
	{
		line(x+2,y+3*i,x+16,y+3*i);
		line(x+13,y+11+3*i,x+27,y+11+3*i);
	}
	for(i=4;i<=9;i++)
	{
		line(x+2,y+3*i,x+9,y+3*i);
		line(x+13,y+11+3*i,x+27,y+11+3*i);
	}
}

/*
    �������ܣ���ɫ����ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IBlueCopyU(int x,int y)
{
	int i;
	setcolor(DRM_LIGHTGRAY);
	line(x,y,x+12,y);
	line(x+12,y,x+12,y+5);
	line(x+12,y+5,x+18,y+5);
	line(x+12,y,x+18,y+5);
	line(x+18,y+5,x+18,y+11);
	line(x+11,y+29,x,y+29);
	line(x,y+29,x,y);
	line(x+11,y+11,x+23,y+11);
	line(x+23,y+11,x+23,y+16);
	line(x+23,y+16,x+29,y+16);
	line(x+23,y+11,x+29,y+16);
	line(x+29,y+16,x+29,y+40);
	line(x+29,y+40,x+11,y+40);
	line(x+11,y+40,x+11,y+11);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+7,y+14,DRM_LIGHTGRAY);
	floodfill(x+15,y+4,DRM_LIGHTGRAY);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+16,y+20,DRM_LIGHTGRAY);
	floodfill(x+26,y+15,DRM_LIGHTGRAY);
	setcolor(DRM_LIGHTBLUE);
	for(i=1;i<=1;i++)
	{
		line(x+2,y+3*i,x+10,y+3*i);
		line(x+13,y+11+3*i,x+21,y+11+3*i);
	}
	for(i=2;i<=3;i++)
	{
		line(x+2,y+3*i,x+16,y+3*i);
		line(x+13,y+11+3*i,x+27,y+11+3*i);
	}
	for(i=4;i<=9;i++)
	{
		line(x+2,y+3*i,x+9,y+3*i);
		line(x+13,y+11+3*i,x+27,y+11+3*i);
	}
}

/*
    �������ܣ���ɫճ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IGrayPasteU(int x,int y)
{
	int i;
	setcolor(DRM_DARKGRAY); 
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	rectangle(x+8,y+5,x+32,y+35);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+20,y+20,DRM_DARKGRAY);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);	
	for(i=2;i<=8;i++)
	{
		line(x+12,y+5+3*i,x+28,y+5+3*i);
	}
	setfillstyle(1,DRM_LIGHTGRAY);
	sector(x+17,y+7,90,180,5,3);
	sector(x+23,y+7,0,90,5,3);
	bar(x+17,y+4,x+23,y+7);
	bar(x+17,y+4,x+23,y+3);
	pieslice(x+20,y+3,0,180,3);
}

/*
    �������ܣ���ɫճ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IBrownPasteU(int x,int y)
{
	int i;
	setcolor(DRM_BROWN); 
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	rectangle(x+8,y+5,x+32,y+35);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+20,y+20,DRM_BROWN);
	setcolor(DRM_LIGHTBLUE);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);	
	for(i=2;i<=8;i++)
	{
		line(x+12,y+5+3*i,x+28,y+5+3*i);
	}
	setcolor(DRM_CHOCOLATE);
	setfillstyle(1,DRM_CHOCOLATE);
	sector(x+17,y+7,90,180,5,3);
	sector(x+23,y+7,0,90,5,3);
	bar(x+17,y+4,x+23,y+7);
	bar(x+17,y+4,x+23,y+3);
	pieslice(x+20,y+3,0,180,3);
}

/*
    �������ܣ�ɾ��ͼ�������� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IBasicDeleteU(int x,int y)
{
	moveto(x,y+3);
	lineto(x+3,y);
	lineto(x+20,y+17);
	lineto(x+37,y);
	lineto(x+40,y+3);
	lineto(x+23,y+20);
	lineto(x+40,y+37);
	lineto(x+37,y+40);
	lineto(x+20,y+23);
	lineto(x+3,y+40);
	lineto(x,y+37);
	lineto(x+17,y+20);
	line(x,y+3,x+17,y+20);
}

/*
    �������ܣ���ɫɾ��ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IGrayDeleteU(int x,int y)
{
	setcolor(DRM_LIGHTGRAY);
	IbasicdeleteU(x,y);
	setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
	floodfill(x+20,y+20,DRM_LIGHTGRAY);
}

/*
    �������ܣ���ɫɾ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IRedDeleteU(int x,int y)
{
	setcolor(DRM_BLACK);
	IbasicdeleteU(x,y);
	setfillstyle(SOLID_FILL,DRM_RED);
	floodfill(x+20,y+20,DRM_BLACK);
} 

/*
    �������ܣ���ɫ����ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IGrayClipU(int x,int y)
{
	setcolor(DRM_BLACK);
	moveto(x+16,y+23);
	lineto(x+24,y+23);
	lineto(x+29,y+8);
	lineto(x+29,y+5);
	lineto(x+20,y+20);
	lineto(x+11,y+5);
	lineto(x+11,y+8);
	line(x+11,y+8,x+16,y+23); 
	setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
	floodfill(x+20,y+22,DRM_BLACK);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_LIGHTGRAY);
	arc(x+20,y+35,0,180,12);
	arc(x+8,y+23,270,360,12);
	arc(x+32,y+23,180,270,12);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);	
	setfillstyle(SOLID_FILL,DRM_BLACK);
	fillellipse(x+20,y+22,2,2);
}

/*
    �������ܣ���ɫ����ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IBlueClipU(int x,int y)
{
	setcolor(DRM_BLACK);
	moveto(x+16,y+23);
	lineto(x+24,y+23);
	lineto(x+29,y+8);
	lineto(x+29,y+5);
	lineto(x+20,y+20);
	lineto(x+11,y+5);
	lineto(x+11,y+8);
	line(x+11,y+8,x+16,y+23); 
	setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
	floodfill(x+20,y+22,DRM_BLACK);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_LIGHTBLUE);
	arc(x+20,y+35,0,180,12);
	arc(x+8,y+23,270,360,12);
	arc(x+32,y+23,180,270,12);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);	
	setfillstyle(SOLID_FILL,DRM_RED);
	fillellipse(x+20,y+22,2,2);
}

/*
    �������ܣ���ɫ������ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IGrayRenameU(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_LIGHTGRAY);
	bar(x,y+13,x+40,y+27);
	setfillstyle(SOLID_FILL,DRM_BLACK);
	bar(x+3,y+16,x+22,y+24);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setcolor(DRM_BLACK);
	line(x+31,y+5,x+31,y+35);
	arc(x+27,y+5,0,90,4);
	arc(x+35,y+5,90,180,4);
	arc(x+27,y+35,270,360,4);
	arc(x+35,y+35,180,270,4);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH); 
}

/*
    �������ܣ���ɫ������ͼ��
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IBlueRenameU(int x,int y)
{
	setcolor(DRM_BLACK);
	rectangle(x,y+13,x+40,y+27);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+20,y+20,DRM_BLACK);
	setfillstyle(SOLID_FILL,DRM_BLUE);
	bar(x+3,y+16,x+22,y+24);
	setcolor(DRM_BLACK);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	line(x+31,y+5,x+31,y+35);
	arc(x+27,y+5,0,90,4);
	arc(x+35,y+5,90,180,4);
	arc(x+27,y+35,270,360,4);
	arc(x+35,y+35,180,270,4);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH); 
}

/*
    �������ܣ��½��ļ���ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void INewFolderU(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_ORANGE);
	bar(x,y,x+21,y+32);
	setcolor(DRM_LIGHTYELLOW);
	rectangle(x,y,x+21,y+32);
	setcolor(DRM_ORANGE);
	line(x,y+32,x+8,y+32);
	setcolor(DRM_LIGHTYELLOW);
	line(x,y,x+8,y+8);
	line(x+8,y+8,x+8,y+40);
	line(x+8,y+40,x,y+32);
	line(x,y+32,x,y);
	setcolor(DRM_YELLOW);
	floodfill(x+2,y+26,DRM_LIGHTYELLOW);	
	floodfill(x+6,y+35,DRM_LIGHTYELLOW);
}

/*
    �������ܣ�ȫ��ѡ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void IAllSelectU(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
	bar(x,y+21,x+19,y+40);
	bar(x+21,y,x+40,y+19);
	bar(x,y,x+19,y+19);
	bar(x+21,y+21,x+40,y+40);
}

/*
    �������ܣ�ȡ��ѡ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void INonSelectU(int x,int y)
{
	setcolor(DRM_LIGHTGRAY);
	rectangle(x+1,y+1,x+18,y+18);
	rectangle(x+22,y+22,x+39,y+39);
	rectangle(x+1,y+22,x+18,y+39);
	rectangle(x+22,y+1,x+39,y+18);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+5,y+5,DRM_LIGHTGRAY);
	floodfill(x+30,y+30,DRM_LIGHTGRAY);
	floodfill(x+30,y+5,DRM_LIGHTGRAY);
	floodfill(x+5,y+30,DRM_LIGHTGRAY);
}

/*
    �������ܣ�����ѡ��ͼ�� 
    ���������(x,y)����ͼ�����Ͻ�λ��
    �����������
    ����ֵ����
*/
void INagSelectU(int x,int y)
{
	setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
	bar(x,y+21,x+19,y+40);
	bar(x+21,y,x+40,y+19);
	setcolor(DRM_LIGHTGRAY);
	rectangle(x+1,y+1,x+18,y+18);
	rectangle(x+22,y+22,x+39,y+39);
	setfillstyle(SOLID_FILL,DRM_WHITE);
	floodfill(x+30,y+30,DRM_LIGHTGRAY);
	floodfill(x+5,y+5,DRM_LIGHTGRAY);
}
