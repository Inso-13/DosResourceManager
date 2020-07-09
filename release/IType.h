#if !defined(__ITYPE_H)
#define __ITYPE_H

typedef enum IBool{false,true} IBool;

typedef struct IDate
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
}IDate;

typedef struct IFile
{
    char name[20];
    IDate date;
    char type[5];
    long size;
    char path[50];
}IFile;

typedef struct IFileNode
{
    IFile file;
    IBool isSelect;
    IBool isHead;
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
    void (*pfun)(IFileNode*);
    IFileNode* target;
}IEvent;

typedef struct IEventStackNode
{
    IEvent event;
    struct IEventStackNode* next;
}IEventStackNode;

void IFileNodeSetNull(IFileNode* node);
IFileNode* IFindParent(IFileNode* child);
IBool IAddChild(IFileNode* parent,IFileNode* child);// 1 for added
IBool IAddSibling(IFileNode* pre,IFileNode* next);// 1 for added
void IDelFilelist(IFileNode* root);
IEventStackNode* IInitEventStack(void);
void IEventStackPush(IEventStackNode* top,IEvent newEvent);
IBool IEventStackPop(IEventStackNode* top);// 1 for poped
IBool IEventStackActive(IEventStackNode* top,int x,int y);// 1 for active
void IDelStack(IEventStackNode* top);

#endif