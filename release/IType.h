/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ�����˼�����Ҫ�Ľṹ����������ͣ�����M(Model)��
 **************************************************
 */

#if !defined(__ITYPE_H)
#define __ITYPE_H

typedef struct IFile    //�ļ��ṹ
{
    char name[13];  //�ļ���
    char type[4];   //�ļ����ͣ�һ���ļ�Ϊ��׺����Ŀ¼Ϊ0���رգ���1���򿪣�
    unsigned time;      //�޸�ʱ�� 
    unsigned date;      //�޸�����
    int size;      //�ļ���С����λKB
}IFile;

typedef struct IFileNode    //�ļ��ڵ�
{
    IFile file;                 //�ļ�
    char flags;                 // bit0 �Ƿ�ȴ�cut,bit1 �Ƿ�ѡ��,bit2 �Ƿ�Ϊ����ͷ,bit 3 �Ƿ������ļ���,bit 4 ǿ�Ƹ����ӽڵ�
    struct IFileNode *pre;     //ǰһ���ڵ㣨���������ͷ����preΪ���ڵ㣩
    struct IFileNode *next;    //��һ���ڵ�
    struct IFileNode *child;   //������ͷ
}IFileNode;

typedef struct IFileNodePointer  //�ļ��ڵ��ָ��������Ҫ����curNode����
{
    struct IFileNodePointer *pre;      //ǰһ��
    struct IFileNodePointer *next;     //��һ��
    IFileNode *child;                  //��ָ����ļ��ڵ�
    int wait;                           //�ȴ���ɾ���Ĵ���
}IFileNodePointer;

typedef struct IEvent   //�¼�
{
    int x1;
    int y1;
    int x2;
    int y2;
    int type;               //�������
    void (*pfun)(IFileNode*,IFileNode*);     //�ص����� (void*) (int*) ǿת 
    IFileNode *node0;      //�ص������ĵ�һ������
    IFileNode *node1;      //�ص������ĵڶ�������
    char change;            //�ı��λ��
}IEvent;

typedef struct IEventStackNode      //�¼�ջ
{
    IEvent event;
    struct IEventStackNode *next;
}IEventStackNode;

#endif