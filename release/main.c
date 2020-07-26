#include<GRAPHICS.H>
#include<STDIO.H>
#include<ALLOC.H>
#include<STRING.H>
#include<CONIO.H>
#include<DOS.H>
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
    int mouseX,mouseY,mouseStatus,exit=0,lastMenu=0,menu=0;
    int lastMenuX,lastMenuY;
    char activeFlag=0,temp[50],isCtrl=0,numOfSelected=0,page1=1;
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
    curNode->flag=0;
    nodeX->child=NULL;
    nodeX->pre=NULL;
    nodeX->next=NULL;

    IInitGraph();
    view1Image=malloc(5094);
    //  init above
    IPlainView();

    IView0(root,curNode,top0,3,69);
    IView1(&curNode,top1,isCtrl,&page1);
    IMouseMath(mouseDraw);
    IMouseSetLimit(640,480);
    /*    the main loop    */
    while(!exit)
    {   
#ifdef DB
        setcolor(DARKGRAY);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(330,470,temp);
#endif

        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);

        if((mouseStatus&2)&&mouseX>628&&mouseX<635&&mouseY>5&&mouseY<10)
            exit=1;
        if((mouseStatus&4)&&mouseX>150&&mouseX<640&&mouseY>55&&mouseY<465)
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
        if((mouseStatus&2)&&mouseX>620&&mouseX<626&&mouseY>450&&mouseY<457)
        {
            page1++;
            activeFlag|=4;
        }
        else if((mouseStatus&2)&&mouseX>580&&mouseX<586&&mouseY>450&&mouseY<457)
        {
            page1--;
            activeFlag|=4;
        }

        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage(mouseX,mouseY,mouseX+95,mouseY+105,view1Image);
            IMenu(mouseX,mouseY,numOfSelected,top1,curNode,nodeX);
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
            setfillstyle(SOLID_FILL,WHITE);
            bar(0,69,149,463);
            IEventStackPop(top0,1000);
            IView0(root,curNode,top0,3,69);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        if(activeFlag&4)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,WHITE);
            bar(155,73,639,463);
            bar(120,33,500,48);
            bar(0,466,620,479);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,top1,isCtrl,&page1);
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