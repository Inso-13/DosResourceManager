#include<STDIO.H>
#include<ALLOC.H>
#include<STRING.H>
#include<CONIO.H>
#include<DOS.H>
#include<PROCESS.H>
#include<BIOS.H>
#include"IType.h"
#include"IMouse.h"
#include"IInit.h"
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IHanZi.h"
#include"IView.h"
#include"IActive.h"
// #define DB

void main()
{
    int mouseDraw[16][16],mouseSave[16][16];
    int mouseX,mouseY,mouseStatus,exit=0,lastMenu=0,menu=0,menuFlag=0;
    int lastMenuX,lastMenuY;
    char activeFlag=0,temp[50],isCtrl=0,numOfSelected=0,page1=1,delFlag=0;
    void *view1Image=NULL;
    IFileNode *root;
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));
    IEventStackNode *top0,*top1;

    root=IDiskInit();
    top0=IInitEventStack();
    top1=IInitEventStack();
    curNode->child=root;
    curNode->pre=NULL;
    curNode->next=NULL;
    curNode->wait=15;
    nodeX->child=NULL;
    nodeX->pre=NULL;
    nodeX->next=NULL;

    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
    //  init above
    view1Image=malloc(imagesize(0,0,95,160));
    IPlainView();

    IView0(root,curNode,top0,4,110);
    IView1(&curNode,top1,isCtrl,&page1,&delFlag);
    IMouseMath(mouseDraw);
    IMouseSetLimit(1024,768);
    /*    the main loop    */
    while(!exit)
    {   
#ifdef DB
        setcolor(0);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(528,752,temp);
#endif
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);

        if((mouseStatus&2)&&mouseX>1004&&mouseX<1016&&mouseY>8&&mouseY<16)
            exit=1;
        if(menuFlag||((mouseStatus&4)&&mouseX>240&&mouseX<1024&&mouseY>88&&mouseY<744))
            menu=1;
        else if(mouseStatus&2)
            menu=0;
        if(bioskey(2)&4)
        {
            delay(100);
            if(bioskey(2)&4)
            {
                isCtrl=!(isCtrl&isCtrl);
                activeFlag|=4;
            }
        }
        if((mouseStatus&2)&&mouseX>992&&mouseX<1001&&mouseY>720&&mouseY<731)
        {
            page1++;
            activeFlag|=4;
        }
        else if((mouseStatus&2)&&mouseX>928&&mouseX<586*1.6&&mouseY>720&&mouseY<731)
        {
            page1--;
            activeFlag|=4;
        }

        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage(mouseX,mouseY,mouseX+95,mouseY+160,view1Image);
            IMenu(mouseX,mouseY,numOfSelected,top1,curNode,nodeX,&menuFlag,&delFlag);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            if(!menuFlag)
                lastMenu=1;
            continue;
        }
        else if(menuFlag)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IMenu(lastMenuX,lastMenuY,numOfSelected,top1,curNode,nodeX,&menuFlag,&delFlag);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=1;
            continue;
        }
        else if(lastMenu&&!menu)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            putimage(lastMenuX,lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
        }

        if(activeFlag&2)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(0,110,238,740);
            IEventStackPop(top0,1000);
            IView0(root,curNode,top0,4,110);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        if((activeFlag&4)||delFlag)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(248,110,1022,740);
            bar(192,52,800,76);
            bar(0,745,992,766);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,top1,isCtrl,&page1,&delFlag);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
    }
    // ~init below
    Icd("C:\\DOSRES\\SRC");
    IDelPointer(curNode);
    free(view1Image);
    IDelStack(top1);
    IDelStack(top0);
    IDetree(root);
    free(nodeX);
    free(root);
    IQuit();
}