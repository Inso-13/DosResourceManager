#include<stdio.h>
#include<stdlib.h>
#include"IMouse.h"
#include"IType.h"
#include"IDir.h"

void main()
{
    // int gd=DETECT,gm,Keystate,MouseExist,MouseButton,MouseX,MouseY;
    // int up[16][16],down[16][16],mouse_draw[16][16],mouse_save[16][16];
    IFileNode rootC={{"C",{1980,1,1,0,0},"0",0,"C:"},0,1,0,0,0};
    IFileNode rootD={{"D",{1980,1,1,0,0},"0",0,"D:"},0,1,0,0,0};
    IEntree(&rootC);
    IEntree(&rootD);
    Icd("D:\\temp\\bcgt\\working");
    // initgraph(&gd,&gm,"c:\\Borlandc\\bgi");
    // MouseMath(up,down,mouse_draw);
    // MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
    // init above

    //~init below
    IDelFilelist(&rootC);
    IDelFilelist(&rootD);
    // closegraph();
}

