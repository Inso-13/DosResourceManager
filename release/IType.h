#if !defined(__ITYPE_H)
#define __ITYPE_H

#include"IBase.h"

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
    char name[13];
    IDate date;
    char type[4];
    long size;
    char path[40];
    IBool readOnly;
    IBool isHidden;
}IFile;

typedef struct IFileNode
{
    IFile file;
    IBool isSelect;
    IBool isHead;
    int hasFile;
    int hasFolder;
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
    int type;
    void (*pfun)(IFileNode far*,IFileNode far*);
    IFileNode far* node0;
    IFileNode far* node1;
}IEvent;

typedef struct IEventStackNode
{
    IEvent event;
    struct IEventStackNode far* next;
}IEventStackNode;

#endif