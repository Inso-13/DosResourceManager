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
    struct IFileNode far* pre;
    struct IFileNode far* next;
    struct IFileNode far* child;
}IFileNode;

typedef struct IEvent
{
    int key;
    int x1;
    int y1;
    int x2;
    int y2;
    void (*pfun)(IFileNode far*);
    IFileNode far* target;
}IEvent;

typedef struct IEventStackNode
{
    IEvent event;
    struct IEventStackNode far* next;
}IEventStackNode;

void IFileNodeSetNull(IFileNode far* node);
IFileNode far* IFindParent(IFileNode far* child);
IBool IAddChild(IFileNode far* parent,IFileNode far* child);// 1 for added
IBool IAddSibling(IFileNode far* pre,IFileNode far* next);// 1 for added
void IDelFilelist(IFileNode far* root);
IEventStackNode far* IInitEventStack(void);
void IEventStackPush(IEventStackNode far* top,IEvent newEvent);
IBool IEventStackPop(IEventStackNode far* top);// 1 for poped
IBool IEventStackActive(IEventStackNode far* top,int x,int y);// 1 for active
void IDelStack(IEventStackNode far* top);

#endif