#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>
#include"IEvent.h"

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
    top->next = q;      //入栈
}
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
char IEventStackActive(IEventStackNode * top,int x,int y,int type)
{
    IEventStackNode * temp=top->next;
    
    while(temp)
    {
        if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type))
        {
            temp->event.pfun(temp->event.node0,temp->event.node1);      //激活槽函数
            return temp->event.change;
        }
        else
            temp=temp->next;
    }
    return 0;   //未激活槽函数，返回0
}
void IDelStack(IEventStackNode * top)
{
    while(top->next)
        IEventStackPop(top,5);  //不断出栈
    free(top);  //释放栈顶
}