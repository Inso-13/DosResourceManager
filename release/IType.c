#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"IUtility.h"
#include"IType.h"

void IFileNodeSetNull(IFileNode far* node)
{
    node->isHead=0;
    node->isSelect=0;
    node->hasFile=0;
    node->hasFolder=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
IFileNode far* IFindParent(IFileNode far* child)
{
    IFileNode far* temp=child;
    
    while(!temp->isHead)
    {
        temp=temp->pre;
    }
    return temp->pre;
}
IBool IAddChild(IFileNode far* parent,IFileNode far* child)
{
    IFileNode far* temp=NULL;
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
void IDelFilelist(IFileNode far* root)
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
    IFileNodeSetNull(root);
    free(root);
    root=NULL;
}
IBool IAddSibling(IFileNode far* pre,IFileNode far* next)
{
    return IAddChild(IFindParent(pre),next);
}
IEventStackNode far* IInitEventStack(void)
{
    IEventStackNode far* top=(IEventStackNode far*)malloc(sizeof(IEventStackNode));
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
    IEventStackNode far* q=(IEventStackNode far*)malloc(sizeof(IEventStackNode));
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
IBool IEventStackPop(IEventStackNode far* top)
{
    IEventStackNode far* q;

    if(!q->next)
        return 0;
    q = top->next;
    top->next = q->next;
    free(q);
    q = NULL;
    return 1;
}
IBool IEventStackActive(IEventStackNode far* top,int x,int y,int type)
{
    IEventStackNode far* temp=top->next;
    
    while(temp)
    {
        if((!(temp->event.key)||kbhit()==temp->event.key)&&x>temp->event.x1&&x<temp->event.x2&&y>temp->event.y1&&y<temp->event.y2&&temp->event.type==type)
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
        IEventStackPop(top);
    }
    free(top);
}