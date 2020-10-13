/*
 **************************************************
 *   版本号：1.2.1
 *   作者：黄子昊
 *   生成日期：2020-10-13
 *   说明：仿Windows资源管理器
 **************************************************
 */

#include"main.h"

void main()
{
    int mouseDraw[16][16],mouseSave[16][16],mouseX,mouseY,mouseStatus;  //鼠标相关变量
    int lastMenuX,lastMenuY,lastMenu=0,menu=0;  //菜单相关变量
    int i,j;  //其他整型变量
    char id,exit=0,activeFlag=0,numOfSelected=0,page0=1,page1=1,page2=1,menuFlag=0,searching=0;   //标志变量
    char name[13]={0},password[13]={0},temp[PATH_LEN];    //辅助字符串
    void *view1Image=NULL;  //图形缓冲区
    FILE *fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb"),*fpCLS=NULL;    //文件指针
    IFileNode *root=NULL;        //文件根节点
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));  //当前节点指针
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));    //辅助节点指针
    IEventStackNode *top0=IInitEventStack(),*top1=IInitEventStack();    //事件栈顶
    //定义变量

    fpCLS=fopen("C:\\DOSRES\\ETC\\DEL.TXT","w+");fclose(fpCLS);
    fpCLS=fopen("C:\\DOSRES\\ETC\\LOG.TXT","w+");fclose(fpCLS);  //清空文件
    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
    view1Image=malloc(imagesize(0,0,95,160));   //图形界面初始化
	IMouseMath(mouseDraw);
    IMouseSetLimit(1023+2*DF,767+2*DF);
    delay(2);   //鼠标初始化
    IPlainLogin(fpHZ);
    ILogin(name,password,top0,id,fpHZ);
    while(1)
    {
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        if(activeFlag==REACT_LOGIN||id==-1)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IEventStackPop(top0,10);
            ILogin(name,password,top0,id,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            id=0;
        }   //等待输入用户名密码
        if(kbhit()&&getch()==13||(mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>370+DF&&mouseX<470+DF&&mouseY>550+DF&&mouseY<577+DF)
        {
            ILoginConfirm(&id,name,password);
            if(id==1)
                break;
            id=-1;
            IWarningBeep();   
        }   //检查登录
        else if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>370+190+DF&&mouseX<470+190+DF&&mouseY>550+DF&&mouseY<550+27+DF)
        {
            id=0;
            break;
        }   //取消登录
    }   //登录界面
    root=IDiskInit(id);
    curNode->child=root;curNode->pre=NULL;curNode->next=NULL;curNode->wait=30000;
    nodeX->child=NULL;nodeX->pre=NULL;nodeX->next=NULL;   //文件节点初始化
    IPlainView(fpHZ);
    IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,VIEW0_PAGE,fpHZ);
    IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
    //主循环开始
    while(!exit)
    {   
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);//鼠标状态查询
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);//改变0号窗口
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);//改变1/2号窗口
        if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>1004+DF&&mouseX<1016+DF&&mouseY>8+DF&&mouseY<16+DF)
            exit=1; //点击退出按钮
        if((menuFlag&FLAG_IS_SEC_MENU)||((mouseStatus&MOUSE_RIGHT_PRESS)&&mouseX>240+DF&&mouseX<1024+DF&&mouseY>88+DF&&mouseY<744+DF))
            menu=1;
        else if(mouseStatus&MOUSE_LEFT_PRESS)
            menu=0; //是否尝试激活菜单
        if(bioskey(2)&4)
        {
            delay(100);
            if(bioskey(2)&4)
            {
                if(menuFlag&FLAG_IS_CTRLED)
                    menuFlag&=FLAG_DEL_CTRLED;
                else
                    menuFlag|=FLAG_ADD_CTRLED;
                activeFlag|=REACT_VIEW1;
            }
        }   //是否按下Ctrl
        if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>992+DF&&mouseX<1001+DF&&mouseY>720+DF&&mouseY<731+DF)
        {
            if(!searching)
            {
                page1++;
                activeFlag|=REACT_VIEW1;
            }
            else
            {
                page2++;
                activeFlag|=REACT_VIEW2;
            }
        }
        else if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>928+DF&&mouseX<937+DF&&mouseY>720+DF&&mouseY<731+DF)
        {
            if(!searching)
            {
                page1--;
                activeFlag|=REACT_VIEW1;
            }
            else
            {
                page2--;
                activeFlag|=REACT_VIEW2;
            }
        }   //窗口翻页
        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage((mouseX>928+DF)?(928+DF):mouseX,(mouseY>607+DF)?(607+DF):mouseY,((mouseX>928+DF)?(928+DF):mouseX)+95,((mouseY>607+DF)?(607+DF):mouseY)+160,view1Image);
            IMenu(mouseX,mouseY,numOfSelected,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            if(!(menuFlag&FLAG_IS_SEC_MENU))
                lastMenu=1;
            continue;
        }   //激活菜单窗口
        else if(menuFlag&FLAG_IS_SEC_MENU)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IMenu(lastMenuX,lastMenuY,numOfSelected,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=1;
            continue;
        }   //激活排序菜单
        else if(lastMenu&&!menu)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            putimage((lastMenuX>928+DF)?(928+DF):lastMenuX,(lastMenuY>607+DF)?(607+DF):lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
        }   //关闭菜单窗口
        if(activeFlag&REACT_VIEW0)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(0+DF,110+DF,238+DF,740+DF);
            IEventStackPop(top0,1000);
            IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,1,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //更新0号窗口
        if((activeFlag&REACT_VIEW1)||(menuFlag&FLAG_TO_DEL))
        {
            searching=0;
            page2=1;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(248+DF,90+DF,1022+DF,740+DF);
            bar(192+DF,52+DF,800+DF,76+DF);
            bar(0+DF,745+DF,1023+DF,766+DF);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //更新1号窗口
        if(activeFlag&REACT_VIEW2)
        {
            searching=1;
            for(i=0;i<16;i++)
                for(j=0;j<16;j++)
                    mouseSave[i][j]=DRM_WHITE;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setcolor(DRM_DARKGRAY);
            line(0+DF,84+DF,1024+DF,84+DF);
            line(0+DF,85+DF,1024+DF,85+DF);
            rectangle(832+DF,51+DF,1017+DF,78+DF);
            line(851+DF,51+DF,851+DF,78+DF);
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(248+DF,90+DF,1022+DF,740+DF);
            bar(192+DF,52+DF,800+DF,76+DF);
            bar(0+DF,745+DF,1023+DF,766+DF);
            IEventStackPop(top1,1000);
            IView2(&page2,fpHZ,top1,&curNode);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //激活2号窗口
    }
    fpCLS=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+");
    fclose(fpCLS);
    Icd("C:\\DOSRES\\SRC");
    //以下释放内存
    IDelPointer(curNode);
    IDelFilelist(root);
    free(view1Image);
    IDelStack(top1);
    IDelStack(top0);
    fclose(fpHZ);
    free(nodeX);
    free(root);
    IQuit();
}