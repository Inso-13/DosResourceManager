#include<GRAPHICS.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include"IEvent.h"
#include"IView.h"
#include"IUtility.h"
#include"IDiry.h"

void IPointerRight(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+2,y+2);
    line(x+1,y,x+3,y+2);
    line(x,y+4,x+1,y+3);
    line(x+1,y+4,x+2,y+3);
}
void IPointerDown(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+2,y+2);
    line(x,y+1,x+2,y+3);
    line(x+4,y,x+3,y+1);
    line(x+4,y+1,x+3,y+2);
}
void IGoLeft(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+2,y,x,y+2);
    line(x+2,y+5,x,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoRight(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+3,y,x+5,y+2);
    line(x+3,y+5,x+5,y+3);
    line(x,y+2,x+5,y+2);
    line(x,y+3,x+5,y+3);
}
void IGoUp(int x,int y)
{
    setcolor(DARKGRAY);
    line(x+2,y,x,y+2);
    line(x+2,y+1,x,y+3);
    line(x+3,y+1,x+4,y+2);
    line(x+3,y+2,x+4,y+3);
    line(x+2,y+2,x+2,y+7);
}
void IRefresh(int centerX,int centerY)
{
    setcolor(DARKGRAY);
    arc(centerX,centerY,0,45,3);
    arc(centerX,centerY,110,180,3);
    arc(centerX,centerY+1,180,360,3);
    line(centerX-2,centerY-3,centerX-3,centerY-3);
    putpixel(centerX-1,centerY-1,DARKGRAY);
}
void IMagnifier(int x,int y)
{
    setcolor(DARKGRAY);
    circle(x+2,y+2,2);
    circle(x+2,y+2,3);
    line(x,y+4,x-2,y+6);
    line(x,y+5,x-2,y+7);
}
void IDetailOption(int x,int y)
{
    setcolor(DARKGRAY);
    line(x,y,x+6,y);
    line(x,y+1,x+6,y+1);
    line(x,y+3,x+6,y+3);
    line(x,y+5,x+6,y+5);
    line(x,y+6,x+6,y+6);
    putpixel(x+1,y+1,BLUE);
    putpixel(x+1,y+3,YELLOW);
    putpixel(x+1,y+5,RED);
}
void IPictureOption(int x,int y)
{
    setcolor(DARKGRAY);
    rectangle(x,y,x+6,y+6);
    setcolor(BLUE);
    line(x+1,y+1,x+5,y+1);
    line(x+3,y+1,x+5,y+1);
    setcolor(GREEN);
    line(x+1,y+3,x+2,y+3);
    line(x+1,y+4,x+5,y+4);
    line(x+1,y+5,x+5,y+5);
}
void IExit(int x,int y)
{
    setcolor(WHITE);
    line(x,y,x+4,y+4);
    line(x,y+4,x+4,y);
}
void IPlainView()
{
    FILE *fpHZ;

    fpHZ=fopen("HZ16","rb");

    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    setbkcolor(WHITE);
    settextstyle(0,0,1);

    cleardevice();
    setfillstyle(1,DARKGRAY);
    bar(0,0,640,14);
    setcolor(LIGHTGRAY);
    line(0,28,640,28);
    line(0,29,640,29);
    IPointerDown(625,20);
    rectangle(45,32,565,49);
    line(552,33,552,48);
    rectangle(570,32,636,49);
    IPointerDown(544,40);
    line(0,53,640,53);
    line(0,54,640,54);
    IPointerRight(58,39);
    IGoLeft(6,38);
    IGoRight(19,38);
    IPointerDown(29,39);
    IGoUp(38,37);
    IRefresh(559,40);
    IMagnifier(576,37);
    outtextxy(585,37,"search");
    IDetailOption(622,470);
    IPictureOption(631,470);
    IExit(628,5);

    setcolor(LIGHTGRAY);
    line(150,55,150,464);
    line(0,465,640,465);
    fclose(fpHZ);
}
int IView0(IFileNode* root,IFileNode** curNode,IEventStackNode* top,int beginX,int beginY)
{
    int increaceY=0,temp;
    IEvent tempEvent;

    if(!root) return 0;         //如果为空指针
    if(!IisFolder(root)) return 0;      //如果不是文件夹
    if(beginY>450) return 0;
    if(*curNode==root)
    {
        setfillstyle(SOLID_FILL,LIGHTGRAY);
        bar(0,beginY,149,beginY+14);
    }
    if(root->hasFolder==0&&root->hasFile==0)         //如果无子文件夹和子文件
    {
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
    }
    else if(root->file.type[0]=='0')   //如果是未打开的文件夹
    {
        IPointerRight(beginX+1,beginY+5);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,beginX,beginY+4,beginX+10,beginY+9,2,IEntreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,149,beginY+14,8,IEntreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
    }
    else        //如果是打开的文件夹
    {
        IPointerDown(beginX,beginY+6);
        outtextxy(beginX+16,beginY+4,root->file.name);
        increaceY+=15;
        ISetEvent(&tempEvent,beginX,beginY+4,beginX+10,beginY+9,2,IDetreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,0,beginY,149,beginY+14,8,IDetreeActive,root,curNode,6);
        IEventStackPush(top,tempEvent);
        if(root->child)
        {
            increaceY+=IView0(root->child,curNode,top,beginX+5,beginY+increaceY);
        }
    }
    if(root->next)
    {
        increaceY+=IView0(root->next,curNode,top,beginX,beginY+increaceY);
    }
    return increaceY;
}
int IView1(IFileNode** curNode,IEventStackNode* top,char isCtrl)
{
    static int numOfCtrl,lastCtrl;
    int y,numOfItem=0,numOfSelected=0;
    IFileNode* tempNode;
    IEvent tempEvent;
    char temp[50];

    setcolor(BLUE);
    outtextxy(160,60,"Name");
    outtextxy(270,60,"Mod Time");
    outtextxy(430,60,"Type");
    outtextxy(520,60,"Size");
    setcolor(LIGHTGRAY);
    line(265,55,265,70);
    line(425,55,425,70);
    line(515,55,515,70);
    line(585,55,585,70);
    setcolor(DARKGRAY);

    tempNode=(*curNode);
    
    IGetAbsolutePath(tempNode,temp);
    outtextxy(70,38,temp);
    ISetEvent(&tempEvent,553,32,635,49,2,INOP,NULL,NULL,6);
    IEventStackPush(top,tempEvent);

    if(isCtrl&&!lastCtrl) numOfCtrl++;
    lastCtrl=isCtrl;
    if(!tempNode->child)
    {
        outtextxy(350,150,"Nothing detected");
        return 0;
    }
    tempNode=tempNode->child;
    y=73;
    while(tempNode)
    {
        if(tempNode->flags&2)
        {
            setfillstyle(SOLID_FILL,LIGHTGRAY);
            bar(155,y,585,y+12);
            numOfSelected++;
        }

        outtextxy(160,y+4,tempNode->file.name);
        sprintf(temp,"%d/%d/%d %02d:%02d",tempNode->file.date/512+1980,(tempNode->file.date%512)/32,tempNode->file.date%32,tempNode->file.time/2048,(tempNode->file.time%2048)/32);
        outtextxy(270,y+4,temp);

        if(numOfCtrl%2)
            ISetEvent(&tempEvent,155,y,585,y+12,2,ICtrlSelect,tempNode,NULL,4);
        else
            ISetEvent(&tempEvent,155,y,585,y+12,2,ISelect,tempNode,NULL,4);
        IEventStackPush(top,tempEvent);

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,155,y,585,y+12,8,IEntreeActive,tempNode,curNode,6);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                outtextxy(430,y+4,"Disk");
            else
                outtextxy(430,y+4,"Folder");
        }
        else outtextxy(430,y+4,tempNode->file.type);
        if(!IisFolder(tempNode))
        {
            settextjustify(2,2);
            sprintf(temp,"%d KB",tempNode->file.size);
            outtextxy(580,y+4,temp);
            settextjustify(0,2);
        }
        if(y>440) break;
        y+=13;
        numOfItem++;
        tempNode=tempNode->next;
    }
    sprintf(temp,"%d items",numOfItem);
    outtextxy(10,470,temp);
    if(numOfSelected)
    {
        sprintf(temp,"%d selected",numOfSelected);
        outtextxy(100,470,temp);
    }
    if(numOfCtrl%2)
    {
        setcolor(RED);
        outtextxy(200,470,"CTRL");
    }
    return numOfSelected;
}

void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNode** curNode=(IFileNode**)cur;
    IEntree(node,0);
    
    *curNode=node;
}
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNode** curNode=(IFileNode**)cur;
    //IDetree(node,0);   
    if(!node) return;
    if(node->file.type[1]=='\\')
    {
        node->file.type[0]='0';
        return;
    }
    if(!IisFolder(node)) return;
    node->file.type[0]='0';
    *curNode=node;
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
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNode** curNode,IFileNode** nodeX)
{
    IEvent tempEvent;
    if(mouseX>590) mouseX=590;
    if(mouseY>380) mouseY=380;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX);
    if(numOfSelected)
    {
        // if(numOfSelected==1)
        // {
        //     ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*4,mouseX+54,mouseY+14+15*4,2,ISetRename,null,null,4);
        //     IEventStackPush(top,tempEvent);
        // }
        ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+54,mouseY+14,2,ISetCopy,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*1,mouseX+54,mouseY+14+15*1,2,ISetCut,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*2,mouseX+54,mouseY+14+15*2,2,ISetDelete,curNode,NULL,4);
        IEventStackPush(top,tempEvent);
    }
    if(!numOfSelected||((*curNode)==(*nodeX)))
    {
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+15*3,mouseX+54,mouseY+14+15*3,2,ISetPaste,curNode,nodeX,4);
        IEventStackPush(top,tempEvent);
    }
}
void IDrawMenu(int x,int y,int numOfSelected,IFileNode** curNode,IFileNode** nodeX)
{
    int i;
    char str[5][7]={"copy","cut","delete","paste","rename"};
    setcolor(BLUE);
    rectangle(x,y,x+55,y+75);
    for(i=1;i<5;i++)
        line(x+1,y+15*i,x+54,y+15*i);
    for(i=0;i<3;i++)
    {
        if(!numOfSelected)
            setcolor(LIGHTGRAY);
        outtextxy(x+3,y+15*i+3,str[i]);    
    }
    if((!numOfSelected||(*curNode)==(*nodeX))&&(*nodeX))
        setcolor(BLUE);
    else
        setcolor(LIGHTGRAY);
    outtextxy(x+3,y+48,str[3]);
    if(numOfSelected==1)
        setcolor(BLUE);
    else
        setcolor(LIGHTGRAY);
    outtextxy(x+3,y+63,str[4]);        
}
void ISetCopy(IFileNode* cur,IFileNode* X)
{
    IFileNode** curNode=(IFileNode**)cur;
    IFileNode** nodeX=(IFileNode**)X;
    if(*nodeX)
    {
        if((*nodeX)->flags&1)
            (*nodeX)->flags&=30;
    }
    *nodeX=*curNode;
}
void ISetCut(IFileNode* cur,IFileNode* X)
{
    IFileNode** curNode=(IFileNode**)cur;
    IFileNode** nodeX=(IFileNode**)X;
    
    *nodeX=*curNode;
    (*nodeX)->flags|=1;
}
void ISetPaste(IFileNode* cur,IFileNode* X)
{
    IFileNode** curNode=(IFileNode**)cur;
    IFileNode** nodeX=(IFileNode**)X;

    Icplr(*nodeX,*curNode);
    if((*nodeX)->flags&1)
        Irmlr(*nodeX,NULL);
}
void ISetDelete(IFileNode* cur,IFileNode* null)
{
    IFileNode** curNode=(IFileNode**)cur;
    
    Irmlr(*curNode,NULL);
}