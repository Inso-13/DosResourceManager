/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：Active类函数处于中间层，用于将后端（如Diry等）函数的接口统一化，供前端调用栈使用
 **************************************************
 */

#include"IActive.h"

/*
    函数功能：根据情况将nodeX置为NULL
    输入参数：node——需要IDetree的节点
    输出参数：X——辅助文件节点
    返回值：无
*/
void ISetXNull(IFileNode *node,IFileNode *X)
{
    IFileNodePointer *nodeX=(IFileNodePointer*)X;    //文件辅助节点
    char path1[PATH_LEN],path2[PATH_LEN];     //辅助字符串

    if(node->file.type[1]=='\\')
        return;     //如果是根目录，不进行操作

    IGetAbsolutePath(node,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);      //得到两者的路径
    if(!strcmp(path1,path2)||IisChild(path2,path1))
        nodeX->child=NULL;  //发生冲突，删除辅助节点，取消粘贴等待
}

/*
    函数功能：在View1中（单一地）选中文件节点，显示高亮
    输入参数：node——被选中的节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISelect(IFileNode *node,IFileNode *flag)
{
    char *menuFlag=(char*)flag;
    char *temp="1";
    int i=0,j=0;
    IFileNode *tempNode=IFindParent(node)->child;   //选择节点的父节点

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            tempNode->flags&=NODE_DEL_SELECT;
            if((*menuFlag)&FLAG_IS_VIEW11)
                IBar(276+DF+i%30%6*102,116+DF+i%30/6*112,276+DF+99+i%30%6*102,\
                116+DF+109+i%30/6*112,DRM_CHOSENBLUE,DRM_WHITE);
            else
                IBar(248+DF,116+20*i+DF,936+DF,135+20*i+DF,DRM_CHOSENBLUE,\
                DRM_WHITE);
        }
        if(tempNode==node)
        {
            j=i;
        }
        tempNode=tempNode->next;
        i++;
    }   //如果当前路径下已经有被选中的节点，将其置为未被选中

    node->flags|=NODE_ADD_SELECT; //选中该节点
    if((*menuFlag)&FLAG_IS_VIEW11)
        IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
        116+DF+109+j%30/6*112,DRM_WHITE,DRM_CHOSENBLUE);      
    else
        IBar(248+DF,116+20*j+DF,936+DF,135+20*j+DF,DRM_WHITE,DRM_CHOSENBLUE);
    
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(160+DF+16*2,752+3+DF,160+DF+16*2+8*3,767+DF);
    setcolor(DRM_BLUE);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(160+DF+16*2+12,752+3+DF,temp);
    settextjustify(LEFT_TEXT,TOP_TEXT);
}

/*
    函数功能：在View1中（复合地）选中文件节点，显示高亮
    输入参数：node——被选中的节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ICtrlSelect(IFileNode *node,IFileNode *flag)
{
    char temp[4];
    char *menuFlag=(char*)flag;
    IFileNode *tempNode=IFindParent(node)->child;   //选择节点的父节点
    int i=0,j=0,numOfSelected=0;

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
            numOfSelected++;
        if(tempNode==node)
            j=i;
        tempNode=tempNode->next;
        i++;
    }

    if(!(node->flags&NODE_IS_SELECTED))
    {
        node->flags|=NODE_ADD_SELECT;
        numOfSelected++;
        if((*menuFlag)&FLAG_IS_VIEW11)
            IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
            116+DF+109+j%30/6*112,DRM_WHITE,DRM_CHOSENBLUE);      
        else
            IBar(248+DF,116+20*j+DF,936+DF,135+20*j+DF,DRM_WHITE,DRM_CHOSENBLUE);
    }
    else
    {
        node->flags&=NODE_DEL_SELECT;
        numOfSelected--;
        if((*menuFlag)&FLAG_IS_VIEW11)
            IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
            116+DF+109+j%30/6*112,DRM_CHOSENBLUE,DRM_WHITE);
        else
            IBar(248+DF,116+20*j+DF,936+DF,135+20*j+DF,DRM_CHOSENBLUE,DRM_WHITE);
    }
    //如果该节点已被选中，则解选中；否则选中该节点

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(160+DF+16*2,752+3+DF,160+DF+16*2+8*3,767+DF);
    setcolor(DRM_BLUE);
    sprintf(temp,"%d",numOfSelected);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(160+DF+16*2+12,752+3+DF,temp);
    settextjustify(LEFT_TEXT,TOP_TEXT);
}

/*
    函数功能：空操作，可用于占位/截断/刷新等
    输入参数：null1——用于占位, null2——用于占位
    输出参数：无
    返回值：无
*/
void INOP(IFileNode *null1,IFileNode *null2){}

/*
    函数功能：返回上一目录
    输入参数：null——用于占位
    输出参数：cur——当前节点
    返回值：无
*/
void IGoLeftActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;   //返回上一目录
}

/*
    函数功能：返回下一目录
    输入参数：null——用于占位
    输出参数：cur——当前节点
    返回值：无
*/
void IGoRightActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;  //返回下一目录
}

/*
    函数功能：激活查找函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISearchActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;  //当前节点
    FILE *fp=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+"); //覆盖的方式打开用于记录的文件
    char temp[20],path[PATH_LEN];     //辅助字符串

    IGetAbsolutePath(curNode->child,path);  //获得需要查找的路径
    strcpy(temp,"\0");  //清空字符串
    IGetString(851+DF,51+DF,166,temp,SEARCH_STR);   //得到查找的pattern，可以使用？*

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(DRM_RED);
    outtextxy(900+DF,753+DF,"Searching...");    //提示正在搜索

    if(temp[0])
        ISearch(path,temp,fp);  //激活查找函数
    fclose(fp);    //关闭用来记录的文件

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);  //停止显示Searching...
}

/*
    函数功能：打开exe类文件
    输入参数：exe——可执行的文件节点, null——用于占位
    输出参数：无
    返回值：无
*/
void IexeActive(IFileNode *exe,IFileNode *null)
{
    char temp[PATH_LEN+24];     //辅助字符串

    IGetAbsolutePath(exe,temp);

    setfillstyle(SOLID_FILL,DRM_BLACK);
    bar(0,0,1280,1024);
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");  //将日志信息输出至log.txt
    system(temp);   //系统调用，借用编辑器打开文本文件
    delay(2000);  //短暂停留
    IQuit();    //短暂停留后退出
}

/*
    函数功能：打开txt类文件
    输入参数：txt——可编辑的文件节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ItxtActive(IFileNode *txt,IFileNode *null)
{
    char temp[PATH_LEN+48];   //辅助字符串

    strcpy(temp,"C:\\BORLANDC\\BIN\\BC.EXE ");  //调用BC编辑器
    IGetAbsolutePath(txt,temp+23);  
    
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");  //输出重定向至log.txt
    system(temp);   //系统调用，借用BC编辑器打开文本文件
    IQuit();    //返回时退出
}

/*
    函数功能：View0上一页
    输入参数：pag——View0的页码, null——用于占位
    输出参数：无
    返回值：无
*/
void ILastPage(IFileNode *pag,IFileNode *null)
{
    char *page=(char*)pag;  //页码控制

    *page-=1;   //翻到上一页
}

/*
    函数功能：View0下一页
    输入参数：pag——View0的页码, null——用于占位
    输出参数：无
    返回值：无
*/
void INextPage(IFileNode *pag,IFileNode *null)
{
    char *page=(char*)pag;  //页码控制

    *page+=1;   //翻到下一页
}

/*
    函数功能：设置View0为详细信息
    输入参数：flag——View0的控制位, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetView10(IFileNode *flag,IFileNode *null)
{
    char *menuFlag=(char*)flag;    //菜单/视图控制

    (*menuFlag)&=FLAG_ADD_VIEW10;    //设置为显示view1的0号视图
}

/*
    函数功能：设置View0为大图标
    输入参数：flag——View0的控制位, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetView11(IFileNode *flag,IFileNode *null)
{
    char *menuFlag=(char*)flag; //菜单/视图控制

    (*menuFlag)|=FLAG_ADD_VIEW11;    //设置为显示view1的1号视图
}