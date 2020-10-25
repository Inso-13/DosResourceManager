/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：视图函数02等
 **************************************************
 */

#include"IView02.h"

/*
    函数功能：画界面背景
    输入参数：无
    输出参数：无
    返回值：无
*/
void IPlainView(FILE *fpHZ)
{
    if(fpHZ==NULL)  //检查汉字库
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fpHZ is NULL in IPlainView");
    }
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    settextstyle(1,0,2);

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(0+DF,0+DF,1024+DF,768+DF);
    setfillstyle(SOLID_FILL,DRM_BROWN);
    bar(0+DF,0+DF,1024+DF,22+DF);
    setcolor(DRM_BLACK);
    Iouttextxy(10+DF,5+DF,"仿Windows资源管理器",fpHZ);  //头部栏

    setcolor(DRM_DARKGRAY);
    line(0+DF,44+DF,1024+DF,44+DF);
    line(0+DF,45+DF,1024+DF,45+DF);
    rectangle(152+DF,51+DF,824+DF,78+DF);
    line(803+DF,52+DF,803+DF,76+DF);
    rectangle(832+DF,51+DF,1017+DF,78+DF);
    line(851+DF,51+DF,851+DF,78+DF);
    line(0+DF,84+DF,1024+DF,84+DF);
    line(0+DF,85+DF,1024+DF,85+DF);
    IRefresh(814+DF,64+DF);
    IMagnifier(841+DF,61+DF);
    IExit(1004+DF,8+DF);    
    setcolor(DRM_DARKGRAY);
    line(240+DF,88+DF,240+DF,742+DF);
    line(0+DF,744+DF,1024+DF,744+DF);
    //伪菜单栏，和分栏线
}

/*
    函数功能：左侧窗口
    输入参数：root——文件根节点, curNode——当前目录二级指针, nodeX——辅助文件节点, top——事件栈, (beginX,beginY)——开始画的位置, page——页码, flag——标志位
    输出参数：无
    返回值：纵坐标的偏移量
*/
int IView0(IFileNode *root,IFileNodePointer **curNode,IFileNodePointer *nodeX,\
IEventStackNode *top,int beginX,int beginY,char *page,char flag,FILE *fpHZ)
{
    int increaceY=0;    //y轴偏移量
    char thisPage=1;    //是否为当前页
    char tempStr[3];    //暂存页码  
    IEvent tempEvent;   //辅助事件

    if(!root) return 0;         

    if(beginY<110+DF+600*(*page-1)||beginY>110+DF+600*(*page))
        thisPage=0; //并非该页的数据

    if(thisPage&&(*curNode)->child==root)   //选中某个文件夹
    {
        setfillstyle(SOLID_FILL,DRM_CHOSENBLUE);
        bar(0+DF,beginY-(*page-1)*600,238+DF,beginY-(*page-1)*600+22);
    }

    if(IisFolder(root)) //如果是文件夹
    {
        increaceY+=24;  //y轴偏移量
        if(thisPage)    //如果是该页文件夹
            if(!(root->flags&NODE_HAS_FOLDER))         //空文件夹
            {
                Ifolder(beginX+11,beginY-(*page-1)*600+4);  //画图标
                setcolor(DRM_BLACK);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,IAfterEntree,\
                (IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
                IEventStackPush(top,tempEvent); //双击打开文件夹
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,IEntreeActive,\
                root,(IFileNode*)curNode,REACT_MORE);
                IEventStackPush(top,tempEvent); //双击打开文件夹
            }
            else if(root->file.type[0]=='0')   //未打开
            {
                IPointerRight(beginX+1,beginY-(*page-1)*600+8);
                if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                    Idisk(beginX+11,beginY-(*page-1)*600+4);
                else
                    Ifolder(beginX+11,beginY-(*page-1)*600+4);  //画图标
                setcolor(DRM_BLACK);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,\
                beginY-(*page-1)*600+14,MOUSE_LEFT_PRESS,IAfterEntree,\
                (IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
                IEventStackPush(top,tempEvent); //单击打开文件夹
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,\
                beginY-(*page-1)*600+14,MOUSE_LEFT_PRESS,IEntreeActive,root,\
                (IFileNode*)curNode,REACT_MORE);
                IEventStackPush(top,tempEvent); //单击打开文件夹
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,IAfterEntree,\
                (IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW01);
                IEventStackPush(top,tempEvent); //双击打开文件夹
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,IEntreeActive,\
                root,(IFileNode*)curNode,REACT_MORE);
                IEventStackPush(top,tempEvent); //双击打开文件夹
            }
            else        //打开的文件夹
            {
                if(!(root->file.type[1]=='\\'))
                    IPointerDown(beginX,beginY-(*page-1)*600+9);
                if(root->file.type[1]=='d'||root->file.type[1]=='\\')
                    Idisk(beginX+11,beginY-(*page-1)*600+4);
                else
                    Ifolder(beginX+11,beginY-(*page-1)*600+4);  //画图标
                setcolor(DRM_BLACK);
                Iouttextxy(beginX+25+10,beginY-(*page-1)*600+7,root->file.name,fpHZ);
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,\
                beginY-(*page-1)*600+14,MOUSE_LEFT_PRESS,IDetreeActive,root,\
                (IFileNode*)curNode,REACT_VIEW01);
                IEventStackPush(top,tempEvent); //单击关闭文件夹
                ISetEvent(&tempEvent,beginX,beginY-(*page-1)*600+6,beginX+16,\
                beginY-(*page-1)*600+14,MOUSE_LEFT_PRESS,ISetXNull,root,\
                (IFileNode*)nodeX,REACT_MORE);
                IEventStackPush(top,tempEvent); //将nodeX置为null
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,IDetreeActive,\
                root,(IFileNode*)curNode,REACT_VIEW01);
                IEventStackPush(top,tempEvent);//单击关闭文件夹
                ISetEvent(&tempEvent,0+DF,beginY-(*page-1)*600,238+DF,\
                beginY-(*page-1)*600+22,MOUSE_DOUBLE_LEFT_PRESS,ISetXNull,\
                root,(IFileNode*)nodeX,REACT_MORE);
                IEventStackPush(top,tempEvent); //将nodeX置为null
            }
        if(root->child&&root->file.type[0]=='1')
            increaceY+=IView0(root->child,curNode,nodeX,top,beginX+8,\
            beginY+increaceY,page,VIEW0_UNPAGE,fpHZ);
    }
    if(root->next)
        increaceY+=IView0(root->next,curNode,nodeX,top,beginX,beginY+increaceY,\
        page,VIEW0_UNPAGE,fpHZ);

    if(flag==VIEW0_PAGE)
    {
        if(*page>1)
        {
            ISetEvent(&tempEvent,150+DF,720+DF,168+DF,738+DF,MOUSE_LEFT_PRESS,\
            ILastPage,(IFileNode*)page,NULL,REACT_VIEW0);
            IEventStackPush(top,tempEvent); //回到上一页
            setcolor(DRM_BLACK);
        }
        else
            setcolor(LIGHTGRAY);
        IGoLeft(150+DF,720+DF);
        if(*page<=((increaceY-24)/600))
        {
            ISetEvent(&tempEvent,210+DF,720+DF,228+DF,738+DF,MOUSE_LEFT_PRESS,\
            INextPage,(IFileNode*)page,NULL,REACT_VIEW0);
            IEventStackPush(top,tempEvent); //回到下一页
            setcolor(DRM_BLACK);
        }
        else
            setcolor(LIGHTGRAY);
        IGoRight(210+DF,720+DF);
        sprintf(tempStr,"%d",*page);
        setcolor(DRM_BLACK);
        outtextxy(182+DF,722+DF,tempStr);   //输出页码
    }   //只画一次左右箭头
    return increaceY;
}

/*
    函数功能：画查找后的显示界面
    输入参数：page——页数, fpHZ——汉字库
    输出参数：无
    返回值：无
*/
void IView2(char *page,FILE *fpHZ,IEventStackNode *top,IFileNodePointer **curNode)
{

    FILE *searched=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","r");
    char tempStr[PATH_LEN];
    IEvent tempEvent;
    char name[15];
    int y=120+DF,i,n,j=0,numOfsearched=0;

    setcolor(DRM_BLACK);
    IGoLeft(250+DF,720+DF);
    Iouttextxy(270+DF,721+DF,"返回",fpHZ);
    ISetEvent(&tempEvent,250+DF,720+DF,265+DF,735+DF,MOUSE_LEFT_PRESS,INOP,\
    NULL,NULL,REACT_VIEW1);
    IEventStackPush(top,tempEvent);

    Iouttextxy(853+DF,61+DF,"在本文件夹中搜索",fpHZ);
    ISetEvent(&tempEvent,853+DF,52+DF,1016+DF,77+DF,MOUSE_LEFT_PRESS,\
    ISearchActive,(IFileNode*)(*curNode),NULL,REACT_VIEW2);
    IEventStackPush(top,tempEvent);
    //重新搜索

    setcolor(DRM_PURPLE);
    IPutsHZ16(250+DF,94+DF,"匹配文件名",fpHZ);
    IPutsHZ16(500+DF,94+DF,"绝对路径",fpHZ);


    while(fgets(tempStr,PATH_LEN,searched))
    {
        if(++numOfsearched>=MAXNODES)
        {
            Iouttextxy(500+DF,753+DF,"只显示前120个匹配项",fpHZ);
            break;
        }
        //搜索到多于120个匹配项
    }
    if((numOfsearched-1)/30+1<*page)
        (*page)--;
    else if(!(*page))
        *page=1;
    //页码控制
    
    rewind(searched);
    while(fgets(tempStr,PATH_LEN,searched)&&((++j)<=MAXNODES))
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
        ISetEvent(&tempEvent,248+DF,y,936+DF,y+18,MOUSE_LEFT_PRESS,IGotoFrom,(IFileNode*)j,(IFileNode*)curNode,REACT_VIEW01);
        IEventStackPush(top,tempEvent);
        IGetNameByPath(tempStr,name);

        setcolor(DRM_BLACK);
        Iouttextxy(250+DF,y,name,fpHZ);
        Iouttextxy(500+DF,y,tempStr,fpHZ);

        y+=20;
    }
    if(!j)
        IPutsHZ16(530+DF,240+DF,"未检测到匹配项",fpHZ);
    //未搜索到文件
    else
    {
        if(*page>1)
            setcolor(DRM_BLACK);
        else
            setcolor(LIGHTGRAY);
        IGoLeft(928+DF,720+DF);
        if(*page<(j-2)/30+1)
            setcolor(DRM_BLACK);
        else
            setcolor(LIGHTGRAY);
        IGoRight(992+DF,720+DF);
        sprintf(tempStr,"%d",*page);
        setcolor(DRM_BLACK);
        outtextxy(962+DF,722+DF,tempStr);
    }
    //搜索到文件

    fclose(searched);
}
