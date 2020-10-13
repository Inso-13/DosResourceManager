/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：视图函数1等
 **************************************************
 */

#include"IView1.h"

/*
    函数功能：右侧窗口
    输入参数：curNode——当前目录二级指针, nodeX——辅助节点指针，用于保存被复制/剪切的节点,top——事件栈, (beginX,beginY)——开始画的位置, page——页码, flag——标志位，fpHZ——汉字库指针
    输出参数：无
    返回值：纵坐标的偏移量
*/
int IView1(IFileNodePointer **curNode,IFileNodePointer *nodeX,IEventStackNode *top,char *page,char *menuFlag,FILE *fpHZ)
{
    int i,numOfItem=0,numOfSelected=0;
    IFileNode *tempNode=NULL;
    IEvent tempEvent;                   //辅助事件
    char temp[PATH_LEN];

    settextstyle(0,0,0);
    if(fpHZ==NULL)  //检查汉字库
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fpHZ is NULL in IView1");
    }
    
    setcolor(DRM_BLACK);
    tempNode=(*curNode)->child;
    IGetAbsolutePath(tempNode,temp);
    outtextxy(192+DF,61+DF,temp);   //路径栏的显示

    ISetEvent(&tempEvent,803+DF,51+DF,824+DF,78+DF,MOUSE_LEFT_PRESS,INOP,NULL,NULL,REACT_VIEW01);
    IEventStackPush(top,tempEvent); //刷新功能

    if(IFindParent((*curNode)->child))
    {
        setcolor(DRM_BLACK);
        ISetEvent(&tempEvent,108+DF,57+DF,120+DF,76+DF,MOUSE_LEFT_PRESS,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
        IEventStackPush(top,tempEvent); //单击返回上一级
        ISetEvent(&tempEvent,108+DF,57+DF,120+DF,76+DF,MOUSE_LEFT_PRESS,IEntreeActive,IFindParent((*curNode)->child),(IFileNode*)curNode,REACT_MORE);
        IEventStackPush(top,tempEvent); //单击返回上一级
    }
    else
        setcolor(LIGHTGRAY);
    IGoUp(108+DF,57+DF);
    //返回上一级功能

    if((*curNode)->pre&&(*curNode)->pre->child)
    {
        setcolor(DRM_BLACK);
        ISetEvent(&tempEvent,25+DF,59+DF,40+DF,76+DF,MOUSE_LEFT_PRESS,IGoLeftActive,(IFileNode*)curNode,NULL,REACT_VIEW01); //单击返回上一目录功能
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoLeft(25+DF,60+DF);
    //返回上一目录功能

    if((*curNode)->next&&(*curNode)->next->child)
    {
        setcolor(DRM_BLACK);
        ISetEvent(&tempEvent,62+DF,59+DF,92+DF,76+DF,MOUSE_LEFT_PRESS,IGoRightActive,(IFileNode*)curNode,NULL,REACT_VIEW01);    //单击返回下一目录功能
        IEventStackPush(top,tempEvent);
    }
    else
        setcolor(LIGHTGRAY);
    IGoRight(62+DF,60+DF);
    //返回下一目录功能
        
    setcolor(DRM_BLACK);
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(853+DF,52+DF,1016+DF,77+DF);
    if(!tempNode->child)
    {
        Iouttextxy(853+DF,61+DF,"无内容",fpHZ);
        if(!strcmp(tempNode->file.type,"0ds"))
            Iouttextxy(560+DF,240+DF,"仅管理员可见",fpHZ);
        else
            Iouttextxy(530+DF,240+DF,"未打开文件夹或未检索到内容",fpHZ);
    }
    else if(tempNode->file.type[1]=='\\')
        Iouttextxy(853+DF,61+DF,"根目录无法搜索文件",fpHZ);
    else
    {
        Iouttextxy(853+DF,61+DF,"在本文件夹中搜索",fpHZ);
        ISetEvent(&tempEvent,853+DF,52+DF,1016+DF,77+DF,MOUSE_LEFT_PRESS,ISearchActive,(IFileNode*)(*curNode),NULL,REACT_VIEW2);    //单击开始搜索
        IEventStackPush(top,tempEvent);
    }
    //搜索栏显示
    
    tempNode=(*curNode)->child->child;
    while(tempNode)
    {
        numOfItem++;
        if(tempNode->flags&NODE_IS_SELECTED)
            numOfSelected++;
        tempNode=tempNode->next;
    }
    //统计总文件数和被选中的文件数

    IView1PageControl(curNode,page,numOfItem);  //检查是否改变页码
    if(*page>=(numOfItem-1)/30+1)
        (*menuFlag)|=FLAG_ADD_LAST_PAGE;
    else
        (*menuFlag)&=FLAG_DEL_LAST_PAGE;
    //页码控制

    tempNode=(*curNode)->child->child;
    for(i=0;i<(*page-1)*(30);i++)
        tempNode=tempNode->next;
    //跳转至当前页

    setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
    if((*menuFlag)&FLAG_IS_VIEW11)
    {
        bar(1001+DF,747+DF,1020+DF,766+DF);
        IView11(curNode,nodeX,tempNode,fpHZ,top,menuFlag);
        ISetEvent(&tempEvent,976+DF,747+DF,995+DF,766+DF,MOUSE_LEFT_PRESS,ISetView10,(IFileNode*)menuFlag,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
    }
    else
    {
        bar(976+DF,747+DF,995+DF,766+DF);
        IView10(curNode,nodeX,tempNode,fpHZ,top,menuFlag);
        ISetEvent(&tempEvent,1001+DF,747+DF,1020+DF,766+DF,MOUSE_LEFT_PRESS,ISetView11,(IFileNode*)menuFlag,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
    }   //主视图部分
    IDetailOption(980+DF,751+DF);
    IPictureOption(1005+DF,751+DF);
    
    sprintf(temp,"%d个项目",numOfItem);
    Iouttextxy(16+DF,752+3+DF,temp,fpHZ);
    if(numOfSelected)
    {
        sprintf(temp,"选中%d个项目",numOfSelected);
        Iouttextxy(160+DF,752+3+DF,temp,fpHZ);
    }
    if((*menuFlag)&FLAG_IS_CTRLED)
    {
        setcolor(DRM_RED);
        outtextxy(320+DF,752+DF,"CTRL");
    }   //状态栏
    
    IView1DelOrCover(numOfSelected,curNode,nodeX,top,menuFlag,fpHZ);
    //删除或覆盖确认
    return numOfSelected;
}

/*
    函数功能：删除或覆盖确认窗口
    输入参数：numOFSelected——被选中的文件数,curNode——当前目录二级指针, nodeX——辅助节点指针，用于保存被复制/剪切的节点,top——事件栈,fpHZ——汉字库指针
    输出参数：无
    返回值：无
*/
void IView1DelOrCover(int numOfSelected,IFileNodePointer **curNode,IFileNodePointer *nodeX,IEventStackNode *top,char *menuFlag,FILE *fpHZ)
{
    IEvent tempEvent;     //辅助事件
    char temp[50];  //辅助字符串

    if((*menuFlag)&FLAG_TO_DEL)
    {
        (*menuFlag)&=FLAG_DEL_TO_DEL;
        setcolor(DRM_VIOLET);
        rectangle(412+DF,334+DF,662+DF,434+DF);
        setfillstyle(SOLID_FILL,DRM_VIOLET);
        bar(412+DF,334+DF,662+DF,356+DF);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(413+DF,357+DF,661+DF,433+DF);
        rectangle(591+DF,403+DF,641+DF,423+DF);
        rectangle(521+DF,403+DF,571+DF,423+DF);

        setcolor(DRM_BLACK);
        sprintf(temp,"%s%d%s","确定要删除选中的",numOfSelected,"个项目吗？");
        Iouttextxy(433+DF,377+DF,temp,fpHZ);
        IPutsHZ16(530+DF,406+DF,"确定",fpHZ);
        IPutsHZ16(600+DF,406+DF,"取消",fpHZ);
        IWarningBeep();

        ISetEvent(&tempEvent,0+DF,0+DF,1024+DF,768+DF,MOUSE_LEFT_PRESS,INOP,NULL,NULL,REACT_NULL);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521+DF,403+DF,571+DF,423+DF,MOUSE_LEFT_PRESS,ISetDelete,(IFileNode*)(*curNode),(IFileNode*)nodeX,REACT_VIEW01);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591+DF,403+DF,641+DF,423+DF,MOUSE_LEFT_PRESS,INOP,NULL,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
    }
    else if((*menuFlag)&FLAG_TO_COVER)
    {
        (*menuFlag)&=FLAG_CLEAR_COVER;
        setcolor(DRM_VIOLET);
        rectangle(412+DF,334+DF,662+DF,434+DF);
        setfillstyle(SOLID_FILL,DRM_VIOLET);
        bar(412+DF,334+DF,662+DF,356+DF);
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(413+DF,357+DF,661+DF,433+DF);
        rectangle(591+DF,403+DF,641+DF,423+DF);
        rectangle(521+DF,403+DF,571+DF,423+DF);

        setcolor(DRM_BLACK);
        sprintf(temp,"%s","确定要覆盖文件吗？");
        Iouttextxy(433+DF,377+DF,temp,fpHZ);
        IPutsHZ16(530+DF,406+DF,"确定",fpHZ);
        IPutsHZ16(600+DF,406+DF,"取消",fpHZ);
        IWarningBeep();

        ISetEvent(&tempEvent,0+DF,0+DF,1024+DF,768+DF,MOUSE_LEFT_PRESS,INOP,NULL,NULL,REACT_NULL);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,521+DF,403+DF,571+DF,423+DF,MOUSE_LEFT_PRESS,ISetPasteF,(IFileNode*)(*curNode),(IFileNode*)nodeX,REACT_VIEW01);
        IEventStackPush(top,tempEvent);
        ISetEvent(&tempEvent,591+DF,403+DF,641+DF,423+DF,MOUSE_LEFT_PRESS,ISetPaste,(IFileNode*)(*curNode),(IFileNode*)nodeX,REACT_VIEW01);
        IEventStackPush(top,tempEvent);
    }
    else if((*menuFlag)&FLAG_TO_UNCOVER)
    {
        (*menuFlag)&=FLAG_CLEAR_COVER;
        ISetEvent(&tempEvent,0,0,0,0,MOUSE_NULL,ISetPaste,(IFileNode*)(*curNode),(IFileNode*)nodeX,REACT_VIEW01);
        IEventStackPush(top,tempEvent);
    }   //删除确认
}
/*
    函数功能：根据文件类型，画图标
    输入参数：tempNode——文件节点, y——纵向位置
    输出参数：无
    返回值：无
*/
void IView10DrawIcon(IFileNode *tempNode,int y)
{
    if(tempNode->flags&NODE_IS_SELECTED)
    {
        setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
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
    函数功能：根据文件类型，画图标
    输入参数：tempNode——文件节点, x——横向位置, y——纵向位置
    输出参数：无
    返回值：无
*/
void IView11DrawIcon(IFileNode *tempNode,int x,int y)
{
    if(tempNode->flags&NODE_IS_SELECTED)
    {
        setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
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
    函数功能：右侧窗口(详细信息)
    输入参数：curNode——当前目录二级指针, nodeX——辅助节点指针，用于保存被复制/剪切的节点,top——事件栈
    输出参数：无
    返回值：无
*/
void IView10(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,FILE *fpHZ,IEventStackNode *top,char *menuFlag)
{
    IEvent tempEvent;
    char temp[PATH_LEN];
    int y=116+DF;

    setcolor(DRM_PURPLE);
    IPutsHZ16(254+DF,94+DF,"文件名",fpHZ);
    IPutsHZ16(430+DF,94+DF,"修改日期",fpHZ);
    IPutsHZ16(686+DF,94+DF,"类型",fpHZ);
    IPutsHZ16(830+DF,94+DF,"大小",fpHZ);
    setcolor(DRM_LIGHTGRAY);
    line(424+DF,88+DF,424+DF,112+DF);
    line(680+DF,88+DF,680+DF,112+DF);
    line(824+DF,88+DF,824+DF,112+DF);
    line(936+DF,88+DF,936+DF,112+DF);
    //文件详细信息的表头

    while(tempNode)     //对每一个当前页码的文件
    {
        IView10DrawIcon(tempNode,y);
        //根据文件类型，画图标

        setcolor(DRM_BLACK);
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
        //文件详细信息

        if((*menuFlag)&FLAG_IS_CTRLED)
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_LEFT_PRESS,ICtrlSelect,tempNode,NULL,REACT_VIEW1);
        else
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_LEFT_PRESS,ISelect,tempNode,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
        //根据是否Ctrl,设置选择类型

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_DOUBLE_LEFT_PRESS,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_DOUBLE_LEFT_PRESS,IEntreeActive,tempNode,(IFileNode*)curNode,REACT_MORE);
            IEventStackPush(top,tempEvent);
            if(tempNode->file.type[1]=='d')
                Iouttextxy(688+DF,y+6+3,"磁盘",fpHZ);
            else
                Iouttextxy(688+DF,y+6+3,"文件夹",fpHZ);
        }
        else
        {
            outtextxy(688+DF,y+6,tempNode->file.type);
            if(!strcmp(tempNode->file.type,"EXE")||!strcmp(tempNode->file.type,"BAT"))
            {
                ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_DOUBLE_LEFT_PRESS,IexeActive,tempNode,NULL,REACT_VIEW01);
                IEventStackPush(top,tempEvent);
            }
            if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"ASM"))
            {
                ISetEvent(&tempEvent,248+DF,y,936+DF,y+19,MOUSE_DOUBLE_LEFT_PRESS,ItxtActive,tempNode,NULL,REACT_VIEW01);
                IEventStackPush(top,tempEvent);
            }
        }
        //文件打开方式

        if(y>682+DF) break;
        y+=20;
        tempNode=tempNode->next;
    }
}

/*
    函数功能：右侧窗口(大图标)
    输入参数：curNode——当前目录二级指针, nodeX——辅助节点指针，用于保存被复制/剪切的节点,top——事件栈
    输出参数：无
    返回值：无
*/
void IView11(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,FILE *fpHZ,IEventStackNode *top,char *menuFlag)
{
    IEvent tempEvent;
    char temp[PATH_LEN];
    int y=116+DF,x=276+DF;
    char num=0;

    while(tempNode)     //对每一个当前页码的文件
    {
        num++;
        IView11DrawIcon(tempNode,x,y);
        //根据文件类型，画图标
        setcolor(DRM_BLACK);
        Iouttextxy(x+50-strlen(tempNode->file.name)*4,y+95,tempNode->file.name,fpHZ);

        if((*menuFlag)&FLAG_IS_CTRLED)
            ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_LEFT_PRESS,ICtrlSelect,tempNode,NULL,REACT_VIEW1);
        else
            ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_LEFT_PRESS,ISelect,tempNode,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
        //根据是否Ctrl,设置选择类型

        if(IisFolder(tempNode))
        {
            ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_DOUBLE_LEFT_PRESS,IAfterEntree,(IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_DOUBLE_LEFT_PRESS,IEntreeActive,tempNode,(IFileNode*)curNode,REACT_MORE);
            IEventStackPush(top,tempEvent);
        }
        else
        {
            if(!strcmp(tempNode->file.type,"EXE")||!strcmp(tempNode->file.type,"BAT"))
            {
                ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_DOUBLE_LEFT_PRESS,IexeActive,tempNode,NULL,REACT_VIEW01);
                IEventStackPush(top,tempEvent);
            }
            if(!strcmp(tempNode->file.type,"TXT")||!strcmp(tempNode->file.type,"C")||!strcmp(tempNode->file.type,"H")||!strcmp(tempNode->file.type,"CPP")||!strcmp(tempNode->file.type,"ASM"))
            {
                ISetEvent(&tempEvent,x,y,x+99,y+79,MOUSE_DOUBLE_LEFT_PRESS,ItxtActive,tempNode,NULL,REACT_VIEW01);
                IEventStackPush(top,tempEvent);
            }
        }
        //文件打开方式

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
    函数功能：根据文件类型，画图标
    输入参数：curNode——当前目录二级指针, page——页码, numOfItem——项目总数
    输出参数：无
    返回值：无
*/
void IView1PageControl(IFileNodePointer **curNode,char *page,int numOfItem)
{
    static IFileNode *lastCurNode;
    char temp[3];
    
    if(lastCurNode!=(*curNode)->child)
        *page=1;
    else if((numOfItem-1)/30+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    lastCurNode=(*curNode)->child;
    //页码控制

    if(*page<(numOfItem-1)/30+1)
        setcolor(DRM_BLACK);
    else
        setcolor(LIGHTGRAY);
    IGoRight(992+DF,720+DF);
    if(*page>1)
        setcolor(DRM_BLACK);
    else
        setcolor(LIGHTGRAY);
    IGoLeft(928+DF,720+DF);
    sprintf(temp,"%d",*page);
    setcolor(DRM_BLACK);
    outtextxy(962+DF,722+DF,temp);
}
