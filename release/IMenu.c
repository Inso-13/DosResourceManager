/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵������˵���صĲ��ֺ���
*/


#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<DOS.H>
#include<BIOS.H>
#include<CONIO.H>
#include<GRAPHICS.H>
#include"IEvent.h"
#include"IUtility.h"
#include"ISound.h"
#include"IHanZi.h"
#include"IDiry.h"
#include"ISort.h"
#include"IView.h"
#include"IActive.h"
#include"IMenu.h"

/*
    �������ܣ���View1�м���һ���˵�
    ���������(mouseX,mouseY)��������λ��, numOfSelected������ǰ·���б�ѡ�е��ļ���, top����View1���¼�ջ, curNode������ǰ�ڵ�,nodeX���������ڵ�ָ��, menuFlag�����˵��ı�־(bit0 �Ƿ�Ϊ����˵�,bit1 �Ƿ���ɾ��ȷ�ϴ���,bit2 �Ƿ���Ctrl, bit3 �Ƿ������һҳ), fpHZ�������ֿ��ļ�
    �����������
    ����ֵ����
*/
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer* curNode,IFileNodePointer* nodeX,char *menuFlag,FILE* fpHZ)
{
    IEvent tempEvent;
    int i;
    int (*lambda[8])(IFileNode*,IFileNode*)={ISortDateUp,ISortDateDown,ISortSizeUp,ISortSizeDown,ISortNameUp,ISortNameDown,ISortTypeUp,ISortTypeDown};  
    //������ָ������

    if(mouseX>928) mouseX=928;
    if(mouseY>607) mouseY=607;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX,*menuFlag,fpHZ);
    //���˵�

    if(!((*menuFlag)&1))
    {
        if(curNode->child->file.type[1]=='\\')
            return;
        if((*menuFlag)&8)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*5,mouseX+80,mouseY+19+20*5,2,ISetNewFile,(IFileNode*)curNode,NULL,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*6,mouseX+80,mouseY+19+20*6,2,ISetNewFolder,(IFileNode*)curNode,NULL,6);
            IEventStackPush(top,tempEvent);
        }
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*7,mouseX+80,mouseY+19+20*7,2,ISortMenuActive,(IFileNode*)menuFlag,NULL,4);
        IEventStackPush(top,tempEvent);
        if(numOfSelected)
        {
            if(numOfSelected==1)
            {
                ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*4,mouseX+80,mouseY+19+20*4,2,ISetRename,(IFileNode*)curNode,NULL,4);
                IEventStackPush(top,tempEvent);
            }
            ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+80,mouseY+19,2,ISetCopy,(IFileNode*)curNode,(IFileNode*)nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*1,mouseX+80,mouseY+19+20*1,2,ISetCut,(IFileNode*)curNode,(IFileNode*)nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*2,mouseX+80,mouseY+19+20*2,2,ISetDeleteComfirm,(IFileNode*)menuFlag,NULL,4);
            IEventStackPush(top,tempEvent);
        }
        if(!numOfSelected||(curNode->child==nodeX->child))
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*3,mouseX+80,mouseY+19+20*3,2,ISetPaste,(IFileNode*)curNode,(IFileNode*)nodeX,6);
            IEventStackPush(top,tempEvent);
        }
    }
    //�����һ���˵�
    else
    {
        for(i=0;i<8;i++)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*i,mouseX+80,mouseY+19+20*i,2,ISortActive,(IFileNode*)curNode,(IFileNode*)lambda[i],4);
            IEventStackPush(top,tempEvent);
        }
        (*menuFlag)&=14;
    }
    //����Ƕ�������˵�
}

/*
    �������ܣ���View1�л��˵�
    ���������(x,y)�������˵������Ͻ�, numOfSelected������ǰ·���б�ѡ�е��ļ���, curNode������ǰ�ڵ�,nodeX���������ڵ�ָ��, menuFlag�����˵��ı�־(bit0 �Ƿ�Ϊ����˵�,bit1 �Ƿ���ɾ��ȷ�ϴ���, bit2 �Ƿ���Ctrl, bit3�Ƿ������һҳ), fpHZ�������ֿ��ļ�
    �����������
    ����ֵ����
*/
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,char menuFlag,FILE* fpHZ)
{
    int i;
    unsigned char str[2][8][11]={{"����","����","ɾ��","ճ��","������","���ļ�","���ļ���","����.."},{"����������","�����ڽ���","����С����","����С����","����������","�����ƽ���","����������","�����ͽ���"}};
    if(fpHZ==NULL)
    {
        setcolor(0);
        outtextxy(100,100,"fpHZ is NULL in IDrawMenu");
    }
    setfillstyle(SOLID_FILL,255);
    bar(x,y,x+95,y+160);
    setcolor(15);
    rectangle(x,y,x+95,y+160);

    for(i=1;i<8;i++)
        line(x+1,y+20*i,x+94,y+20*i);
    if(!(menuFlag&1))
    { 
        if(curNode->child->file.type[1]=='\\')
            setcolor(247);
        Iouttextxy(x+3,y+20*7+6,str[0][7],fpHZ);
        if(curNode->child->file.type[1]=='\\'||!(menuFlag&8))
            setcolor(247);
        else
            setcolor(15);
        IPutsHZ16(x+3,y+20*5+3,str[0][5],fpHZ);
        IPutsHZ16(x+3,y+20*6+3,str[0][6],fpHZ);
        
        if(!numOfSelected)
            setcolor(247);
        else
            setcolor(15);
        for(i=0;i<3;i++)
            IPutsHZ16(x+3,y+20*i+3,str[0][i],fpHZ);    

        if((!numOfSelected||curNode->child==nodeX->child)&&nodeX->child&&curNode->child->file.type[1]!='\\')
            setcolor(15);
        else
            setcolor(247);
        IPutsHZ16(x+3,y+3+20*3,str[0][3],fpHZ);
        if(numOfSelected==1&&curNode->child->file.type[1]!='\\')
            setcolor(15);
        else
            setcolor(247);
        IPutsHZ16(x+3,y+4*20+3,str[0][4],fpHZ);       
    }
    else
    {
        setcolor(15);
        for(i=0;i<8;i++)
        {
            IPutsHZ16(x+3,y+20*i+3,str[1][i],fpHZ);    
        }
    }
}

/*
    �������ܣ�����ƺ���
    ���������cur������ǰ�ڵ�
    ���������X���������ڵ�ָ�룬���ڱ��汻���ƵĽڵ�
    ����ֵ����
*/
void ISetCopy(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    //���֮ǰ�б����Ƶ��ļ��ڵ㣬�򸲸�֮
    
    nodeX->child=curNode->child;
    nodeX->child->flags&=30;
}

/*
    �������ܣ�������к���
    ���������cur������ǰ�ڵ�
    ���������X���������ڵ�ָ�룬���ڱ��汻���еĽڵ�
    ����ֵ����
*/
void ISetCut(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    //���֮ǰ�б����Ƶ��ļ��ڵ㣬�򸲸�֮

    nodeX->child=curNode->child;
    nodeX->child->flags|=1;
    //���ָ��ƺͼ���
}

/*
    �������ܣ�����ճ������
    ���������cur������ǰ�ڵ�
    ���������X���������ڵ�ָ�룬���ڱ��汻����/���еĽڵ�
    ����ֵ����
*/
void ISetPaste(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    Icplr(nodeX->child,curNode->child);
    //�����ļ��ڵ�

    if(nodeX->child->flags&1)
        Irmlr(nodeX->child);
    //����Ǽ��У���ɾ��Դ�ļ��ڵ�
}

/*
    �������ܣ�����ɾ������
    ���������cur������ǰ�ڵ�
    ���������X���������ڵ�ָ�룬���ڱ��汻����/���еĽڵ�
    ����ֵ����
*/
void ISetDelete(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    nodeX->child=NULL;
    //�����ڵ�����

    Irmlr(curNode->child);
    //����ɾ������
}

/*
    �������ܣ�����ɾ������
    ���������flagx�����˵�״̬λ, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null)
{
    char* flag=(char*)flagx;
    (*flag)|=2;
    //����ȷ��ɾ������
}

/*
    �������ܣ���������������
    ���������cur������ǰ�ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetRename(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(!(tempNode->flags&2))
    {
        i++;
        tempNode=tempNode->next;
    }
    i=i%30;
    //�ҵ���ѡ�е��ļ��ڵ�
    
    strcpy(temp,tempNode->file.name);
    IGetString(254,110+20*i,150,temp,0);
    //��ȡ���ļ���

    if(temp[0])
        Irename(tempNode,temp);
}

/*
    �������ܣ���������ļ�����
    ���������cur������ǰ�ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetNewFile(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    i=i%30;
    if(!i) i=30;
    //�ҵ���ѡ�е��ļ��ڵ�

    IGetString(254,110+20*i,150,temp,4);
    //��ȡ���ļ���

    if(temp[0])
        if(!Inew(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            IWarningBeep();
            delay(1500);
        }
        //��������ļ�ʧ��
}

/*
    �������ܣ���������ļ��к���
    ���������cur������ǰ�ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetNewFolder(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNode* tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    i=i%30;
    if(!i) i=30;
    //�ҵ���ѡ�е��ļ��ڵ�

    IGetString(254,110+20*i,150,temp,4);
    //��ȡ���ļ���

    if(temp[0])
        if(!Imkdir(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            IWarningBeep();
            delay(1500);
        }
        //��������ļ���ʧ��
}