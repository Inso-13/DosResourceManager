#if !defined(__ITYPE_H)
#define __ITYPE_H

#include"IBase.h"

typedef enum IBool{false,true} IBool;   //布尔型变量，false=0，true=1


typedef struct IFile    //文件结构
{
    char name[13];  //文件名
    char type[4];   //文件类型，一般文件为后缀名，目录为0（关闭）或1（打开）
    unsigned time;      //修改时间
    unsigned date;      //修改日期
    int size;      //文件大小，单位KB
}IFile;

typedef struct IFileNode    //文件节点
{
    IFile file;                 //文件
    char flags;                 // bit0 是否等待cut,bit1 是否被选中,bit2 是否为链表头,bit 3 是否只读,bit 4 是否隐藏
    char del;                   //空间回收控制
    int hasFile;                //包含的文件数
    int hasFolder;              //包含的文件夹数
    struct IFileNode * pre;     //前一个节点（如果是链表头，则pre为父节点）
    struct IFileNode * next;    //后一个节点
    struct IFileNode * child;   //子链表头
}IFileNode;

typedef struct IFileNodePointer
{
    struct IFileNodePointer * pre;
    struct IFileNodePointer * next;
    IFileNode * child;
    int wait;
}IFileNodePointer;

typedef struct IEvent   //事件
{
    int x1;
    int y1;
    int x2;
    int y2;
    int type;               //点击类型
    void (*pfun)(IFileNode *,IFileNode *);     //槽函数
    IFileNode * node0;      //槽函数的第一个参数
    IFileNode * node1;      //槽函数的第二个参数
    char change;            //改变的位置
}IEvent;

typedef struct IEventStackNode      //事件栈
{
    IEvent event;
    struct IEventStackNode * next;
}IEventStackNode;

#endif