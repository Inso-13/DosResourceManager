/*
    �汾�ţ�0.6.2
    ���ߣ������
    �������ڣ�2020-9-10
    ˵������Windows��Դ������,���ڲ�����, ��δ֪����
*/


#include"main.h"

void main()
{
    int mouseDraw[16][16],mouseSave[16][16],mouseX,mouseY,mouseStatus;  //�����ر���
    int lastMenuX,lastMenuY,lastMenu=0,menu=0;  //�˵���ر���
    int id,exit=0,i,j;  //�������ͱ���
    char activeFlag=0,numOfSelected=0,page0=1,page1=1,page2=1,menuFlag=0,searching=0;   //��־����
    char name[13],password[13],nameC[13],passwordC[13],temp[50];    //�����ַ���
    void *view1Image=NULL;  //ͼ�λ�����
    FILE* fp=NULL,*fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb");    //�ļ�ָ��
    IFileNode *root=NULL;        //�ļ����ڵ�
    IFileNodePointer *curNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));  //��ǰ�ڵ�ָ��
    IFileNodePointer *nodeX=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));    //�����ڵ�ָ��
    IEventStackNode *top0=IInitEventStack(),*top1=IInitEventStack();    //�¼�ջ��
    //�������

    SVGA_Init();
    Set_Pal_File("C:\\DOSRES\\SRC\\win.act");
    view1Image=malloc(imagesize(0,0,95,160));
    //ͼ�ν����ʼ��
#ifdef DB
	IMouseMath(mouseDraw);
#endif
    IMouseSetLimit(1023,767);
    //����ʼ��

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
        if(kbhit()&&getch()==13||(mouseStatus&2)&&mouseX>370&&mouseX<470&&mouseY>550&&mouseY<577)
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
            IWarningBeep();
        }
        else if((mouseStatus&2)&&mouseX>370+190&&mouseX<470+190&&mouseY>550&&mouseY<550+27)
        {
            id=0;
            break;
        }
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
    nodeX->next=NULL;
    //�ļ��ڵ��ʼ��

    IPlainView(fpHZ);
    IView0(root,&curNode,nodeX,top0,4,110,&page0,1);
    IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            mouseSave[i][j]=getpixel(mouseX+j,mouseY+i);
    //��ѭ����ʼ

    while(!exit)
    {   
        if(coreleft()<1000)
        {
            setcolor(144);
            Iouttextxy(500,300,"�ڴ治�㣬����3����˳�",fpHZ);
            IWarningBeep();
            delay(3000);
            IQuit();
        }

#ifdef DB
        setcolor(0);
        sprintf(temp,"left memory:%u Byte",coreleft());
        outtextxy(500,753,temp);
#endif

        mouseStatus=IMouseStatus(&mouseX,&mouseY,mouseDraw,mouseSave);
        //���״̬��ѯ
        activeFlag=IEventStackActive(top0,mouseX,mouseY,mouseStatus);
        //�ı�0�Ŵ���
        if(!activeFlag)
            activeFlag=IEventStackActive(top1,mouseX,mouseY,mouseStatus);
        //�ı�1�Ŵ���
        if((mouseStatus&2)&&mouseX>1004&&mouseX<1016&&mouseY>8&&mouseY<16)
            exit=1;
        //����˳���ť

        if((menuFlag&1)||((mouseStatus&4)&&mouseX>240&&mouseX<1024&&mouseY>88&&mouseY<744))
            menu=1;
        else if(mouseStatus&2)
            menu=0;
        //�Ƿ��Լ���˵�

        if(bioskey(2)&4)
        {
            delay(100);
            if(bioskey(2)&4)
            {
                if(menuFlag&4)
                    menuFlag&=11;
                else
                    menuFlag|=4;

                activeFlag|=4;
            }
        }
        //�Ƿ���Ctrl

        if((mouseStatus&2)&&mouseX>992&&mouseX<1001&&mouseY>720&&mouseY<731)
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
        else if((mouseStatus&2)&&mouseX>928&&mouseX<586*1.6&&mouseY>720&&mouseY<731)
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
        }
        //1�Ŵ��ڵķ�ҳ

        if(!lastMenu&&menu==1){
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenuX=mouseX;
            lastMenuY=mouseY;
            getimage((mouseX>928)?928:mouseX,(mouseY>607)?607:mouseY,((mouseX>928)?928:mouseX)+95,((mouseY>607)?607:mouseY)+160,view1Image);
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
            putimage((lastMenuX>928)?928:lastMenuX,(lastMenuY>607)?607:lastMenuY,view1Image,COPY_PUT);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
            lastMenu=0;
        }   //�رղ˵�����

        if(activeFlag&2)
        {
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(0,110,238,740);
            IEventStackPop(top0,1000);
            IView0(root,&curNode,nodeX,top0,4,110,&page0,1);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        //����0�Ŵ���
        if((activeFlag&4)||(menuFlag&2))
        {
            searching=0;
            page2=1;
            IMouseOff(mouseX,mouseY,mouseDraw,mouseSave);
            setfillstyle(SOLID_FILL,255);
            bar(248,90,1022,740);
            bar(192,52,800,76);
            bar(0,745,992,766);
            IEventStackPop(top1,1000);
            numOfSelected=IView1(&curNode,nodeX,top1,&page1,&menuFlag,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        //����1�Ŵ���
        if(activeFlag&8)
        {
            searching=1;
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
            IView2(&page2,fpHZ);
            IMouseOn(mouseX,mouseY,mouseDraw,mouseSave);
        }
        //����2�Ŵ���
    }

    Icd("C:\\DOSRES\\SRC");
    //�����ͷ��ڴ�
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