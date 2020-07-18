#if !defined(__ITYPE_H)
#define __ITYPE_H

#include"IBase.h"

typedef enum IBool{false,true} IBool;   //布尔型变量，false=0，true=1

typedef struct IDate    //时间结构
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
}IDate;

typedef struct IFile    //文件结构
{
    char name[13];  //文件名
    IDate date;     //文件修改日期
    char type[4];   //文件类型，一般文件为后缀名，目录为0（关闭）或1（打开）
    long size;      //文件大小，单位KB
    char path[40];  //文件虚拟绝对路径
    IBool readOnly; //是否只读
    IBool isHidden; //是否隐藏
}IFile;

typedef struct IFileNode    //文件节点
{
    IFile file;                 //文件
    IBool isSelect;             //是否被选中
    IBool isHead;               //是否为链表头
    int hasFile;                //包含的文件数
    int hasFolder;              //包含的文件夹数
    struct IFileNode * pre;     //前一个节点（如果是链表头，则pre为父节点）
    struct IFileNode * next;    //后一个节点
    struct IFileNode * child;   //子链表头
}IFileNode;

typedef struct IEvent   //事件
{
    int key;            //键盘按键，如ctrl
    int x1;
    int y1;
    int x2;
    int y2;
    int type;           //点击类型
    void (*pfun)(IFileNode *,IFileNode *);     //槽函数
    IFileNode * node0;      //槽函数的第一个参数
    IFileNode * node1;      //槽函数的第二个参数
}IEvent;

typedef struct IEventStackNode      //事件栈
{
    IEvent event;
    struct IEventStackNode * next;
}IEventStackNode;

#endif