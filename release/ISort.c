/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：主要定义排序函数
 **************************************************
 */


#include"ISort.h"

/*
    函数功能：排序
    输入参数：parent——父节点, fun——用于确定顺序的函数指针
    输出参数：无
    返回值：无
*/
void ISort(IFileNode *parent,int (*fun)(IFileNode*,IFileNode*))
{
    IFileNode *tempNode=parent->child;
    int n=0,i,j,u;

    while(tempNode)
    {
        n++;
        tempNode=tempNode->next;
    }    //计算链表的长度

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)    
        {
            tempNode=parent->child;
            for(u=0;u<j;u++)
                tempNode=tempNode->next;
            if(fun(tempNode,tempNode->next)>0)
                IExchangeFileNode(tempNode,tempNode->next); //交换节点
        }
    }   //冒泡排序
}

/*
    函数功能：按时间升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortDateUp(IFileNode *node1,IFileNode *node2)
{
    int t;  

    t=(int)node1->file.date-(int)node2->file.date;
    if(t) return t; //先比较日期
    t=(int)node1->file.time-(int)node2->file.time;
    return t;   //后比较时间
}

/*
    函数功能：按时间降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortDateDown(IFileNode *node1,IFileNode *node2)
{
    int t;

    t=(int)node2->file.date-(int)node1->file.date;
    if(t) return t; //先比较日期
    t=(int)node2->file.time-(int)node1->file.time;
    return t; //后比较时间
}

/*
    函数功能：按文件大小升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortSizeUp(IFileNode *node1,IFileNode *node2)
{
    if(IisFolder(node1))
    {
        if(IisFolder(node2))
            return 0;
        else 
            return -1;
    }   
    else if(IisFolder(node2))
        return 1;   //文件夹最小

    else if(node1->file.size<0)
    {
        if(node2->file.size<0)
            return 0;
        else 
            return 1;
    }
    else if(node2->file.size<0)
        return -1;  //超过32K的文件最大
    else
        return node1->file.size-node2->file.size;
}

/*
    函数功能：按文件大小降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortSizeDown(IFileNode *node1,IFileNode *node2)
{
    if(IisFolder(node1))
    {
        if(IisFolder(node2))
            return 0;
        else 
            return 1;
    }
    else if(IisFolder(node2))
        return -1;  //文件夹最小
    else if(node1->file.size<0)
    {
        if(node2->file.size<0)
            return 0;
        else 
            return -1;
    }
    else if(node2->file.size<0)
        return 1;   //超过32K的文件最大
    else
        return node2->file.size-node1->file.size;
}

/*
    函数功能：按文件名升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortNameUp(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node1->file.name,node2->file.name);
}

/*
    函数功能：按文件名降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortNameDown(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node2->file.name,node1->file.name);
}

/*
    函数功能：按文件类型升序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortTypeUp(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node1->file.type,node2->file.type);
}

/*
    函数功能：按文件类型降序排序
    输入参数：(node1,node2)——需要比较的两个节点
    输出参数：无
    返回值：无
*/
int ISortTypeDown(IFileNode *node1,IFileNode *node2)
{
    return strcmp(node2->file.type,node1->file.type);
}

/*
    函数功能：打开排序菜单
    输入参数：flag——排序菜单打开标志, null——用于占位
    输出参数：无
    返回值：无
*/
void ISortMenuActive(IFileNode *flag,IFileNode *null)
{
    char *n=(char*)flag;   
    
    ICheckNull(null);
    *n|=1;  //将打开标志置为1
}

/*
    函数功能：激活排序函数
    输入参数：cur——当前节点, pfun——用于确定顺序的函数指针，类似于lambda
    输出参数：无
    返回值：无
*/
void ISortActive(IFileNode *cur,IFileNode *pfun)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;   //当前节点
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;  //比较函数指针
    
    if(curNode->child->child)
        ISort(curNode->child,fun);  //激活排序函数
}

/*
    函数功能：排序时,用于交换两个兄弟节点在链表中的顺序
    输入参数：(node1,node2)——两个需要交换的节点
    输出参数：无
    返回值：无
*/
void IExchangeFileNode(IFileNode *node1,IFileNode *node2)
{
    if(node1->flags&NODE_IS_HEAD)  //如果node1是链表头
    {
        node1->flags&=NODE_DEL_HEAD;
        node2->flags|=NODE_ADD_HEAD;
        node1->pre->child=node2;
        node2->pre=node1->pre;
        if(node2->next)
        {
            node2->next->pre=node1;
            node1->next=node2->next;
        }
        else 
            node1->next=NULL;
        node2->next=node1;
        node1->pre=node2;
    }
    else //如果node1不是链表头
    {
        if(node2->next)
        {
            node2->next->pre=node1;
            node1->next=node2->next;
        }
        else
            node1->next=NULL;
        node1->pre->next=node2;
        node2->pre=node1->pre;
        node2->next=node1;
        node1->pre=node2;
    }
}