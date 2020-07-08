#include<stdio.h>
#include<stdlib.h>
#include"IMouse.h"
#include"IType.h"
#include"IDir.h"

void main()
{
    // int gd=DETECT,gm,Keystate,MouseExist,MouseButton,MouseX,MouseY;
    // int up[16][16],down[16][16],mouse_draw[16][16],mouse_save[16][16];
    IFileNode root={{"BORLANDC",{1980,1,1,0,0},"0",0,"C:\\BORLANDC"},0,1,0,0,0};
    IEntree(&root);
    Icd("D:\\temp\\bcgt\\working");
    // initgraph(&gd,&gm,"c:\\Borlandc\\bgi");
    // MouseMath(up,down,mouse_draw);
    // MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
    // init above
    IDelFilelist(&root);
    // closegraph();
}

