/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：与菜单相关的部分函数
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
    函数功能：在View1中激活一级菜单
    输入参数：(mouseX,mouseY)——鼠标的位置, numOfSelected——当前路径中被选中的文件数, top——View1的事件栈, curNode——当前节点,nodeX——辅助节点指针, menuFlag——菜单的标志(bit0 是否为二层菜单,bit1 是否有删除确认窗口,bit2 是否按下Ctrl, bit3 是否是最后一页), fpHZ——汉字库文件
    输出参数：无
    返回值：无
*/
void IMenu(int mouseX,int mouseY,int numOfSelected,IEventStackNode* top,IFileNodePointer* curNode,IFileNodePointer* nodeX,char *menuFlag,FILE* fpHZ)
{
    IEvent tempEvent;
    int i;
    int (*lambda[8])(IFileNode*,IFileNode*)={ISortDateUp,ISortDateDown,ISortSizeUp,ISortSizeDown,ISortNameUp,ISortNameDown,ISortTypeUp,ISortTypeDown};  
    //排序函数指针数组

    if(mouseX>928) mouseX=928;
    if(mouseY>607) mouseY=607;
    IDrawMenu(mouseX,mouseY,numOfSelected,curNode,nodeX,*menuFlag,fpHZ);
    //画菜单

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
    //如果是一级菜单
    else
    {
        for(i=0;i<8;i++)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*i,mouseX+80,mouseY+19+20*i,2,ISortActive,(IFileNode*)curNode,(IFileNode*)lambda[i],4);
            IEventStackPush(top,tempEvent);
        }
        (*menuFlag)&=14;
    }
    //如果是二级排序菜单
}

/*
    函数功能：在View1中画菜单
    输入参数：(x,y)——画菜单的左上角, numOfSelected——当前路径中被选中的文件数, curNode——当前节点,nodeX——辅助节点指针, menuFlag——菜单的标志(bit0 是否为二层菜单,bit1 是否有删除确认窗口, bit2 是否按下Ctrl, bit3是否是最后一页), fpHZ——汉字库文件
    输出参数：无
    返回值：无
*/
void IDrawMenu(int x,int y,int numOfSelected,IFileNodePointer * curNode,IFileNodePointer * nodeX,char menuFlag,FILE* fpHZ)
{
    int i;
    unsigned char str[2][8][11]={{"复制","剪切","删除","粘贴","重命名","新文件","新文件夹","排序.."},{"按日期升序","按日期降序","按大小升序","按大小降序","按名称升序","按名称降序","按类型升序","按类型降序"}};
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
    函数功能：激活复制函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制的节点
    返回值：无
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
    //如果之前有被复制的文件节点，则覆盖之
    
    nodeX->child=curNode->child;
    nodeX->child->flags&=30;
}

/*
    函数功能：激活剪切函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被剪切的节点
    返回值：无
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
    //如果之前有被复制的文件节点，则覆盖之

    nodeX->child=curNode->child;
    nodeX->child->flags|=1;
    //区分复制和剪切
}

/*
    函数功能：激活粘贴函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制/剪切的节点
    返回值：无
*/
void ISetPaste(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    Icplr(nodeX->child,curNode->child);
    //复制文件节点

    if(nodeX->child->flags&1)
        Irmlr(nodeX->child);
    //如果是剪切，则删除源文件节点
}

/*
    函数功能：激活删除函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制/剪切的节点
    返回值：无
*/
void ISetDelete(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;

    nodeX->child=NULL;
    //辅助节点置零

    Irmlr(curNode->child);
    //激活删除函数
}

/*
    函数功能：激活删除函数
    输入参数：flagx——菜单状态位, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetDeleteComfirm(IFileNode* flagx,IFileNode* null)
{
    char* flag=(char*)flagx;
    (*flag)|=2;
    //激活确认删除窗口
}

/*
    函数功能：激活重命名函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
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
    //找到被选中的文件节点
    
    strcpy(temp,tempNode->file.name);
    IGetString(254,110+20*i,150,temp,0);
    //获取新文件名

    if(temp[0])
        Irename(tempNode,temp);
}

/*
    函数功能：激活创建新文件函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
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
    //找到被选中的文件节点

    IGetString(254,110+20*i,150,temp,4);
    //获取新文件名

    if(temp[0])
        if(!Inew(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            IWarningBeep();
            delay(1500);
        }
        //如果创建文件失败
}

/*
    函数功能：激活创建新文件夹函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
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
    //找到被选中的文件节点

    IGetString(254,110+20*i,150,temp,4);
    //获取新文件名

    if(temp[0])
        if(!Imkdir(curNode->child,temp))
        {
            setcolor(249);
            outtextxy(400,752,"Failed");
            IWarningBeep();
            delay(1500);
        }
        //如果创建文件夹失败
}