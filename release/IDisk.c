/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-10-7
 *   ˵�������̳�ʼ������
 **************************************************
 */

#include"IDisk.h"

/*
    �������ܣ���ʼ���ļ����ڵ�
    ���������id�����û����
    �����������
    ����ֵ�����ļ��ڵ�
*/
IFileNode * IDiskInit(int id)
{
    IFileNode * root=(IFileNode *)malloc(sizeof(IFileNode)),* rootC=(IFileNode *)malloc(sizeof(IFileNode)),*tempNode=rootC,*lastNode=rootC;
    int i,disk;
    char temp[3];

    IFileNodeSetNull(root);
    IFileNodeSetNull(rootC);
    root->child=rootC;
    strcpy(root->file.type,"1\\");
    strcpy(root->file.name,"DOS");
    root->flags=12;
    rootC->pre=root;
    rootC->flags|=4;
    strcpy(temp,"C:");
    
    for(i=0;i<26;i++)   //����26��Ӣ����ĸ���������д���
    {
        setdisk(i);
        disk=getdisk();
        if(disk==i)     //������̴��ڣ���ʼ�����̽ڵ�
        {
            if(disk<2||disk>24)
                continue;
            tempNode->file.date=33;
            tempNode->file.time=0;
            tempNode->file.size=-1;
            tempNode->flags|=8;
            if(disk==2&&id==0)
                strcpy(tempNode->file.type,"0ds");
            else
                strcpy(tempNode->file.type,"0d");
            temp[0]=disk+'A';
            strcpy(tempNode->file.name,temp);
            tempNode=(IFileNode *)malloc(sizeof(IFileNode));
            IFileNodeSetNull(tempNode);
            lastNode->next=tempNode;
            tempNode->pre=lastNode;
            lastNode=lastNode->next;
        }
    }
    lastNode->pre->next=NULL;
    free(lastNode);
    setdisk(2);
    return root;    //���ش��̽ڵ�ĸ��ڵ�
}