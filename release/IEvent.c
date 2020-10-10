/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：与事件相关的函数
 **************************************************
 */

#include"IEvent.h"

/*
    函数功能：在堆中生成新的事件栈
    输入参数：无
    输出参数：无
    返回值：返回全新的事件栈
*/
IEventStackNode * IInitEventStack(void)
{
    IEventStackNode * top=(IEventStackNode *)malloc(sizeof(IEventStackNode));
    if(top==NULL)
    {
#ifdef DB  //如果是在调试模式下
        printf("not enough memory in IInitEventStack\n");
#endif
        IQuit();
    }   //内存检查
    top->next=NULL;     //初始化栈顶
    return top;
}

/*
    函数功能：事件入栈，top自动改变
    输入参数：top——事件栈顶, newEvent——需要入栈的事件
    输出参数：无
    返回值：无
*/
void IEventStackPush(IEventStackNode * top,IEvent newEvent)
{
    IEventStackNode * q=(IEventStackNode *)malloc(sizeof(IEventStackNode));

    if(q==NULL)
    {
#ifdef DB  //如果是在调试模式下
        printf("not enough memory in IEventStackPush\n");
#endif
        IQuit();
    }   //内存检查
    q->event = newEvent;
    q->next = top->next;
    top->next = q;  //入栈
}

/*
    函数功能：事件出栈，top自动改变
    输入参数：top——事件栈顶, n——需要出栈的次数
    输出参数：无
    返回值：正常返回1，事件栈高度不足n则返回0
*/
int IEventStackPop(IEventStackNode * top,int n)
{
    IEventStackNode *q=NULL;
    while(n--)      //出栈n次
    {
        q=top;
        if(!q->next)
            return 0;       //不足n返回0
        q = top->next;
        top->next = q->next;
        q->next = NULL;
        free(q);    //释放内存
    }
    return 1;       //正常返回1
}

/*
    函数功能：根据事件激活槽函数
    输入参数：top——事件栈顶, (x,y)——点击坐标, type点击类型
    输出参数：无
    返回值：返回change(需要更新的view)
*/
char IEventStackActive(IEventStackNode * top,int x,int y,int type)
{
    IEventStackNode * temp=top->next;
    
    while(temp)
    {
        if(temp->event.type==-1||(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type)))
        {   //如果完全符合点击条件
            temp->event.pfun(temp->event.node0,temp->event.node1);      //激活槽函数
            if(temp->event.change<0)
            {
                temp=temp->next;
                continue;   //级联向下查询
            }
            else
                return temp->event.change;  //返回需要改变的视图值
        }
        else
            temp=temp->next;    //不符合点击条件，继续查找
    }
    return 0;   //未激活槽函数，返回0
}

/*
    函数功能：析构栈
    输入参数：top——事件栈顶
    输出参数：无
    返回值：无
*/
void IDelStack(IEventStackNode * top)
{
    while(top->next)
        IEventStackPop(top,5);    //不断出栈

    free(top);  //释放栈顶
}


/*
    函数功能：设置(初始化)事件
    输入参数：event——待初始化的事件, 其他——事件的属性
    输出参数：无
    返回值：无
*/
void ISetEvent(IEvent* event,int x1,int y1,int x2,int y2,int type,void (*pfun)(IFileNode *,IFileNode *),IFileNode * node0,IFileNode * node1,char change)
{
    event->x1=x1;
    event->y1=y1;
    event->x2=x2;
    event->y2=y2;
    event->type=type;
    event->pfun=pfun;
    event->node0=node0;
    event->node1=node1;
    event->change=change;
}