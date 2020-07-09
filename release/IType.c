#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"IType.h"
#define DB

void IFileNodeSetNull(IFileNode* node)
{
    node->isHead=0;
    node->isSelect=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
IFileNode* IFindParent(IFileNode* child)
{
    IFileNode *temp=child;
    
    while(!temp->isHead)
    {
        temp=temp->pre;
    }
    return temp->pre;
}
IBool IAddChild(IFileNode* parent,IFileNode* child)
{
    IFileNode *temp=NULL;
    if(!parent) return 0;
    if(!strcmp(child->file.name,""))
    {
        free(child);
        return 0;
    }
    if(parent->child)
    {
        temp=parent->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=child;
        child->pre=temp;
        child->isHead=0;
    }
    else
    {
        parent->child=child;
        child->pre=parent;
        child->isHead=1;
    }
#ifdef  DB
    printf("%s is added as %s's child\n",child->file.name,parent->file.name);
    printf("its path is %s\n",child->file.path);
#endif
    return 1;
}
void IDelFilelist(IFileNode* root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
        root->child=NULL;
    }
    if(root->next)
    {
        IDelFilelist(root->next);
        root->next=NULL;
    }
#ifdef  DB
    printf("%s is freed\n",root->file.name);
#endif
    free(root);
    root=NULL;
}
IBool IAddSibling(IFileNode* pre,IFileNode* next)
{
    return IAddChild(IFindParent(pre),next);
}
IEventStackNode* IInitEventStack(void)
{
    IEventStackNode* top=(IEventStackNode*)malloc(sizeof(IEventStackNode));
#ifdef  DB
    if(top==NULL)
    {
        printf("not enough memory\n");
        exit(-1);
    }
#endif
    top->next=NULL;
    return top;
}
void IEventStackPush(IEventStackNode* top,IEvent newEvent)
{
    IEventStackNode* q=(IEventStackNode*)malloc(sizeof(IEventStackNode));
#ifdef  DB
    if(q==NULL)
        printf("not enough memory\n");
#endif
    q->event = newEvent;
    q->next = top->next;
    top->next = q;
}
IBool IEventStackPop(IEventStackNode* top)
{
    IEventStackNode* q;

    if(!q->next)
        return 0;
    q = top->next;
    top->next = q->next;
    free(q);
    q = NULL;
    return 1;
}
IBool IEventStackActive(IEventStackNode* top,int x,int y)
{
    IEventStackNode* temp=top->next;
    
    while(temp)
    {
        if(temp->event.key)
        {
            if(kbhit()==temp->event.key)
            {
                temp->event.pfun(temp->event.target);
            }
            if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2)
            {
                temp->event.pfun(temp->event.target);
                return 1;
            }   
        }
        else
        {
            if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2)
            {
                temp->event.pfun(temp->event.target);
                return 1;
            }
            else
                temp=temp->next;
        }
    }
    return 0;
}
void IDelStack(IEventStackNode* top)
{
    while(top->next)
    {
        IEventStackPop(top);
    }
    free(top);
}