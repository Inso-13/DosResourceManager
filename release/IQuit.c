/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ�������쳣�˳�����
 **************************************************
 */

#include"IQuit.h"

/*
    �������ܣ��˳�����
    �����������
    �����������
    ����ֵ����
*/
void IQuit()
{
    closegraph();   //�ر�ͼ�ν���
    fcloseall();    //�ر������ļ�
    exit(0);    //�˳�
}

/*
    �������ܣ�����curNode����
    ���������pointer����curNode�ڵ�
    �����������
    ����ֵ����
*/
void IDelPointer(IFileNodePointer *pointer)
{
    IFileNodePointer *tempNode=pointer;
    while(tempNode->next)
    {
        tempNode=tempNode->next;
    }   //�ҵ�����β

    while(tempNode->pre)
    {
        tempNode=tempNode->pre;
        free(tempNode->next);
        tempNode->next=NULL;
    }   //������β������ͷ�������ͷŽڵ�
    free(tempNode);    //�ͷ����һ���ڵ�
}
