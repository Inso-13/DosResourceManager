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
IFileNode *IDiskInit(char id)
{
    IFileNode *root=(IFileNode*)malloc(sizeof(IFileNode)); //���ڵ�
    IFileNode *rootC=(IFileNode*)malloc(sizeof(IFileNode)); //C�̽ڵ�
    IFileNode *tempNode=rootC,*lastNode=rootC;  //�����ļ��ڵ� 
    int i,disk; //ѭ������
    char temp[3];  //�����ַ���

    IFileNodeSetNull(root); 
    IFileNodeSetNull(rootC);
    root->child=rootC;
    strcpy(root->file.type,"1\\");
    strcpy(root->file.name,ROOT_NAME);
    root->flags=NODE_IS_HEAD+NODE_HAS_FOLDER;
    rootC->pre=root;
    rootC->flags|=NODE_IS_HEAD;
    strcpy(temp,"C:");  //�ڵ��ʼ��
    
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
            if(disk==2&&id==0)  //������οͣ�����C��
                strcpy(tempNode->file.type,"0ds");
            else    //����ǹ���Ա������Ҫ����C��
                strcpy(tempNode->file.type,"0d");
            temp[0]=disk+'A';
            strcpy(tempNode->file.name,temp);
            tempNode=(IFileNode*)malloc(sizeof(IFileNode));    //�������ڴ�
            IFileNodeSetNull(tempNode); //�ڵ��ʼ��
            lastNode->next=tempNode;
            tempNode->pre=lastNode;
            lastNode=lastNode->next;
        }
    }
    lastNode->pre->next=NULL;
    free(lastNode); //�ͷ�lastNode�ڵ�
    setdisk(2);     //�ص�C��
    return root;    //���ش��̽ڵ�ĸ��ڵ�
}