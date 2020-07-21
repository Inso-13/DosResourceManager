#include<GRAPHICS.H>
#include<STDIO.H>
#include<ALLOC.H>
#include<STRING.H>
#include<CONIO.H>
#include<DOS.H>
#include"IType.h"
#include"IMouse.h"
#include"IInit.h"
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IHanZi.h"
#include"IView.h"

void main()
{
    int mouseDraw[16][16],mouseSave[16][16];
    int mouseX,mouseY,mouseStatus,increaseX;
    char activeFlag=0,temp[50];
    IFileNode *root,*rootR;
    IFileNode *curNode=(IFileNode*)malloc(sizeof(IFileNode));
    IEventStackNode *top0,*top1;


    root=IDiskInit();
    rootR=IFindNodeByName("R:",root);
    rootR->pre->next=NULL;
    rootR->pre=NULL;
    rootR->flags|=4;
    strcpy(rootR->file.name,"ReBin");
    strcpy(rootR->file.type,"0r");
    top0=IInitEventStack();
    top1=IInitEventStack();
    curNode=root;

    IInitGraph();
    //  init above
    IPlainView();

    increaseX=IView0(root,&curNode,top0,3,69);
    IView0(rootR,&curNode,top0,3,69+increaseX);
    IView1(&curNode,top1);
    IMouseMath(mouseDraw);
    IMouseSetLimit(640,480);
    /*    the main loop    */
    while(!kbhit())
    {   
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus,0);
        sprintf(temp,"left memory:%u",coreleft());
        outtextxy(500,400,temp);
        if(activeFlag&2)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,WHITE);
            bar(0,69,149,463);
            IEventStackPop(top0,1000);
            increaseX=IView0(root,&curNode,top0,3,69);
            IView0(rootR,&curNode,top0,3,69+increaseX);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        if(activeFlag&4)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,WHITE);
            bar(160,73,639,463);
            bar(70,33,550,48);
            IEventStackPop(top1,1000);
            IView1(&curNode,top1);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
    }
    // ~init below
    Icd("C:\\DOSRES\\SRC");
    IDelStack(top1);
    IDelStack(top0);
    IDetree(root,0);
    free(curNode);
    free(root);
    getch();
    IQuit();
}
