#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"IType.h"

IBool IFileNodeSetNull(IFileNode* node)
{
    node->isHead=0;
    node->isSelect=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
    return 1;
}
IBool IAddChild(IFileNode* parent,IFileNode* child)
{
    IFileNode *temp=NULL;
    if(!strcmp(child->file.name,""))
    {
        free(child);
        return 1;
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
    printf("%s is added as %s's child\n",child->file.name,parent->file.name);
    printf("its path is %s\n",child->file.path);
    return 1;
}
IBool IDelFilelist(IFileNode* root)
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
    printf("%s is freed\n",root->file.name);
    free(root);
    root=NULL;
    return 1;
}
IBool IAddSibling(IFileNode* pre,IFileNode* next)
{
    IFileNode *temp=pre;
    
    while(!temp->isHead)
    {
        temp=temp->pre;
    }
    return IAddChild(temp->pre,next);
}
IEventStackNode* IInitEventStack(void)
{
    IEventStackNode* top=(IEventStackNode*)malloc(sizeof(IEventStackNode));
    top->next=NULL;
    return top;
}
IBool IEventStackPush(IEventStackNode* top,IEvent newEvent)
{
    IEventStackNode* q=(IEventStackNode*)malloc(sizeof(IEventStackNode));
    q->event = newEvent;
    q->next = top->next;
    top->next = q;
    return 1;
}
IBool IEventStackPop(IEventStackNode* top)
{
    IEventStackNode* q;
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
                temp->event.pfun();
            }
            if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2)
            {
                temp->event.pfun();
                return 1;
            }   
        }
        else
        {
            if(x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2)
            {
                temp->event.pfun();
                return 1;
            }
            else
                temp=temp->next;
        }
    }
    return 0;
}
IBool IDelStack(IEventStackNode* top)
{
    while(top->next)
    {
        IEventStackPop(top);
    }
    free(top);
    return 1;
}
