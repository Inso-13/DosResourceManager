#include<STDIO.H>
#include<STDLIB.H>
#include<STRING.H>
#include<GRAPHICS.H>
#include<CONIO.H>
#include"IMouse.h"
#include"IUtility.h"
#include"IType.h"
#include"IDir.h"
#include"IHanZi.h"
int main()
{
    FILE *fpHZ=fopen("HZ16","rb");
    int up[16][16],down[16][16],mouse_draw[16][16],mouse_save[16][16];
    int Keystate,MouseExist,MouseButton,MouseX,MouseY;
    char tempStr[80];

    IInitGraph();
    MouseMath(up,down,mouse_draw);
    MouseOn(MouseX,MouseY,mouse_draw,mouse_save);
    // init above
    
    strcpy(tempStr,"╪ссм╪ссм");
    // IFileNode rootC={{"C",{1980,1,1,0,0},"0",0,"C:"},0,1,0,0,0};
    // IFileNode* root=&rootC;
    // IFileNode rootD={{"D",{1980,1,1,0,0},"0",0,"D:"},0,1,0,0,0};
    // IEntree(root);
    // IEntree(root->child);
    // IEntree(&rootD);
    // Icd("D:\\temp\\bcgt\\working");
    // IDelFilelist(&rootC);
    // IDelFilelist(&rootD);
    IPutsHZ16(100,100,2,BLUE,tempStr,fpHZ);

    // ~init below    
    getch();
    IQuit();
    return 0;
    
}

