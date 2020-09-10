/*
    �汾�ţ�1.0
    ���ߣ���һ��
    �������ڣ�2020-9-4
    ˵�������¼���صĺ���
*/


#include<CONIO.H>
#include<STDIO.H>
#include<ALLOC.H>
#include"IQuit.h"
#include"IEvent.h"

/*
    �������ܣ��ڶ��������µ��¼�ջ
    �����������
    �����������
    ����ֵ������ȫ�µ��¼�ջ
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
    top->next=NULL;     //��ʼ��ջ��
    return top;
}

/*
    �������ܣ��¼���ջ��top�Զ��ı�
    ���������top�����¼�ջ��, newEvent������Ҫ��ջ���¼�
    �����������
    ����ֵ����
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
    top->next = q;  //��ջ
}

/*
    �������ܣ��¼���ջ��top�Զ��ı�
    ���������top�����¼�ջ��, n������Ҫ��ջ�Ĵ���
    �����������
    ����ֵ����������1���¼�ջ�߶Ȳ���n�򷵻�0
*/
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

/*
    �������ܣ������¼�����ۺ���
    ���������top�����¼�ջ��, (x,y)�����������, type�������
    �����������
    ����ֵ������change(��Ҫ���µ�view)
*/
char IEventStackActive(IEventStackNode * top,int x,int y,int type)
{
    IEventStackNode * temp=top->next;
    
    while(temp)
    {
        if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type))
        {
            temp->event.pfun(temp->event.node0,temp->event.node1);      //����ۺ���
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
    return 0;   //δ����ۺ���������0
}

/*
    �������ܣ�����ջ
    ���������top�����¼�ջ��
    �����������
    ����ֵ����
*/
void IDelStack(IEventStackNode * top)
{
    while(top->next)
        IEventStackPop(top,5);  
    //���ϳ�ջ

    free(top);
    //�ͷ�ջ��
}