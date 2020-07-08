#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include"Imouse.h"

void main()
{
    int gd=DETECT,gm;
    int Keystate,MouseExist,MouseButton,MouseX,MouseY;
    int up[16][16],down[16][16],mouse_draw[16][16],mouse_save[16][16];
    
    initgraph(&gd,&gm,"c:\\Borlandc\\bgi");

    MouseMath(up,down,mouse_draw);
    MouseSetXY(100,100);
    MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
    
    outtextxy(400,500,"press to exit");
    settextstyle(0,0,4);
    outtextxy(100,200,"DOSMouseDemo");
	bar(100,300,200,350);
	settextstyle(0,0,1);
    setcolor(BLUE);
    outtextxy(125,325,"Button");
    setcolor(WHITE);
    while(!kbhit())
    {
        switch(MouseStatus(&MouseX,&MouseY,mouse_draw,mouse_save))
        {
            case 1:
                MouseOff(&MouseX,&MouseY,mouse_draw,mouse_save);
                putpixel(MouseX,MouseY,YELLOW);
                MouseGetXY(&MouseX,&MouseY);
                MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
				if(MouseX>100&&MouseX<200&&MouseY>300&&MouseY<350)
				{
	                outtextxy(300,300,"left clicked");
				}
				break;
            case 2:
                MouseOff(&MouseX,&MouseY,mouse_draw,mouse_save);
                putpixel(MouseX,MouseY,RED);
                MouseGetXY(&MouseX,&MouseY);
                MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
                if(MouseX>100&&MouseX<200&&MouseY>300&&MouseY<350)
				{
	                outtextxy(300,350,"right clicked");
				}
				break;
			case 3:
                MouseOff(&MouseX,&MouseY,mouse_draw,mouse_save);
                putpixel(MouseX,MouseY,RED);
                MouseGetXY(&MouseX,&MouseY);
                MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
                if(MouseX>100&&MouseX<200&&MouseY>300&&MouseY<350)
				{
	                outtextxy(300,400,"\(left\) double clicked");
				}
            default:
                break;
        }
    }
    closegraph();
}

