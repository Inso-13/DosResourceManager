#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>
#include"IEvent.h"

IEventStackNode far* IInitEventStack(void)
{
    IEventStackNode far* top=(IEventStackNode far*)farmalloc(sizeof(IEventStackNode));
    if(top==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
    top->next=NULL;
    return top;
}
void IEventStackPush(IEventStackNode far* top,IEvent newEvent)
{
    IEventStackNode far* q=(IEventStackNode far*)farmalloc(sizeof(IEventStackNode));
    if(q==NULL)
    {
#ifdef  DB
        printf("not enough memory\n");
#endif
        IQuit();
    }
    q->event = newEvent;
    q->next = top->next;
    top->next = q;
}
IBool IEventStackPop(IEventStackNode far* top,int n)
{
    IEventStackNode far* q;
    while(n--)
    {
        if(!q->next)
        return 0;
        q = top->next;
        top->next = q->next;
        farfree(q);
        q = NULL;
    }
    return 1;
}
IBool IEventStackActive(IEventStackNode far* top,int x,int y,int type)
{
    IEventStackNode far* temp=top->next;
    
    while(temp)
    {
        if((!(temp->event.key)||kbhit()==temp->event.key)&&x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type))
        {
            temp->event.pfun(temp->event.node0,temp->event.node1);
            return 1;
        }
        else
        {
            temp=temp->next;
        }
    }
    return 0;
}
void IDelStack(IEventStackNode far* top)
{
    while(top->next)
    {
        IEventStackPop(top,1);
    }
    farfree(top);
}