#include<STDIO.H>
#include<STDLIB.H>
#include<STRING.H>
#include<GRAPHICS.H>
#include<CONIO.H>
#include<DIR.H>
#include<IO.H>
#include"IMouse.h"
#include"IUtility.h"
#include"IType.h"
#include"IDir.h"
#include"IHanZi.h"

int main()
{
    // FILE *fpHZ=fopen("HZ16","rb");
    // int up[16][16],down[16][16],mouse_draw[16][16],mouse_save[16][16];
    // int Keystate,MouseExist,MouseButton,MouseX,MouseY;
    // char tempStr[80];

    // IInitGraph();
    // MouseMath(up,down,mouse_draw);
    // MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
    // init above
    // IFileNode rootC={{"C",{1980,1,1,0,0},"0",0,"C:"},0,1,0,0,0};
    // IFileNode far* root=&rootC;
    IFileNode D={{"D",{1980,1,1,0,0},"0",0,"D:\\TEMP"},0,1,0,0,0};
    // IFileNode temp={{"temp",{1980,1,1,0,0},"0",0,""},0,1,0,0,0};
    IEntree(&D);
    IEntree(D.child);
    IEntree(D.child->child);
    Icpr(D.child->child,&D);
    Irmr(IFindNodeByName("WORKING",&D));
    Icd("D:\\TEMP\\BCGT\\WORKING");
    IDelFilelist(&D);
    // ~init below    
    getch();
    IQuit();
    return 0;
    
}

