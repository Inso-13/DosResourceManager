#include"main.h"

void main()
{
    FILE *fpHZ;
    int mouseDraw[16][16],mouseSave[16][16];
    int mouseX,mouseY;
    IFileNode *root,*rootR;
    IEventStackNode *top;

    mouseX=0,mouseY=0;
    fpHZ=fopen("HZ16","rb");
    root=IDiskInit();
    // rootR=IFindNodeByName("R:",root);
    top=IInitEventStack();
    IInitGraph();
    IMouseMath(mouseDraw);
    IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
    //  init above

    
    /*    the main loop    */
    while(!kbhit())
    {
        IEventStackActive(top,mouseX,mouseY,IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave),0);
    }
    
    // ~init below
    Icd("C:\\DOSRES\\SRC");
    IDelStack(top);
    IDetree(root);
    free(root);
    fclose(fpHZ);
    getch();
    IQuit();
}

