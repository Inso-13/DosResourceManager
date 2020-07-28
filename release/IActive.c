#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<BIOS.H>
#include<CONIO.H>
#include"IEvent.h"
#include"IView.h"
#include"IUtility.h"
#include"IDiry.h"
#include"IActive.h"
#include"IInit.h"
#include"IHanZi.h"

void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * oldCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));
    IFileNodePointer * tempNode,*nextNode;

    tempNode=curNode->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }

    oldCurNode->child=curNode->child;
    oldCurNode->wait=curNode->wait;
    oldCurNode->child->del=curNode->child->del;
    oldCurNode->pre=curNode->pre;
    curNode->wait=15;
    if(curNode->pre)
    {
        curNode->pre->next=oldCurNode;
    }
    curNode->pre=oldCurNode;
    oldCurNode->next=curNode;

    IEntree(node);
    
    curNode->child=node;
    tempNode=curNode->pre;
    while(tempNode)
    {
        tempNode->wait--;
        if(tempNode->wait<0&&!tempNode->child->del)
        {
            if(tempNode->pre)
            {
                tempNode=tempNode->pre;
                tempNode->next=tempNode->next->next;
                free(tempNode->next);
                tempNode->next->pre=tempNode;
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        else
            tempNode=tempNode->pre;
    }
    tempNode=curNode->pre;
}
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer * oldCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * tempNode,*lastNode,*nextNode;

    tempNode=curNode->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    oldCurNode->child=curNode->child;
    oldCurNode->wait=curNode->wait;
    oldCurNode->child->del=curNode->child->del;
    oldCurNode->pre=curNode->pre;
    curNode->wait=15;
    if(curNode->pre)
    {
        curNode->pre->next=oldCurNode;
    }
    curNode->pre=oldCurNode;
    oldCurNode->next=curNode;    
    curNode->child=node;

    node->file.type[0]='0';
    tempNode=curNode;
    if(!tempNode->child->del)
    {
        tempNode->child->file.type[0]='1';
        IDetree(node);
    }
    while(tempNode)
    {
        lastNode=tempNode->pre;
        if(tempNode->child->del==-1&&tempNode->child->file.type[0]=='0')
        {
            tempNode->child->file.type[0]='1';
            IDetree(tempNode->child);
        }
        tempNode=lastNode;
    }
}
void ISelect(IFileNode* node,IFileNode* null)
{
    IFileNode* tempNode=IFindParent(node)->child;
    while(tempNode)
    {
        tempNode->flags&=29;
        tempNode=tempNode->next;
    }
    node->flags|=2;
}
void ICtrlSelect(IFileNode* node,IFileNode* null)
{
    if(!(node->flags&2))
        node->flags|=2;
    else
        node->flags&=5;
}
void INOP(IFileNode* null1,IFileNode* null2){}
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer * curNode,IFileNodePointer * nodeX,int *menuFlag,char *delFlag)
{
    IEvent tempEvent;
    int i;
    int (*lambda[8])(IFileNode*,IFileNode*)={ISortDateUp,ISortDateDown,ISortSizeUp,ISortSizeDown,ISortNameUp,ISortNameDown,ISortTypeUp,ISortTypeDown};

    if(mouseX>944) mouseX=944;
    if(mouseY>608) mouseY=608;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX,*menuFlag);
    if(*menuFlag==0)
    {
        if(curNode->child->file.type[1]=='\\')
            return;
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*5,mouseX+80,mouseY+19+20*5,2,ISetNewFile,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*6,mouseX+80,mouseY+19+20*6,2,ISetNewFolder,curNode,nodeX,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*7,mouseX+80,mouseY+19+20*7,2,ISortMenuActive,menuFlag,NULL,4);
        IEventStackPush(top,tempEvent);
        if(numOfSelected)
        {
            if(numOfSelected==1)
            {
                ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*4,mouseX+80,mouseY+19+20*4,2,ISetRename,curNode,NULL,4);
                IEventStackPush(top,tempEvent);
            }
            ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+80,mouseY+19,2,ISetCopy,curNode,nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*1,mouseX+80,mouseY+19+20*1,2,ISetCut,curNode,nodeX,4);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*2,mouseX+80,mouseY+19+20*2,2,ISetDeleteComfirm,delFlag,NULL,4);
            IEventStackPush(top,tempEvent);
        }
        if(!numOfSelected||(curNode->child==nodeX->child))
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*3,mouseX+80,mouseY+19+20*3,2,ISetPaste,curNode,nodeX,6);
            IEventStackPush(top,tempEvent);
        }
    }
    else
    {
        for(i=0;i<8;i++)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*i,mouseX+80,mouseY+19+20*i,2,ISortActive,curNode,lambda[i],4);
            IEventStackPush(top,tempEvent);
        }
        *menuFlag=0;
    }
}
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,int menuFlag)
{
    int i;
    FILE* fpHZ=fopen("C:\\DOSRES\\SRC\\HZ16","rb");
    char str[2][8][11]={{"复制","剪切","删除","粘贴","重命名","新文件","新文件夹","排序.."},{"按日期升序","按日期降序","按大小升序","按大小降序","按名称升序","按名称降序","按类型升序","按类型降序"}};
    setfillstyle(SOLID_FILL,255);
    bar(x,y,x+95,y+160);
    setcolor(15);
    rectangle(x,y,x+95,y+160);

    for(i=1;i<8;i++)
        line(x+1,y+20*i,x+94,y+20*i);
    if(!menuFlag)
    { 
        if(curNode->child->file.type[1]=='\\')
            setcolor(247);
        IPutsHZ16(x+3,y+20*5+3,str[0][5],fpHZ);
        IPutsHZ16(x+3,y+20*6+3,str[0][6],fpHZ);
        Iouttextxy(x+3,y+20*7+6,str[0][7],fpHZ);
        for(i=0;i<3;i++)
        {
            if(!numOfSelected)
                setcolor(247);
            IPutsHZ16(x+3,y+20*i+3,str[0][i],fpHZ);    
        }
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
    fclose(fpHZ);
}
void ISetCopy(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=curNode;

    while(tempNode)
    {
        if(tempNode->child->del==1)
            tempNode->child->del=-1;
        tempNode=tempNode->pre;
    }
    curNode->child->del=1;
    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    
    nodeX->child=curNode->child;
}
void ISetCut(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=curNode;

    while(tempNode)
    {
        if(tempNode->child->del==1)
            tempNode->child->del=-1;
        tempNode=tempNode->pre;
    }
    curNode->child->del=1;
    if(nodeX->child)
    {
        if(nodeX->child->flags&1)
            nodeX->child->flags&=30;
    }
    nodeX->child=curNode->child;
    nodeX->child->flags|=1;
}
void ISetPaste(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    Icplr(nodeX->child,curNode->child);
    if(nodeX->child->flags&1)
        Irmlr(nodeX->child,NULL);
}
void ISetDelete(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;

    Irmlr(curNode->child,NULL);
}
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null)
{
    char* flag=(char*)flagx;
    *flag=1;
}
void IGoLeftActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;
}
void IGoRightActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;
}
char* IGetString(int x,int y,int length,char* string,int flag)
{
    char* org=string;
    char temp[20];
    char tempChar='\0';
    int i=0,n=0,t=0;

    setcolor(0);
    rectangle(x-1,y,x+length+1,y+27);
    strcpy(string,"\0");
    setfillstyle(SOLID_FILL,255);
    bar(x,y+1,x+length,y+26);

    while(1)
    {
        while(!kbhit())
        {
            if(t>0)
            {
                setcolor(144);
            }
            else
            {
                setcolor(255);
            }
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            t++;
        }
        bar(x,y+1,x+length,y+26);
        tempChar=getch();

        if(tempChar=='\r')
            break;
        else if(tempChar=='\b')
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //????????
                i--;
            else if(tempChar=='M'&&n>i)    //?????????
                i++;
            else
            {
                getch();
                tempChar=getch();
                continue;
            }
        }
        else if(n<12&&((tempChar>='0'&&tempChar<='9')||(tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||tempChar=='_'||(flag&&(tempChar=='?'||tempChar=='*'))))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        setcolor(144);
        bar(x,y+1,x+length,y+26);
        outtextxy(x+2,y+9,string);

    }
    return org;
}
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
    IGetString(254,110+20*i,150,temp,0);
    if(temp[0])
        Irename(tempNode,temp);
}
void ISearchActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    char temp[20];

    IGetString(851,51,166,temp,1);
    if(temp[0])
        ISearch(curNode->child,temp);
}
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
    IGetString(156,73+13*i,100,temp,0);
    if(temp[0])
        Inew(curNode->child,temp);
}
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
    IGetString(156,73+13*i,100,temp,0);
    if(temp[0])
        Imkdir(curNode->child,temp);
}
void IexeActive(IFileNode* exe,IFileNode* null)
{
    char temp[50];
    setfillstyle(SOLID_FILL,0);
    bar(0,0,1024,768);
    IGetAbsolutePath(exe,temp);
    system(temp);
    IPlainView();
}
void ItxtActive(IFileNode* txt,IFileNode* null)
{
    char temp[50];
    strcpy(temp,"BC ");
    IGetAbsolutePath(txt,temp+3);
    SVGA_Deinit();
    system(temp);
}
void ISortMenuActive(IFileNode* flag,IFileNode* null)
{
    int *n=(int*) flag;
    *n=1;
}
void ISortActive(IFileNode* cur,IFileNode* pfun)
{
    IFileNodePointer* curNode=(IFileNodePointer*)cur;
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;
    if(curNode->child->child)
        ISort(curNode->child,fun);
}
