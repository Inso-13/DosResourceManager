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
#include"IMenu.h"
#include"IActive.h"
// #define DB

void main()
{
    int mouseDraw[16][16],mouseSave[16][16];
    int mouseX,mouseY,id,mouseStatus,exit=0,lastMenu=0,menu=0,menuFlag=0;
    int lastMenuX,lastMenuY,i,j;
    char activeFlag=0,temp[50],isCtrl=0,numOfSelected=0,page0=1,page1=1,delFlag=0;
    char name[13],password[13],nameC[13],passwordC[13];
    void *view1Image=NULL;
    FILE* fp=NULL,*fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb");
    IFileNode *root;
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));
    IEventStackNode *top0,*top1;    
    //定义变量

#ifdef DB
    VGA_Init();
#else
    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
#endif

    //变量初始化
    view1Image=malloc(imagesize(0,0,95,160));
    IMouseMath(mouseDraw);
    IMouseSetLimit(1024,768);
    //界面初始化

#ifdef DB
    id=1;
#else
    strcpy(name,"\0");
    strcpy(password,"\0");
    IPlainLogin();
    ILogin(name,password,top0,id,fpHZ);
    while(1)
    {
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        if(activeFlag==1||id==-1)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IEventStackPop(top0,10);
            ILogin(name,password,top0,id,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            id=0;
        }
        if((mouseStatus&2)&&mouseX>370&&mouseX<470&&mouseY>550&&mouseY<550+27)
        {
            fp=fopen("C:\\DOSRES\\ETC\\ADMIN.TXT","rb");
            if(fp==NULL)
            {
                setcolor(0);
                outtextxy(100,100,"fp is NULL in main");
            }
            while(fgets(temp,50,fp))
            {
                for(i=0;i<strlen(temp);i++)
                {
                    if(temp[i]==':')
                        break;
                }
                strcpy(passwordC,temp+i+1);
                strcpy(temp+i,"\0");
                strcpy(nameC,temp);
                if(passwordC[strlen(passwordC)-1]=='\n')
                    passwordC[strlen(passwordC)-2]='\0';
                if(!strcmp(nameC,name)&&!strcmp(passwordC,password))
                {
                    id=1;
                    break;
                }
            }
            fclose(fp);
            fp=NULL;

            if(id==1)
                break;
            id=-1;
        }
        else if((mouseStatus&2)&&mouseX>370+190&&mouseX<470+190&&mouseY>550&&mouseY<550+27)
        {
            id=0;
            break;
        }
    }
#endif

    root=IDiskInit(id);
    top0=IInitEventStack();
    top1=IInitEventStack();

    curNode->child=root;
    curNode->pre=NULL;
    curNode->next=NULL;
    curNode->wait=30000;
    nodeX->child=NULL;
    nodeX->pre=NULL;
    nodeX->next=NULL;

    //登录界面

    IPlainView(fpHZ);
    IView0(root,&curNode,top0,4,110,&page0,1);
    IView1(&curNode,top1,isCtrl,&page1,&delFlag,fpHZ);
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
    //主循环开始
    while(!exit)
    {   
#ifdef DB
        setcolor(0);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(300,400,temp);
#endif
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        //鼠标状态查询
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        //改变0号窗口
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);
        //改变1号窗口

        if((mouseStatus&2)&&mouseX>1004&&mouseX<1016&&mouseY>8&&mouseY<16)
            exit=1;
        //点击退出按钮

        if(menuFlag||((mouseStatus&4)&&mouseX>240&&mouseX<1024&&mouseY>88&&mouseY<744))
            menu=1;
        else if(mouseStatus&2)
            menu=0;
        //是否尝试激活菜单

        if(bioskey(2)&4)
        {
            delay(100);
            if(bioskey(2)&4)
            {
                isCtrl=!(isCtrl&isCtrl);
                activeFlag|=4;
            }
        }
        //是否按下Ctrl

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
        //1号窗口的翻页

        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage((mouseX>944)?944:mouseX,(mouseY>608)?608:mouseY,((mouseX>944)?944:mouseX)+95,((mouseY>608)?608:mouseY)+160,view1Image);
            IMenu(mouseX,mouseY,numOfSelected,top1,curNode,nodeX,&menuFlag,&delFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            if(!menuFlag)
                lastMenu=1;
            continue;
        }   //激活菜单窗口
        else if(menuFlag)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IMenu(lastMenuX,lastMenuY,numOfSelected,top1,curNode,nodeX,&menuFlag,&delFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=1;
            continue;
        }   //激活排序菜单
        else if(lastMenu&&!menu)
        {

            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            putimage((lastMenuX>944)?944:lastMenuX,(lastMenuY>608)?608:lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
        }   //关闭菜单窗口

        if(activeFlag&2)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(0,110,238,740);
            IEventStackPop(top0,1000);
            IView0(root,&curNode,top0,4,110,&page0,1);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        //更新0号窗口
        if((activeFlag&4)||delFlag)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(248,90,1022,740);
            bar(192,52,800,76);
            bar(0,745,992,766);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,top1,isCtrl,&page1,&delFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        if(activeFlag&8)
        {
            for(i=0;i<16;i++)
                for(j=0;j<16;j++)
                    mouseSave[i][j]=255;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setcolor(7);
            rectangle(832,51,1017,78);
            line(851,51,851,78);
            setfillstyle(SOLID_FILL,255);
            bar(248,90,1022,740);
            bar(192,52,800,76);
            bar(0,745,992,766);
            IEventStackPop(top1,1000);
            IView2(fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        //更新1号窗口
    }

    Icd("C:\\DOSRES\\SRC");
    //以下释放内存
    IDelPointer(curNode);
    free(view1Image);
    IDelStack(top1);
    IDelStack(top0);
    IDetree(root);
    fclose(fpHZ);
    free(nodeX);
    free(root);
    IQuit();
}