/*
 **************************************************
 *   �汾�ţ�1.0.0
 *   ���ߣ������
 *   �������ڣ�2020-10-7
 *   ˵������Windows��Դ������,���ڲ�����
 **************************************************
 */

#include"main.h"

void main()
{
    int mouseDraw[16][16],mouseSave[16][16],mouseX,mouseY,mouseStatus;  //�����ر���
    int lastMenuX,lastMenuY,lastMenu=0,menu=0;  //�˵���ر���
    int id,exit=0,i,j;  //�������ͱ���
    char activeFlag=0,numOfSelected=0,page0=1,page1=1,page2=1,menuFlag=0,searching=0;   //��־����
    char name[13],password[13],temp[150];    //�����ַ���
    void *view1Image=NULL;  //ͼ�λ�����
    FILE *fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb"),*fpCLS=NULL;    //�ļ�ָ��
    IFileNode *root=NULL;        //�ļ����ڵ�
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));  //��ǰ�ڵ�ָ��
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));    //�����ڵ�ָ��
    IEventStackNode *top0=IInitEventStack(),*top1=IInitEventStack();    //�¼�ջ��
    //�������

    fpCLS=fopen("C:\\DOSRES\\ETC\\DEL.TXT","w+");
    fclose(fpCLS);
    fpCLS=fopen("C:\\DOSRES\\ETC\\LOG.TXT","w+");
    fclose(fpCLS);  //����ļ�

    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
    view1Image=malloc(imagesize(0,0,95,160));   //ͼ�ν����ʼ��

	IMouseMath(mouseDraw);
    IMouseSetLimit(1023+2*DF,767+2*DF);
    delay(2);   //����ʼ��

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
        }   //�ȴ������û�������
        if(kbhit()&&getch()==13||(mouseStatus&2)&&mouseX>370+DF&&mouseX<470+DF&&mouseY>550+DF&&mouseY<577+DF)
        {
            ILoginConfirm(&id,name,password);
            if(id==1)
                break;
            id=-1;
            IWarningBeep();   
        }   //����¼
        else if((mouseStatus&2)&&mouseX>370+190+DF&&mouseX<470+190+DF&&mouseY>550+DF&&mouseY<550+27+DF)
        {
            id=0;
            break;
        }   //ȡ����¼
    }
#endif
    //��¼����

    root=IDiskInit(id);
    curNode->child=root;
    curNode->pre=NULL;
    curNode->next=NULL;
    curNode->wait=30000;
    nodeX->child=NULL;
    nodeX->pre=NULL;
    nodeX->next=NULL;   //�ļ��ڵ��ʼ��

    IPlainView(fpHZ);
    IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,1,fpHZ);
    IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
    
    //��ѭ����ʼ
    while(!exit)
    {   
#ifdef DB
        setcolor(0);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(500+DF,753+DF,temp);
#endif

        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);//���״̬��ѯ
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);//�ı�0�Ŵ���
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);//�ı�1/2�Ŵ���
        if((mouseStatus&2)&&mouseX>1004+DF&&mouseX<1016+DF&&mouseY>8+DF&&mouseY<16+DF)
            exit=1; //����˳���ť

        if((menuFlag&1)||((mouseStatus&4)&&mouseX>240+DF&&mouseX<1024+DF&&mouseY>88+DF&&mouseY<744+DF))
            menu=1;
        else if(mouseStatus&2)
            menu=0; //�Ƿ��Լ���˵�

        if(bioskey(2)&4)
        {
            delay(100);
            if(bioskey(2)&4)
            {
                if(menuFlag&4)
                    menuFlag&=123;
                else
                    menuFlag|=4;

                activeFlag|=4;
            }
        }   //�Ƿ���Ctrl

        if((mouseStatus&2)&&mouseX>992+DF&&mouseX<1001+DF&&mouseY>720+DF&&mouseY<731+DF)
        {
            if(!searching)
            {
                page1++;
                activeFlag|=4;
            }
            else
            {
                page2++;
                activeFlag|=8;
            }
        }
        else if((mouseStatus&2)&&mouseX>928+DF&&mouseX<586*1.6+DF&&mouseY>720+DF&&mouseY<731+DF)
        {
            if(!searching)
            {
                page1--;
                activeFlag|=4;
            }
            else
            {
                page2--;
                activeFlag|=8;
            }
        }   //���ڷ�ҳ

        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage((mouseX>928+DF)?(928+DF):mouseX,(mouseY>607+DF)?(607+DF):mouseY,((mouseX>928+DF)?(928+DF):mouseX)+95,((mouseY>607+DF)?(607+DF):mouseY)+160,view1Image);
            IMenu(mouseX,mouseY,numOfSelected,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            if(!(menuFlag&1))
                lastMenu=1;
            continue;
        }   //����˵�����
        else if(menuFlag&1)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            IMenu(lastMenuX,lastMenuY,numOfSelected,top1,curNode,nodeX,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=1;
            continue;
        }   //��������˵�
        else if(lastMenu&&!menu)
        {

            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            putimage((lastMenuX>928+DF)?(928+DF):lastMenuX,(lastMenuY>607+DF)?(607+DF):lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
        }   //�رղ˵�����

        if(activeFlag&2)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(0+DF,110+DF,238+DF,740+DF);
            IEventStackPop(top0,1000);
            IView0(root,&curNode,nodeX,top0,4+DF,110+DF,&page0,1,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //����0�Ŵ���
        if((activeFlag&4)||(menuFlag&2))
        {
            searching=0;
            page2=1;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(248+DF,90+DF,1022+DF,740+DF);
            bar(192+DF,52+DF,800+DF,76+DF);
            bar(0+DF,745+DF,1023+DF,766+DF);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //����1�Ŵ���
        if(activeFlag&8)
        {
            searching=1;
            for(i=0;i<16;i++)
                for(j=0;j<16;j++)
                    mouseSave[i][j]=255;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setcolor(7);
            rectangle(832+DF,51+DF,1017+DF,78+DF);
            line(851+DF,51+DF,851+DF,78+DF);
            setfillstyle(SOLID_FILL,255);
            bar(248+DF,90+DF,1022+DF,740+DF);
            bar(192+DF,52+DF,800+DF,76+DF);
            bar(0+DF,745+DF,1023+DF,766+DF);
            IEventStackPop(top1,1000);
            IView2(&page2,fpHZ,top1,&curNode);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }   //����2�Ŵ���
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