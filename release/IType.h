#if !defined(__ITYPE_H)
#define __ITYPE_H

#include "IDate.h"
#include "IFile.h"

typedef enum IBool{false,true} IBool;

typedef struct IFileNode
{
    IFile file;
    IBool ishead;
    struct IFileNode* pre;
    struct IFileNode* next;
    struct IFileNode* child;
}IFileNode;
typedef struct IEvent
{
    int key;
    int x1;
    int y1;
    int x2;
    int y2;
    void (*pfun)(void);
}IEvent;

typedef struct IEventStackNode
{
    IEvent event;
    struct IEventStackNode* next;
}IEventStackNode;


IBool IAddChild(IFileNode* parent,IFile* fchild);
IBool IAddSibling(IFileNode* pre,IFile* next);
IBool IDelFilelist(IFileNode* root);
void IInitEventStack(IEventStackNode* top);
IBool IEventStackPush(IEventStackNode* top,IEvent newEvent);
IBool IEventStackPop(IEventStackNode* top);
IBool IEventStackActive(IEventStackNode* top,int x,int y);
IBool IDelStack(IEventStackNode* top);

#endif