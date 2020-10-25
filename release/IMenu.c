/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：与菜单相关的部分函数
 **************************************************
 */

#include"IMenu.h"

/*
    函数功能：在View1中激活一级菜单
    输入参数：(mouseX,mouseY)——鼠标的位置, numOfSelected——当前路径中被选中的文件数, top——View1的事件栈, curNode——当前节点,nodeX——辅助节点指针, menuFlag——菜单的标志(bit0 是否为二层菜单,bit1 是否有删除确认窗口,bit2 是否按下Ctrl, bit3 是否是最后一页, bit4、5 是否有覆盖确认窗口,bit6 区分View1视图 0为详细信息/1为大图标), fpHZ——汉字库文件
    输出参数：无
    返回值：无
*/
void IMenu(int mouseX,int mouseY,IEventStackNode *top,IFileNodePointer *curNode,\
IFileNodePointer *nodeX,char *menuFlag,FILE *fpHZ)
{
    int i,numOfSelected=0;
    IEvent tempEvent;
    IFileNode *tempNode=curNode->child->child;
    int (*lambda[8])(IFileNode*,IFileNode*)={ISortDateUp,ISortDateDown,\
    ISortSizeUp,ISortSizeDown,ISortNameUp,ISortNameDown,ISortTypeUp,ISortTypeDown};  
    //排序函数指针数组

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
            numOfSelected++;
        tempNode=tempNode->next;
    }
    if(mouseX>928+DF) mouseX=928+DF;
    if(mouseY>607+DF) mouseY=607+DF;
    IDrawMenu(mouseX,mouseY,curNode,nodeX,*menuFlag,fpHZ);
    //画菜单

    if(!((*menuFlag)&FLAG_IS_SEC_MENU))
    {
        if(curNode->child->file.type[1]=='\\')
            return;
        if((*menuFlag)&FLAG_IS_LAST_PAGE)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*5,mouseX+80,mouseY+19+20*5,\
            MOUSE_LEFT_PRESS,ISetNewFile,(IFileNode*)curNode,(IFileNode*)menuFlag,\
            REACT_VIEW1);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*6,mouseX+80,mouseY+19+20*6,\
            MOUSE_LEFT_PRESS,ISetNewFolder,(IFileNode*)curNode,(IFileNode*)menuFlag,\
            REACT_VIEW01);
            IEventStackPush(top,tempEvent);
        }
        ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*7,mouseX+80,mouseY+19+20*7,\
        MOUSE_LEFT_PRESS,ISortMenuActive,(IFileNode*)menuFlag,NULL,REACT_VIEW1);
        IEventStackPush(top,tempEvent);
        if(numOfSelected)
        {
            if(numOfSelected==1)
            {
                ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*4,mouseX+80,mouseY+19+20*4,\
                MOUSE_LEFT_PRESS,ISetRename,(IFileNode*)curNode,(IFileNode*)menuFlag,\
                REACT_VIEW1);
                IEventStackPush(top,tempEvent);
            }
            ISetEvent(&tempEvent,mouseX+1,mouseY+1,mouseX+80,mouseY+19,MOUSE_LEFT_PRESS,\
            ISetCopy,(IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW1);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*1,mouseX+80,mouseY+19+20*1,\
            MOUSE_LEFT_PRESS,ISetCut,(IFileNode*)curNode,(IFileNode*)nodeX,REACT_VIEW1);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*2,mouseX+80,mouseY+19+20*2,\
            MOUSE_LEFT_PRESS,ISetDeleteComfirm,(IFileNode*)menuFlag,NULL,REACT_VIEW1);
            IEventStackPush(top,tempEvent);
        }
        if(!numOfSelected||(curNode->child==nodeX->child))
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*3,mouseX+80,mouseY+19+20*3,\
            MOUSE_LEFT_PRESS,ISetPasteComfirm,(IFileNode*)menuFlag,NULL,REACT_VIEW01);
            IEventStackPush(top,tempEvent);
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*3,mouseX+80,mouseY+19+20*3,\
            MOUSE_LEFT_PRESS,ISetPasteCheck,(IFileNode*)curNode,(IFileNode*)nodeX,\
            REACT_MORE);
            IEventStackPush(top,tempEvent);
        }
    }
    //如果是一级菜单
    else
    {
        for(i=0;i<8;i++)
        {
            ISetEvent(&tempEvent,mouseX+1,mouseY+1+20*i,mouseX+80,mouseY+19+20*i,\
            MOUSE_LEFT_PRESS,ISortActive,(IFileNode*)curNode,(IFileNode*)lambda[i],\
            REACT_VIEW1);
            IEventStackPush(top,tempEvent);
        }
        (*menuFlag)&=FLAG_DEL_SEC_MENU;
    }
    //如果是二级排序菜单
}

/*
    函数功能：在View1中画菜单
    输入参数：(x,y)——画菜单的左上角, numOfSelected——当前路径中被选中的文件数, curNode——当前节点,nodeX——辅助节点指针, menuFlag——菜单的标志(bit0 是否为二层菜单,bit1 是否有删除确认窗口, bit2 是否按下Ctrl, bit3是否是最后一页), fpHZ——汉字库文件
    输出参数：无
    返回值：无
*/
void IDrawMenu(int x,int y,IFileNodePointer *curNode,IFileNodePointer *nodeX,char menuFlag,FILE *fpHZ)
{
    int i,numOfSelected=0;
    unsigned char str[2][8][11]={{"复制","剪切","删除","粘贴","重命名","新文件","新文件夹",\
    "排序.."},{"按日期升序","按日期降序","按大小升序","按大小降序","按名称升序","按名称降序",\
    "按类型升序","按类型降序"}};
    IFileNode *tempNode=curNode->child->child;

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
            numOfSelected++;
        tempNode=tempNode->next;
    }
    if(fpHZ==NULL)
    {
        setcolor(DRM_BLACK);
        outtextxy(100,100,"fpHZ is NULL in IDrawMenu");
    }
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(x,y,x+95,y+160);
    setcolor(DRM_DARKBLUE);
    rectangle(x,y,x+95,y+160);

    for(i=1;i<8;i++)
        line(x+1,y+20*i,x+94,y+20*i);
    if(!(menuFlag&FLAG_IS_SEC_MENU))
    { 
        if(curNode->child->file.type[1]=='\\')
            setcolor(DRM_LIGHTGRAY);
        Iouttextxy(x+3,y+20*7+6,str[0][7],fpHZ);
        if(curNode->child->file.type[1]=='\\'||!(menuFlag&FLAG_IS_LAST_PAGE))
            setcolor(DRM_LIGHTGRAY);
        else
            setcolor(DRM_DARKBLUE);
        IPutsHZ16(x+3,y+20*5+3,str[0][5],fpHZ);
        IPutsHZ16(x+3,y+20*6+3,str[0][6],fpHZ);
        
        if(!numOfSelected)
            setcolor(DRM_LIGHTGRAY);
        else
            setcolor(DRM_DARKBLUE);
        for(i=0;i<3;i++)
            IPutsHZ16(x+3,y+20*i+3,str[0][i],fpHZ);    

        if((!numOfSelected||curNode->child==nodeX->child)&&nodeX->child&&\
        curNode->child->file.type[1]!='\\')
            setcolor(DRM_DARKBLUE);
        else
            setcolor(DRM_LIGHTGRAY);
        IPutsHZ16(x+3,y+3+20*3,str[0][3],fpHZ);
        if(numOfSelected==1&&curNode->child->file.type[1]!='\\')
            setcolor(DRM_DARKBLUE);
        else
            setcolor(DRM_LIGHTGRAY);
        IPutsHZ16(x+3,y+4*20+3,str[0][4],fpHZ);       
    }
    else
    {
        setcolor(DRM_DARKBLUE);
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
void ISetCopy(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;

    if(nodeX->child)
    {
        if(nodeX->child->flags&NODE_IS_CUT)
            nodeX->child->flags&=NODE_DEL_CUT;
    }
    //如果之前有被复制的文件节点，则覆盖之
    
    nodeX->child=curNode->child;
    nodeX->child->flags&=NODE_DEL_CUT;
}

/*
    函数功能：激活剪切函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被剪切的节点
    返回值：无
*/
void ISetCut(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;

    if(nodeX->child)
    {
        if(nodeX->child->flags&NODE_IS_CUT)
            nodeX->child->flags&=NODE_DEL_CUT;
    }
    //如果之前有被复制的文件节点，则覆盖之

    nodeX->child=curNode->child;
    nodeX->child->flags|=NODE_IS_CUT;
    //区分复制和剪切
}

/*
    函数功能：激活粘贴函数(非覆盖)
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制/剪切的节点
    返回值：无
*/
void ISetPaste(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;
    IFileNode *tempNode=nodeX->child->child;
    char temp1[PATH_LEN],temp2[PATH_LEN];

    IGetAbsolutePath(curNode->child,temp1);
    while(tempNode)
    {
        if(tempNode->flags&2 && IisFolder(tempNode))
        {
            IGetAbsolutePath(tempNode,temp2);
            if(IisChild(temp1,temp2)||!strcmp(temp1,temp2))
            {
                setcolor(DRM_RED);
                outtextxy(400+DF,752+DF,"Failed");
                IWarningBeep();
                delay(1500);
                return;
            }
            break;
        }
        tempNode=tempNode->next;
    }
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(DRM_RED);
    outtextxy(900+DF,753+DF,"Pasting...");

    Icplr(nodeX->child,curNode->child,UNFORCED);
    //复制文件节点

    if(nodeX->child->flags&NODE_IS_CUT)
        Irmlr(nodeX->child);
    //如果是剪切，则删除源文件节点
    
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,753+DF,1000+DF,765+DF);
}

/*
    函数功能：激活粘贴函数(覆盖)
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制/剪切的节点
    返回值：无
*/
void ISetPasteF(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;
    
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(DRM_RED);
    outtextxy(900+DF,753+DF,"Pasting...");

    Icplr(nodeX->child,curNode->child,FORCED);
    //复制文件节点

    if(nodeX->child->flags&NODE_IS_CUT)
        Irmlr(nodeX->child);
    //如果是剪切，则删除源文件节点
    
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,753+DF,1000+DF,765+DF);
}
/*
    函数功能：粘贴确认函数
    输入参数：flagx——菜单状态位, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetPasteComfirm(IFileNode *flagx,IFileNode *null)
{
    FILE *fp=fopen("C:\\DOSRES\\ETC\\TEMP.TXT","r");
    char *menuFlag=(char*)flagx;
    
    ICheckNull(null);
    if(fgetc(fp)=='f')
    {
        (*menuFlag)&=FLAG_DEL_UNCOVER;
        (*menuFlag)|=FLAG_ADD_COVER;
    }
    else
    {
        (*menuFlag)&=FLAG_DEL_COVER;
        (*menuFlag)|=FLAG_ADD_UNCOVER;
    }
    fclose(fp);
    //激活确认覆盖窗口
}

/*
    函数功能：粘贴检查函数
    输入参数：cur——当前节点, X——辅助节点
    输出参数：无
    返回值：无
*/
void ISetPasteCheck(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;
    IFileNode *tempNode=nodeX->child->child;
    FILE *fp=fopen("C:\\DOSRES\\ETC\\TEMP.TXT","w+");
    char temp[PATH_LEN],ttemp[PATH_LEN];

    IGetAbsolutePath(curNode->child,temp);
    Icd(temp);
    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            if(ISearchPath(tempNode->file.name))
            {
                IGetAbsolutePath(nodeX->child,ttemp);
                if(strcmp(temp,ttemp))
                {
                    fputc('f',fp);      
                    fclose(fp);
                    return;
                }
            }    
        }
        tempNode=tempNode->next;
    }
    fputc('u',fp);
    fclose(fp);
}


/*
    函数功能：激活删除函数
    输入参数：cur——当前节点
    输出参数：X——辅助节点指针，用于保存被复制/剪切的节点
    返回值：无
*/
void ISetDelete(IFileNode *cur,IFileNode *X)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    IFileNodePointer *nodeX=(IFileNodePointer*)X;
    IFileNodePointer *tempNode=NULL,*lastNode=NULL;
    char path1[PATH_LEN],path2[PATH_LEN];

    tempNode=curNode;
    while(tempNode->next)
        tempNode=tempNode->next;

    IGetAbsolutePath(curNode->child,path2);
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);
        if(IisChild(path1,path2))
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        tempNode=lastNode;
    }

    nodeX->child=NULL;
    //辅助节点置零
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(DRM_RED);
    outtextxy(900+DF,753+DF,"Deleting...");

    Irmlr(curNode->child);
    //激活删除函数
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,753+DF,1000+DF,765+DF);
}

/*
    函数功能：激活删除函数
    输入参数：flagx——菜单状态位, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetDeleteComfirm(IFileNode *flagx,IFileNode *null)
{
    char *menuFlag=(char*)flagx;

    ICheckNull(null);
    (*menuFlag)|=FLAG_ADD_DEL_COMFIRM;
    //激活确认删除窗口
}

/*
    函数功能：激活重命名函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetRename(IFileNode *cur,IFileNode *flag)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    char *menuFlag=(char*)flag;
    IFileNode *tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(!(tempNode->flags&NODE_IS_SELECTED))
    {
        i++;
        tempNode=tempNode->next;
    }
    i=i%30;
    //找到被选中的文件节点
    
    strcpy(temp,tempNode->file.name);
    if((*menuFlag)&FLAG_IS_VIEW11)
        IGetString(276+DF+(i%6)*102,116+85+DF+(i/6)*112,150,temp,RENAME_STR);
    else
        IGetString(254+DF,110+DF+20*i,150,temp,RENAME_STR);
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
void ISetNewFile(IFileNode *cur,IFileNode *flag)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    char *menuFlag=(char*)flag;
    IFileNode *tempNode=curNode->child->child;
    int i=0;
    char temp[20],tempStr1[PATH_LEN],tempStr2[PATH_LEN];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    if(!i)
    {
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(500+DF,200+DF,1000+DF,300+DF);
    }
    else if(!(i%30)) 
        i=30;
    else
        i=i%30;
    //找到被选中的文件节点
    if(*menuFlag&FLAG_IS_VIEW11)
    {
        if(i==30)
            IGetString(786+DF,669+DF,150,temp,NEWFILE_STR);
        else
            IGetString(276+DF+(i%6)*102,116+85+DF+(i/6)*112,150,temp,NEWFILE_STR);
    }
    else
        IGetString(254+DF,110+20*i+DF,150,temp,NEWFILE_STR);
    //获取新文件名

    if(temp[0])
    {
        if(!Inew(curNode->child,temp))
        {
            setcolor(DRM_RED);
            outtextxy(400+DF,752+DF,"Failed");
            IWarningBeep();
            delay(1500);
        }
    }    
        //如果创建文件失败
}

/*
    函数功能：激活创建新文件夹函数
    输入参数：cur——当前节点, null——用于占位
    输出参数：无
    返回值：无
*/
void ISetNewFolder(IFileNode *cur,IFileNode *flag)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;
    char *menuFlag=(char*)flag;
    IFileNode *tempNode=curNode->child->child;
    int i=0;
    char temp[20];

    while(tempNode)
    {
        i++;
        tempNode=tempNode->next;
    }
    if(!i)
    {
        setfillstyle(SOLID_FILL,DRM_WHITE);
        bar(500+DF,200+DF,1000+DF,300+DF);
    }
    else if(!(i%30)) 
        i=30;
    else
        i=i%30;
    //找到被选中的文件节点
    if(*menuFlag&FLAG_IS_VIEW11)
    {
        if(i==30)
            IGetString(786+DF,669+DF,150,temp,NEWFILE_STR);
        else
            IGetString(276+DF+(i%6)*102,116+85+DF+(i/6)*112,150,temp,NEWFILE_STR);
    }
    else
        IGetString(254+DF,110+20*i+DF,150,temp,NEWFILE_STR);
    //获取新文件名

    if(temp[0])
        if(!Imkdir(curNode->child,temp))
        {
            setcolor(DRM_RED);
            outtextxy(400+DF,752+DF,"Failed");
            IWarningBeep();
            delay(1500);
        }
        //如果创建文件夹失败
}