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

    IView0(root,curNode,top0,3*1.6,69*1.6);
    IView1(&curNode,top1,isCtrl,&page1,&delFlag);
    IMouseMath(mouseDraw);
    IMouseSetLimit(1024,768);
    /*    the main loop    */
    while(!exit)
    {   
#ifdef DB
        setcolor(0);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(330*1.6,470*1.6,temp);
#endif
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);

        if((mouseStatus&2)&&mouseX>628*1.6&&mouseX<635*1.6&&mouseY>5*1.6&&mouseY<10*1.6)
            exit=1;
        if(menuFlag||((mouseStatus&4)&&mouseX>150*1.6&&mouseX<1024&&mouseY>55*1.6&&mouseY<465*1.6))
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
        if((mouseStatus&2)&&mouseX>620*1.6&&mouseX<626*1.6&&mouseY>450*1.6&&mouseY<457*1.6)
        {
            page1++;
            activeFlag|=4;
        }
        else if((mouseStatus&2)&&mouseX>580*1.6&&mouseX<586*1.6&&mouseY>450*1.6&&mouseY<457*1.6)
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
            bar(0,69*1.6,149*1.6,463*1.6);
            IEventStackPop(top0,1000);
            IView0(root,curNode,top0,3*1.6,69*1.6);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        if((activeFlag&4)||delFlag)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(155*1.6,110,639*1.6,463*1.6);
            bar(120*1.6,33*1.6,500*1.6,48*1.6);
            bar(0,466*1.6,620*1.6,479*1.6);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,top1,isCtrl,&page1,&delFlag);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
    }
    // ~init below
    Icd("C:\\DOSRES\\SRC");
    IDelStack(top1);
    IDelStack(top0);
    IDetree(root);
    free(view1Image);
    free(curNode);
    free(nodeX);
    free(root);
    IQuit();
}