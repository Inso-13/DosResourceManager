#if !defined(__ITYPE_H)
#define __ITYPE_H

#include"IBase.h"

typedef enum IBool{false,true} IBool;   //�����ͱ�����false=0��true=1


typedef struct IFile    //�ļ��ṹ
{
    char name[13];  //�ļ���
    char type[4];   //�ļ����ͣ�һ���ļ�Ϊ��׺����Ŀ¼Ϊ0���رգ���1���򿪣�
    unsigned time;      //�޸�ʱ�� 
    unsigned date;      //�޸�����
    int size;      //�ļ���С����λKB
}IFile;

typedef struct IFileNode    //�ļ��ڵ� //41->48
{
    IFile file;                 //�ļ�
    char flags;                 // bit0 �Ƿ�ȴ�cut,bit1 �Ƿ�ѡ��,bit2 �Ƿ�Ϊ����ͷ,bit 3 �Ƿ�ֻ��,bit 4 �Ƿ�����
    int hasFile;                //�������ļ���
    int hasFolder;              //�������ļ�����
    struct IFileNode * pre;     //ǰһ���ڵ㣨���������ͷ����preΪ���ڵ㣩
    struct IFileNode * next;    //��һ���ڵ�
    struct IFileNode * child;   //������ͷ
}IFileNode;

typedef struct IFileNodePointer  //                a->b->c
{
    struct IFileNodePointer * pre;
    struct IFileNodePointer * next;
    IFileNode * child;
    int wait;
}IFileNodePointer;

typedef struct IPathList
{
    struct IPathList *next;
    char path[60];
}IPathList;

typedef struct IEvent   //�¼�
{
    int x1;
    int y1;
    int x2;
    int y2;
    int type;               //�������
    void (*pfun)(IFileNode *,IFileNode *);     //�ۺ��� (void*) (int*) 1�ֽ� ǿת 
    IFileNode * node0;      //�ۺ����ĵ�һ������
    IFileNode * node1;      //�ۺ����ĵڶ�������
    char change;            //�ı��λ��
}IEvent;

typedef struct IEventStackNode      //�¼�ջ
{
    IEvent event;
    struct IEventStackNode * next;
}IEventStackNode;

#endif