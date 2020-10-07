/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������ͼ������
 **************************************************
 */

#include"IView.h"

/*
    �������ܣ������汳��
    �����������
    �����������
    ����ֵ����
*/
void IPlainView(FILE* fpHZ)
{
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IPlainView");
    }
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    settextstyle(1,0,2);

    setfillstyle(SOLID_FILL,255);
    bar(0+DF,0+DF,1024+DF,768+DF);
    setfillstyle(SOLID_FILL,84);
    bar(0+DF,0+DF,1024+DF,22+DF);
    setcolor(0);
    Iouttextxy(10+DF,5+DF,"��Windows��Դ������",fpHZ);

    setcolor(7);
    line(0+DF,44+DF,1024+DF,44+DF);
    line(0+DF,45+DF,1024+DF,45+DF);
    IPointerDown(1000+DF,32+DF);
    rectangle(152+DF,51+DF,824+DF,78+DF);
    line(803+DF,52+DF,803+DF,76+DF);
    rectangle(832+DF,51+DF,1017+DF,78+DF);
    line(851+DF,51+DF,851+DF,78+DF);
    line(0+DF,84+DF,1024+DF,84+DF);
    line(0+DF,85+DF,1024+DF,85+DF);
    IPointerRight(172+DF,62+DF);
    IRefresh(814+DF,64+DF);
    IMagnifier(841+DF,61+DF);
    IExit(1004+DF,8+DF);

    setcolor(7);
    line(240+DF,88+DF,240+DF,742+DF);
    line(0+DF,744+DF,1024+DF,744+DF);
}

/*
    �������ܣ���ര��
    ���������root�����ļ����ڵ�, curNode������ǰĿ¼����ָ��, nodeX���������ļ��ڵ�, top�����¼�ջ, (beginX,beginY)������ʼ����λ��, page����ҳ��, flag������־λ
    �����������
    ����ֵ���������ƫ����
*/
int IView0(IFileNode* root,IFileNodePointer ** curNode,IFileNodePointer* nodeX,IEventStackNode* top,int beginX,int beginY,char* page,char flag,FILE* fpHZ)
{
    int increaceY=0,temp,n;
    char thisPage=1;
    char tempStr[3];
    IEvent tempEvent;

    if(!root) return 0;         

    if(beginY<110+DF+600*(*page-1)||beginY>110+DF+600*(*page))
        thisPage=0;

    if(thisPage&&(*curNode)->child==root)
    {
        setfillstyle(SOLID_FILL,139);
        bar(0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22);
    }

    if(IisFolder(root))
    {
        if(!(root->flags&8))         //���ļ���
        {
            if(thisPage)
            {
                Ifolder(beginX+11,beginY-(*page-1)*600+4);
                setcolor(0);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,IEntreeActive,root,(IFileNode*)curNode,-1);
                IEventStackPush(top,tempEvent);
            }
            increaceY+=24;
        }
        else if(root->file.type[0]=='0')   //δ��
        {
            if(thisPage)
            {
                IPointerRight(beginX+1,beginY-(*page-1)*600+8);
                if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                    Idisk(beginX+11,beginY-(*page-1)*600+4);
                else
                    Ifolder(beginX+11,beginY-(*page-1)*600+4);
                setcolor(0);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,beginY-(*page-1)*600+14,2,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,beginY-(*page-1)*600+14,2,IEntreeActive,root,(IFileNode*)curNode,-1);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,IEntreeActive,root,(IFileNode*)curNode,-1);
                IEventStackPush(top,tempEvent);
            }
            increaceY+=24;
        }
        else        //�򿪵��ļ���
        {
            if(thisPage)
            {
                IPointerDown(beginX,beginY-(*page-1)*600+9);
                if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                    Idisk(beginX+11,beginY-(*page-1)*600+4);
                else
                    Ifolder(beginX+11,beginY-(*page-1)*600+4);
                setcolor(0);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,beginY-(*page-1)*600+14,2,IDetreeActive,root,(IFileNode*)curNode,6);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,beginY-(*page-1)*600+14,2,ISetXNull,root,(IFileNode*)nodeX,-1);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,IDetreeActive,root,(IFileNode*)curNode,6);
                IEventStackPush(top,tempEvent);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22,8,ISetXNull,root,(IFileNode*)nodeX,-1);
                IEventStackPush(top,tempEvent);
            }
            increaceY+=24;
            if(root->child)
            {
                increaceY+=IView0(root->child,curNode,nodeX,top,beginX+8,beginY+increaceY,page,0,fpHZ);
            }
        }
    }
    if(root->next)
    {
        increaceY+=IView0(root->next,curNode,nodeX,top,beginX,beginY+increaceY,page,0,fpHZ);
    }

    if(flag)
    {
        if(*page>1)
        {
            ISetEvent(&tempEvent,150+DF,720+DF,168+DF,738+DF,2,ILastPage,(IFileNode*)page,NULL,2);
            IEventStackPush(top,tempEvent);
            setcolor(0);
        }
        else
            setcolor(LIGHTGRAY);
        IGoLeft(150+DF,720+DF);
        if(*page<=((increaceY-24)/600))
        {
            ISetEvent(&tempEvent,210+DF,720+DF,228+DF,738+DF,2,INextPage,(IFileNode*)page,NULL,2);
            IEventStackPush(top,tempEvent);
            setcolor(0);
        }
        else
            setcolor(LIGHTGRAY);
        IGoRight(210+DF,720+DF);
        sprintf(tempStr,"%d",*page);
        setcolor(0);
        outtextxy(182+DF,722+DF,tempStr);
    }
    //ֻ��һ�����Ҽ�ͷ
    return increaceY;
}

/*
    �������ܣ��Ҳര��
    ���������curNode������ǰĿ¼����ָ��, nodeX���������ڵ�ָ�룬���ڱ��汻����/���еĽڵ�,top�����¼�ջ, (beginX,beginY)������ʼ����λ��, page����ҳ��, flag������־λ��fpHZ�������ֿ�ָ��
    �����������
    ����ֵ���������ƫ����
*/
int IView1(IFileNodePointer ** curNode,IFileNodePointer* nodeX,IEventStackNode* top,char* page,char* menuFlag,FILE* fpHZ)
{

    int i,numOfItem=0,numOfSelected=0;
    IFileNode* tempNode=NULL;
    IEvent tempEvent;
    char temp[150];

    settextstyle(0,0,0);
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IView1");
    }
    setcolor(0);

    tempNode=(*curNode)->child;
    IGetAbsolutePath(tempNode,temp);
    outtextxy(192+DF,61+DF,temp);
    //·��������ʾ

    ISetEvent(&tempEvent,803+DF,51+DF,824+DF,78+DF,2,INOP,NULL,NULL,6);
    IEventStackPush(top,tempEvent);
    //ˢ�¹���

    if(IFindParent((*curNode)->child))
    {
        setcolor(0);
        ISetEvent(&tempEvent,108+DF,57+DF,120+DF,76+DF,2,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,108+DF,57+DF,120+DF,76+DF,2,IEntreeActive,IFindParent((*curNode)->child),(IFileNode*)curNode,-1);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoUp(108+DF,57+DF);
    //������һ������

    if((*curNode)->pre&&(*curNode)->pre->child)
    {
        setcolor(0);
        ISetEvent(&tempEvent,25+DF,59+DF,40+DF,76+DF,2,IGoLeftActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoLeft(25+DF,60+DF);
    //������һĿ¼����

    if((*curNode)->next&&(*curNode)->next->child)
    {
        setcolor(0);
        ISetEvent(&tempEvent,62+DF,59+DF,92+DF,76+DF,2,IGoRightActive,(IFileNode*)curNode,NULL,6);
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoRight(62+DF,60+DF);
    //������һĿ¼����
        
    setcolor(0);
    setfillstyle(SOLID_FILL,255);
    bar(853+DF,52+DF,1016+DF,77+DF);
    if(!tempNode->child)
    {
        Iouttextxy(853+DF,61+DF,"������",fpHZ);
        if(!strcmp(tempNode->file.type,"0ds"))
            Iouttextxy(560+DF,240+DF,"������Ա�ɼ�",fpHZ);
        else
            Iouttextxy(530+DF,240+DF,"δ���ļ��л�δ����������",fpHZ);
    }
    else if(tempNode->file.type[1]=='\\')
        Iouttextxy(853+DF,61+DF,"��Ŀ¼�޷������ļ�",fpHZ);
    else
    {
        Iouttextxy(853+DF,61+DF,"�ڱ��ļ���������",fpHZ);
        ISetEvent(&tempEvent,853+DF,52+DF,1016+DF,77+DF,2,ISearchActive,(IFileNode*)(*curNode),NULL,8);
        IEventStackPush(top,tempEvent);
    }
    //��������ʾ
    
    tempNode=(*curNode)->child->child;
    while(tempNode)
    {
        numOfItem++;
        if(tempNode->flags&2)
            numOfSelected++;
        tempNode=tempNode->next;
    }
    //ͳ�����ļ����ͱ�ѡ�е��ļ���

    IView1PageControl(curNode,page,numOfItem);
    if(*page>=(numOfItem-1)/30+1)
        (*menuFlag)|=8;
    else
        (*menuFlag)&=119;
    //ҳ�����

    tempNode=(*curNode)->child->child;
    for(i=0;i<(*page-1)*(30);i++)
        tempNode=tempNode->next;
    //��ת����ǰҳ

    setfillstyle(SOLID_FILL,139);
    if((*menuFlag)&64)
    {
        bar(1001+DF,747+DF,1020+DF,766+DF);
        IView11(curNode,nodeX,tempNode,fpHZ,top,menuFlag);
        ISetEvent(&tempEvent,976+DF,747+DF,995+DF,766+DF,2,ISetView10,(IFileNode*)menuFlag,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    else
    {
        bar(976+DF,747+DF,995+DF,766+DF);
        IView10(curNode,nodeX,tempNode,fpHZ,top,menuFlag);
        ISetEvent(&tempEvent,1001+DF,747+DF,1020+DF,766+DF,2,ISetView11,(IFileNode*)menuFlag,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    //����ͼ����

    IDetailOption(980+DF,751+DF);
    IPictureOption(1005+DF,751+DF);
    
    sprintf(temp,"%d����Ŀ",numOfItem);
    Iouttextxy(16+DF,752+3+DF,temp,fpHZ);
    if(numOfSelected)
    {
        sprintf(temp,"ѡ��%d����Ŀ",numOfSelected);
        Iouttextxy(160+DF,752+3+DF,temp,fpHZ);
    }
    if((*menuFlag)&4)
    {
        setcolor(144);
        outtextxy(320+DF,752+DF,"CTRL");
    }
    //״̬��
    
    if((*menuFlag)&2)
    {
        (*menuFlag)&=125;
        setcolor(84);
        rectangle(412+DF,334+DF,662+DF,434+DF);
        setfillstyle(SOLID_FILL,84);
        bar(412+DF,334+DF,662+DF,356+DF);
        setfillstyle(SOLID_FILL,255);
        bar(413+DF,357+DF,661+DF,433+DF);
        rectangle(591+DF,403+DF,641+DF,423+DF);
        rectangle(521+DF,403+DF,571+DF,423+DF);

        setcolor(0);
        sprintf(temp,"%s%d%s","ȷ��Ҫɾ��ѡ�е�",numOfSelected,"����Ŀ��");
        Iouttextxy(433+DF,377+DF,temp,fpHZ);
        IPutsHZ16(530+DF,406+DF,"ȷ��",fpHZ);
        IPutsHZ16(600+DF,406+DF,"ȡ��",fpHZ);
        IWarningBeep();

        ISetEvent(&tempEvent,0+DF,0+DF,1024+DF,768+DF,2,INOP,NULL,NULL,0);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521+DF,403+DF,571+DF,423+DF,2,ISetDelete,(IFileNode*)(*curNode),(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591+DF,403+DF,641+DF,423+DF,2,INOP,NULL,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    else if((*menuFlag)&16)
    {
        (*menuFlag)&=79;
        setcolor(84);
        rectangle(412+DF,334+DF,662+DF,434+DF);
        setfillstyle(SOLID_FILL,84);
        bar(412+DF,334+DF,662+DF,356+DF);
        setfillstyle(SOLID_FILL,255);
        bar(413+DF,357+DF,661+DF,433+DF);
        rectangle(591+DF,403+DF,641+DF,423+DF);
        rectangle(521+DF,403+DF,571+DF,423+DF);

        setcolor(0);
        sprintf(temp,"%s","ȷ��Ҫ�����ļ���");
        Iouttextxy(433+DF,377+DF,temp,fpHZ);
        IPutsHZ16(530+DF,406+DF,"ȷ��",fpHZ);
        IPutsHZ16(600+DF,406+DF,"ȡ��",fpHZ);
        IWarningBeep();

        ISetEvent(&tempEvent,0+DF,0+DF,1024+DF,768+DF,2,INOP,NULL,NULL,0);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521+DF,403+DF,571+DF,423+DF,2,ISetPasteF,(IFileNode*)(*curNode),(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591+DF,403+DF,641+DF,423+DF,2,ISetPaste,(IFileNode*)(*curNode),(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
    }
    else if((*menuFlag)&32)
    {
        (*menuFlag)&=79;
        ISetEvent(&tempEvent,0,0,0,0,-1,ISetPaste,(IFileNode*)(*curNode),(IFileNode*)nodeX,6);
        IEventStackPush(top,tempEvent);
    }
    //ɾ��ȷ��

    return numOfSelected;
}

/*
    �������ܣ������ļ����ͣ���ͼ��
    ���������tempNode�����ļ��ڵ�, y��������λ��
    �����������
    ����ֵ����
*/
void IView10DrawIcon(IFileNode* tempNode,int y)
{
    if(tempNode->flags&2)
    {
        setfillstyle(SOLID_FILL,139);
        bar(248+DF,y,936+DF,y+19);
    }
    if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"txt"))
        Itxt(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"DOC")||!strcmp(tempNode->file.type,"doc"))
        Idoc(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"c")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"cpp"))
        Ic(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"h")||!strcmp(tempNode->file.type,"HPP")||!strcmp(tempNode->file.type,"hpp"))
        Ih(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"obj")||!strcmp(tempNode->file.type,"OBJ"))
        Iobj(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"exe")||!strcmp(tempNode->file.type,"EXE"))
        Iexe(256+DF,y+2);
    else if(!strcmp(tempNode->file.type,"jpg")||!strcmp(tempNode->file.type,"JPG")||!strcmp(tempNode->file.type,"bmp")||!strcmp(tempNode->file.type,"BMP"))
        Ipic(256+DF,y+2);
    else if(IisFolder(tempNode))
    {
        if(tempNode->file.type[1]=='d')
            Idisk(256+DF,y+2);
        else
            Ifolder(256+DF,y+2);
    }
    else
        Imystery(256+DF,y+2);
}

/*
    �������ܣ������ļ����ͣ���ͼ��
    ���������tempNode�����ļ��ڵ�, x��������λ��, y��������λ��
    �����������
    ����ֵ����
*/
void IView11DrawIcon(IFileNode* tempNode,int x,int y)
{
    if(tempNode->flags&2)
    {
        setfillstyle(SOLID_FILL,139);
        bar(x,y,x+99,y+109);
    }
    if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"txt"))
        ItxtL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"DOC")||!strcmp(tempNode->file.type,"doc"))
        IdocL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"c")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"cpp"))
        IcL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"h")||!strcmp(tempNode->file.type,"HPP")||!strcmp(tempNode->file.type,"hpp"))
        IhL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"obj")||!strcmp(tempNode->file.type,"OBJ"))
        IobjL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"exe")||!strcmp(tempNode->file.type,"EXE"))
        IexeL(x+25,y+10);
    else if(!strcmp(tempNode->file.type,"jpg")||!strcmp(tempNode->file.type,"JPG")||!strcmp(tempNode->file.type,"bmp")||!strcmp(tempNode->file.type,"BMP"))
        IpicL(x+25,y+10);
    else if(IisFolder(tempNode))
    {
        if(tempNode->file.type[1]=='d')
            IdiskL(x+25,y+10);
        else
            IfolderL(x+25,y+10);
    }
    else
        ImysteryL(x+25,y+10);
}

/*
    �������ܣ��Ҳര��(��ϸ��Ϣ)
    ���������curNode������ǰĿ¼����ָ��, nodeX���������ڵ�ָ�룬���ڱ��汻����/���еĽڵ�,top�����¼�ջ
    �����������
    ����ֵ����
*/
void IView10(IFileNodePointer ** curNode,IFileNodePointer* nodeX,IFileNode* tempNode,FILE* fpHZ,IEventStackNode* top,char* menuFlag)
{
    IEvent tempEvent;
    char temp[150];
    int y=116+DF;

    setcolor(50);
    IPutsHZ16(254+DF,94+DF,"�ļ���",fpHZ);
    IPutsHZ16(430+DF,94+DF,"�޸�����",fpHZ);
    IPutsHZ16(686+DF,94+DF,"����",fpHZ);
    IPutsHZ16(830+DF,94+DF,"��С",fpHZ);
    setcolor(247);
    line(424+DF,88+DF,424+DF,112+DF);
    line(680+DF,88+DF,680+DF,112+DF);
    line(824+DF,88+DF,824+DF,112+DF);
    line(936+DF,88+DF,936+DF,112+DF);
    //�ļ���ϸ��Ϣ�ı�ͷ

    while(tempNode)     //��ÿһ����ǰҳ����ļ�
    {
        IView10DrawIcon(tempNode,y);
        //�����ļ����ͣ���ͼ��

        setcolor(0);
        Iouttextxy(256+20+DF,y+6,tempNode->file.name,fpHZ);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,(tempNode->file.date%512)/32,tempNode->file.date%32,tempNode->file.time/2048,(tempNode->file.time%2048)/32);
        outtextxy(432+DF,y+6,temp);
        if(!IisFolder(tempNode))
        {
            settextjustify(2,2);
            if(tempNode->file.size<0)
                sprintf(temp,">32 MB",tempNode->file.size);
            else if(tempNode->file.size==0)
                sprintf(temp,"<1 KB",tempNode->file.size);
            else
                sprintf(temp,"%d KB",tempNode->file.size);
            outtextxy(928+DF,y+6,temp);
            settextjustify(0,2);
        }
        //�ļ���ϸ��Ϣ

        if((*menuFlag)&4)
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);
        //�����Ƿ�Ctrl,����ѡ������

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,8,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,8,IEntreeActive,tempNode,(IFileNode*)curNode,-1);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                Iouttextxy(688+DF,y+6+3,"����",fpHZ);
            else
                Iouttextxy(688+DF,y+6+3,"�ļ���",fpHZ);
        }
        else
        {
            outtextxy(688+DF,y+6,tempNode->file.type);
            if(!strcmp(tempNode->file.type,"EXE")||!strcmp(tempNode->file.type,"BAT"))
            {
                ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,8,IexeActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
            if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"ASM"))
            {
                ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,8,ItxtActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
        }
        //�ļ��򿪷�ʽ

        if(y>682+DF) break;
        y+=20;
        tempNode=tempNode->next;
    }
}

/*
    �������ܣ��Ҳര��(��ͼ��)
    ���������curNode������ǰĿ¼����ָ��, nodeX���������ڵ�ָ�룬���ڱ��汻����/���еĽڵ�,top�����¼�ջ
    �����������
    ����ֵ����
*/
void IView11(IFileNodePointer ** curNode,IFileNodePointer* nodeX,IFileNode* tempNode,FILE* fpHZ,IEventStackNode* top,char* menuFlag)
{
    IEvent tempEvent;
    char temp[150];
    int y=116+DF,x=276+DF;
    char num=0;

    while(tempNode)     //��ÿһ����ǰҳ����ļ�
    {
        num++;
        IView11DrawIcon(tempNode,x,y);
        //�����ļ����ͣ���ͼ��
        setcolor(0);
        Iouttextxy(x+50-strlen(tempNode->file.name)*4,y+95,tempNode->file.name,fpHZ);

        if((*menuFlag)&4)
            ISetEvent(&tempEvent,x,y,x+99,y+79,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,x,y,x+99,y+79,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);
        //�����Ƿ�Ctrl,����ѡ������

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,x,y,x+99,y+79,8,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,6);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,x,y,x+99,y+79,8,IEntreeActive,tempNode,(IFileNode*)curNode,-1);
            IEventStackPush(top,tempEvent);
        }
        else
        {
            if(!strcmp(tempNode->file.type,"EXE")||!strcmp(tempNode->file.type,"BAT"))
            {
                ISetEvent(&tempEvent,x,y,x+99,y+79,8,IexeActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
            if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"ASM"))
            {
                ISetEvent(&tempEvent,x,y,x+99,y+79,8,ItxtActive,tempNode,NULL,6);
                IEventStackPush(top,tempEvent);
            }
        }
        //�ļ��򿪷�ʽ

        if(num>=30) break;
        if(num%6)
            x+=102;
        else
        {
            y+=112;
            x=276+DF;
        }
        tempNode=tempNode->next;
    }
}
/*
    �������ܣ������ļ����ͣ���ͼ��
    ���������curNode������ǰĿ¼����ָ��, page����ҳ��, numOfItem������Ŀ����
    �����������
    ����ֵ����
*/
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem)
{
    static IFileNode* lastCurNode;
    char temp[3];
    
    if(lastCurNode!=(*curNode)->child)
        *page=1;
    else if((numOfItem-1)/30+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    lastCurNode=(*curNode)->child;
    //ҳ�����

    if(*page<(numOfItem-1)/30+1)
        setcolor(0);
    else
        setcolor(LIGHTGRAY);
    IGoRight(992+DF,720+DF);
    if(*page>1)
        setcolor(0);
    else
        setcolor(LIGHTGRAY);
    IGoLeft(928+DF,720+DF);
    sprintf(temp,"%d",*page);
    setcolor(0);
    outtextxy(962+DF,722+DF,temp);
}

/*
    �������ܣ������Һ����ʾ����
    ���������page����ҳ��, fpHZ�������ֿ�
    �����������
    ����ֵ����
*/
void IView2(char* page,FILE* fpHZ,IEventStackNode* top,IFileNodePointer** curNode)
{

    FILE* searched=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","r");
    char tempStr[150];
    IEvent tempEvent;
    char name[15];
    int y=120+DF,i,n,j=0,numOfsearched=0;

    setcolor(0);
    IGoLeft(250+DF,720+DF);
    Iouttextxy(270+DF,721+DF,"����",fpHZ);
    ISetEvent(&tempEvent,250+DF,720+DF,265+DF,735+DF,2,INOP,NULL,NULL,4);
    IEventStackPush(top,tempEvent);

    Iouttextxy(853+DF,61+DF,"�ڱ��ļ���������",fpHZ);
    ISetEvent(&tempEvent,853+DF,52+DF,1016+DF,77+DF,2,ISearchActive,(IFileNode*)(*curNode),NULL,8);
    IEventStackPush(top,tempEvent);
    //��������

    setcolor(50);
    IPutsHZ16(250+DF,94+DF,"ƥ���ļ���",fpHZ);
    IPutsHZ16(500+DF,94+DF,"����·��",fpHZ);


    while(fgets(tempStr,150,searched))
    {
        if(++numOfsearched>=120)
        {
            Iouttextxy(500+DF,753+DF,"ֻ��ʾǰ120��ƥ����",fpHZ);
            break;
        }
        //����������120��ƥ����
    }
    if((numOfsearched-1)/30+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    //ҳ�����
    
    rewind(searched);
    while(fgets(tempStr,150,searched)&&((++j)<=120))
    {
        if((j-1)/30+1<*page)
            continue;
        else if((j-1)/30+1>*page)
            continue;
        
        n=strlen(tempStr);
        if(tempStr[n-1]=='\n')
        {
            tempStr[n-1]='\0';
            n-=1;
        }
        IGetNameByPath(tempStr,name);

        setcolor(0);
        Iouttextxy(250+DF,y,name,fpHZ);
        Iouttextxy(500+DF,y,tempStr,fpHZ);

        y+=20;
    }
    if(!j)
        IPutsHZ16(530+DF,240+DF,"δ��⵽ƥ����",fpHZ);
    //δ�������ļ�
    else
    {
        if(*page>1)
            setcolor(0);
        else
            setcolor(LIGHTGRAY);
        IGoLeft(928+DF,720+DF);
        if(*page<(j-2)/30+1)
            setcolor(0);
        else
            setcolor(LIGHTGRAY);
        IGoRight(992+DF,720+DF);
        sprintf(tempStr,"%d",*page);
        setcolor(0);
        outtextxy(962+DF,722+DF,tempStr);
    }
    //�������ļ�

    fclose(searched);
}
