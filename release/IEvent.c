/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵�������¼���صĺ���
 **************************************************
 */

#include"IEvent.h"

/*
    �������ܣ��ڶ��������µ��¼�ջ
    �����������
    �����������
    ����ֵ������ȫ�µ��¼�ջ
*/
IEventStackNode *IInitEventStack(void)
{
    IEventStackNode *top=(IEventStackNode*)malloc(sizeof(IEventStackNode));
    if(top==NULL)
    {
#ifdef DB  //������ڵ���ģʽ��
        printf("not enough memory in IInitEventStack\n");
#endif
        IQuit();
    }   //�ڴ���
    top->next=NULL;     //��ʼ��ջ��
    return top;
}

/*
    �������ܣ��¼���ջ��top�Զ��ı�
    ���������top�����¼�ջ��, newEvent������Ҫ��ջ���¼�
    �����������
    ����ֵ����
*/
void IEventStackPush(IEventStackNode *top,IEvent newEvent)
{
    IEventStackNode *q=(IEventStackNode*)malloc(sizeof(IEventStackNode));

    if(q==NULL)
    {
#ifdef DB  //������ڵ���ģʽ��
        printf("not enough memory in IEventStackPush\n");
#endif
        IQuit();
    }   //�ڴ���
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
int IEventStackPop(IEventStackNode *top,int n)
{
    IEventStackNode *q=NULL;
    while(n--)      //��ջn��
    {
        if(!top->next)
            return 0;       //����n����0
        q = top->next;
        top->next = q->next;
        q->next = NULL;
        free(q);    //�ͷ��ڴ�
    }
    return 1;       //��������1
}

/*
    �������ܣ������¼�����ص�����
    ���������top�����¼�ջ��, (x,y)�����������, type�������
    �����������
    ����ֵ������change(��Ҫ���µ�view)
*/
char IEventStackActive(IEventStackNode *top,int x,int y,int type)
{
    IEventStackNode *temp=top->next;
    
    while(temp)
    {
        if(temp->event.type==-1||(x>temp->event.x1&&x<temp->event.x2&&\
        y>temp->event.y1&&y<temp->event.y2&&(temp->event.type&type)))
        {   //�����ȫ���ϵ������
            temp->event.pfun(temp->event.node0,temp->event.node1);      //����ص�����
            if(temp->event.change<0)
            {
                temp=temp->next;
                continue;   //�������²�ѯ
            }
            else
                return temp->event.change;  //������Ҫ�ı����ͼֵ
        }
        else
            temp=temp->next;    //�����ϵ����������������
    }
    return 0;   //δ����ص�����������0
}

/*
    �������ܣ�����ջ
    ���������top�����¼�ջ��
    �����������
    ����ֵ����
*/
void IDelStack(IEventStackNode *top)
{
    while(top->next)
        IEventStackPop(top,5);    //���ϳ�ջ

    free(top);  //�ͷ�ջ��
}


/*
    �������ܣ�����(��ʼ��)�¼�
    ���������event��������ʼ�����¼�, ���������¼�������
    �����������
    ����ֵ����
*/
void ISetEvent(IEvent *event,int x1,int y1,int x2,int y2,int type,\
void (*pfun)(IFileNode*,IFileNode*),IFileNode *node0,IFileNode *node1,char change)
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