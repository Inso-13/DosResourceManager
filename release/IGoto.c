/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-10-4
 *   ˵��������·������ָ��λ�õĺ���
 **************************************************
 */

#include"IGoto.h"

/*
    �������ܣ�ֱ�ӽ���Ŀ¼
    ���������path����·��
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGotoFrom(IFileNode *j,IFileNode *cur)
{
    int num=(int)j;                                             //ѡ��Ľڵ��λ��
    FILE *searched=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","r");    //���ҵ����ļ�
    IFileNodePointer **curNode=(IFileNodePointer**)cur;         //��ǰ�ڵ�����
    IFileNode* tempNode=(*curNode)->child;                      //ѭ�������ڵ�
    char tempStr[PATH_LEN],tempName[PATH_LEN];                  //�����ַ���
    int i;                                                      //ѭ���������ͱ���

    while(num--)
        fgets(tempStr,PATH_LEN,searched);                       //�õ��ļ��ľ���·��
    fclose(searched);

    IGetAbsolutePath(tempNode,tempName);
    strcpy(tempStr,tempStr+strlen(tempName));
    while(1)
    {
        for(i=1;i<strlen(tempStr);i++)
        {
            if(tempStr[i]=='\\')
                break;
        }
        if(i<strlen(tempStr))
        {
            strcpy(tempName,tempStr+1);
            tempName[i-1]='\0';
            IEntreeActive(tempNode,cur);
            tempNode=IFindNodeByName(tempName,tempNode->child);
            strcpy(tempStr,tempStr+i);
        }   //�ָ��ļ��ľ���·����������Ŀ¼
        else
        {
            IEntreeActive(tempNode,cur);
            strcpy(tempStr,tempStr+1);
            if(tempStr[strlen(tempStr)-1]=='\n')
                tempStr[strlen(tempStr)-1]='\0';
            tempNode=tempNode->child;
            while(tempNode->next)
            {
                tempNode->flags&=NODE_DEL_SELECT;
                tempNode=tempNode->next;
            }   //ȡ��Ŀ��Ŀ¼��������ѡ��
            tempNode->flags&=NODE_DEL_SELECT;
            tempNode=IFindParent(tempNode);
            tempNode=IFindNodeByName(tempStr,tempNode->child);
            tempNode->flags|=NODE_ADD_SELECT;
            break;
        }   //ѡ��Ŀ���ļ�
    }
}

/*
    �������ܣ�ֱ�ӽ���Ŀ¼
    ���������path����·��
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
char IGoto(char *path,IFileNodePointer **curNode)
{
    IFileNode *initNode=(*curNode)->child;       //curNode�ĳ�ʼֵ��ʧ��ʱ���¸���curNode
    IFileNode *tempNode=initNode;                //ѭ�������ڵ�
    char tempStr1[PATH_LEN],tempStr2[PATH_LEN];  //�����ַ���
    char flag=0;                                 //��־λ�����������ļ����ļ���
    int i,n;                                     //ѭ����������

    if(path[strlen(path)-1]=='\\')
        flag=1;
    while(tempNode->pre)
    {
        tempNode=tempNode->pre;
    }   //tempNode==DRM
    
    strcpy(tempStr1,path);
    while(1)
    {
        n=strlen(tempStr1);
        if(!n)
            break;
        for(i=0;i<n;i++)
        {
            if(tempStr1[i]>='a'&&tempStr1[i]<='z')
                tempStr1[i]+='A'-'a';
            else if(tempStr1[i]=='\\')
                break;
        }   //��·��ת��Ϊ��д
        strcpy(tempStr2,tempStr1);
        tempStr2[i]='\0';

        if(i==n)
            strcpy(tempStr1,tempStr1+n);
        else
            strcpy(tempStr1,tempStr1+i+1);
        
        IEntreeActive(tempNode,(IFileNode*)curNode);
        tempNode=IFindNodeByName(tempStr2,tempNode->child);
        if(flag)
            IEntreeActive(tempNode,(IFileNode*)curNode);
            
        if(!tempNode)
        {
            IEntreeActive(initNode,(IFileNode*)curNode);
            return 0;
        }   //���ʧ�ܣ��ص�ԭ����·��
    }
    return 1;
}