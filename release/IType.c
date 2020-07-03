#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"IType.h"

IBool IAddChild(IFileNode* parent,IFile* fchild)
{
    IFileNode *child=(IFileNode*)malloc(sizeof(IFileNode));
    IFileNode *temp=NULL;
    child->file=*fchild;
    child->next=NULL;
    if(!strcmp(parent->file.name,"folder"))
        return 0;
    if(parent->child)
    {
        temp=parent->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=child;
        child->pre=temp;
        child->ishead=0;
    }
    else
    {
        parent->child=child;
        child->pre=parent;
        child->ishead=1;
    }
    child->next=NULL;
    child->child=NULL;
    printf("%s is added as %s's child\n",child->file.name,parent->file.name);
    printf("its path is %c:\\%s%s\n",child->file.disk,strcmp(child->file.path,".")?child->file.path:"",child->file.name);
    return true;
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
IBool IAddSibling(IFileNode* pre,IFile* next)
{
    IFileNode *temp=pre;
    
    while(!temp->ishead)
    {
        temp=temp->pre;
    }
    return IAddChild(temp->pre,next);
}
void IInitEventStack(IEventStackNode* top)
{
    top=(IEventStackNode*)malloc(sizeof(IEventStackNode));
    top->next=NULL;
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
    return 1;
}
