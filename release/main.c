/*
 **************************************************
 *   �汾�ţ�1.8.0
 *   ���ߣ������
 *   �������ڣ�2020-10-27
 *   ˵������Windows��Դ������
 **************************************************
 */

#include"main.h"

void main()
{
    int mouseDraw[16][16],mouseSave[16][16],mouseX,mouseY,mouseStatus;  //�����ر���
    int lastMenuX,lastMenuY,lastMenu=0,menu=0;  //�˵���ر���
    int i,j;  //�������ͱ���
    char id,exit=0,activeFlag=0,page0=1,page1=1,page2=1,menuFlag=0,searching=0;   //��־����
    char name[13]={0},password[13]={0},temp[PATH_LEN];    //�����ַ���
    void *view1Image=NULL;  //ͼ�λ�����
    FILE *fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb"),*fpCLS=NULL;    //�ļ�ָ��
    IFileNode *root=NULL;        //�ļ����ڵ�
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));  //��ǰ�ڵ�ָ��
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));    //�����ڵ�ָ��
    IEventStackNode *top0=IInitEventStack(),*top1=IInitEventStack();    //�¼�ջ��
    //�������

    fpCLS=fopen("C:\\DOSRES\\ETC\\DEL.TXT","w+");fclose(fpCLS);
    fpCLS=fopen("C:\\DOSRES\\ETC\\LOG.TXT","w+");fclose(fpCLS);  //����ļ�
    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
    view1Image=malloc(imagesize(0,0,95,160));   //ͼ�ν����ʼ��
	IMouseMath(mouseDraw);
    IMouseSetLimit(1023+2*DF,767+2*DF);
    delay(2);   //����ʼ��
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
        }   //�ȴ������û�������
        if(kbhit()&&getch()==13||(mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>370+DF&&\
        mouseX<470+DF&&mouseY>550+DF&&mouseY<577+DF)
        {
            ILoginConfirm(&id,name,password);
            if(id==1)
                break;
            id=-1;
            IWarningBeep();   
        }   //����¼
        else if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>370+190+DF&&mouseX<470+190+DF&&\
        mouseY>550+DF&&mouseY<550+27+DF)
        {
            id=0;
            break;
        }   //ȡ����¼
    }   //��¼����
    root=IDiskInit(id);
    curNode->child=root;curNode->pre=NULL;curNode->next=NULL;curNode->wait=30000;
    nodeX->child=NULL;nodeX->pre=NULL;nodeX->next=NULL;   //�ļ��ڵ��ʼ��
    IPlainView(fpHZ);
    IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,VIEW0_PAGE,fpHZ);
    IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
    //��ѭ����ʼ
    while(!exit)
    {   
        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);//���״̬��ѯ
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);//�ı�0�Ŵ���
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);//�ı�1/2�Ŵ���
        if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>1004+DF&&mouseX<1016+DF&&mouseY>8+DF&&\
        mouseY<16+DF)
            exit=1; //����˳���ť
        if((menuFlag&FLAG_IS_SEC_MENU)||((mouseStatus&MOUSE_RIGHT_PRESS)&&mouseX>240+DF&&\
        mouseX<1024+DF&&mouseY>88+DF&&mouseY<744+DF))
            menu=1;
        else if(mouseStatus&MOUSE_LEFT_PRESS)
            menu=0; //�Ƿ��Լ���˵�
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
        }   //�Ƿ���Ctrl
        if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>992+DF&&mouseX<1001+DF&&mouseY>720+DF&&\
        mouseY<731+DF)
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
        else if((mouseStatus&MOUSE_LEFT_PRESS)&&mouseX>928+DF&&mouseX<937+DF&&\
        mouseY>720+DF&&mouseY<731+DF)
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
        }   //���ڷ�ҳ
        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage((mouseX>928+DF)?(928+DF):mouseX,(mouseY>607+DF)?(607+DF):mouseY,\
            ((mouseX>928+DF)?(928+DF):mouseX)+95,((mouseY>607+DF)?(607+DF):mouseY)+160,\
            view1Image);
            IEventStackPop(top1,1000);
            IMenu(mouseX,mouseY,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            if(!(menuFlag&FLAG_IS_SEC_MENU))
                lastMenu=1;
            continue;
        }   //����˵�����
        else if(menuFlag&FLAG_IS_SEC_MENU)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IEventStackPop(top1,1000);
            IMenu(lastMenuX,lastMenuY,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=1;
            continue;
        }   //��������˵�
        else if(lastMenu&&!menu)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            putimage((lastMenuX>928+DF)?(928+DF):lastMenuX,\
            (lastMenuY>607+DF)?(607+DF):lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
            activeFlag=REACT_VIEW1;
        }   //�رղ˵�����
        if(activeFlag&REACT_VIEW0)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,DRM_WHITE);
            bar(0+DF,110+DF,238+DF,740+DF);
            IEventStackPop(top0,1000);
            IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,1,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //����0�Ŵ���
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
            IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //����1�Ŵ���
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
        }   //����2�Ŵ���
        if(activeFlag&REACT_MOUSE)
        {
            for(i=0;i<16;i++)
                for(j=0;j<16;j++)
                    if((mouseSave[i][j]==DRM_CHOSENBLUE||mouseSave[i][j]==DRM_WHITE)&&\
                    getpixel(mouseX+j,mouseY+i)!=DRM_MOUSEBLACK)
                        mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
    }
    fpCLS=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+");
    fclose(fpCLS);
    Icd("C:\\DOSRES\\SRC");
    //�����ͷ��ڴ�
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