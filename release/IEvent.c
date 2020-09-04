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
    top->next=NULL;     //��ʼ��ջ��
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
    top->next = q;      //��ջ
}
IBool IEventStackPop(IEventStackNode * top,int n)
{
    IEventStackNode *q=NULL;
    while(n--)      //��ջn��
    {
        q=top;
        if(!q->next)
            return 0;       //����n����0
        q = top->next;
        top->next = q->next;
        q->next = NULL;
        free(q);
    }
    return 1;       //��������1
}
char IEventStackActive(IEventStackNode * top,int x,int y,int type)
{
    IEventStackNode * temp=top->next;
    
    while(temp)
    {
        if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type))
        {
            temp->event.pfun(temp->event.node0,temp->event.node1);      //����ۺ���
            return temp->event.change;
        }
        else
            temp=temp->next;
    }
    return 0;   //δ����ۺ���������0
}
void IDelStack(IEventStackNode * top)
{
    while(top->next)
        IEventStackPop(top,5);  //���ϳ�ջ
    free(top);  //�ͷ�ջ��
}