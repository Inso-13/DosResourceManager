/*
    版本号：1.0
    作者：郭一菲
    生成日期：2020-9-4
    说明：与事件相关的函数
*/


#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>
#include"IQuit.h"
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
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
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
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
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
IBool IEventStackPop(IEventStackNode * top,int n)
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
        free(q);
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
        if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type))
        {
            temp->event.pfun(temp->event.node0,temp->event.node1);      //激活槽函数
            if(temp->event.change<0)
            {
                temp=temp->next;
                continue;
            }
            else
                return temp->event.change;
        }
        else
            temp=temp->next;
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
        IEventStackPop(top,5);  
    //不断出栈

    free(top);
    //释放栈顶
}