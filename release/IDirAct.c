/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������Diry�����Ľӿ�ͳһ������ǰ�˵���ջʹ��
 **************************************************
 */

#include"IDirAct.h"

/*
    �������ܣ�����IEntree���������ĵ�ǰ�ڵ�
    ���������node������ҪIEntree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IEntreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
	IFileNodePointer *newCurNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));     //�½ڵ�
    IFileNodePointer *tempNode=NULL,*nextNode=NULL;    //ѭ�������ڵ�

    tempNode=(*curNode)->next;  //tempNodeָ��ѭ������һ��
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }//����curNode�����к�һ��ݹ�ɾ����������нڵ�

    newCurNode->child=node;
    newCurNode->next=NULL;
    newCurNode->wait=WAIT_COUNT;
    newCurNode->pre=*curNode;
    (*curNode)->next=newCurNode;
    *curNode=newCurNode;
    //�½ڵ��ʼ��

    IEntree(node,node->flags&NODE_TO_REENTREE);   //����IEntree����

    tempNode=(*curNode)->pre;
    while(tempNode)
    {
        tempNode->wait--;   //����ǰ��ڵ�ĵȴ�����
        if(tempNode->wait<WAIT_OFF)    //����ڵ�ĵȴ���������0
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        else
            tempNode=tempNode->pre;
    }   //end of while(tempNode)
    //ɾ��curNode�����еĳ�ʱ�ڵ㣬�Խ�Լ�ڴ�
}

/*
    �������ܣ�����IDetree���������ĵ�ǰ�ڵ�
    ���������node������ҪIDetree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IDetreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
    IFileNodePointer *tempNode=NULL,*nextNode=NULL,*lastNode=NULL;    //ѭ�������ڵ�
    char path1[PATH_LEN],path2[PATH_LEN];  //�����ַ���

    if(node->file.type[1]=='\\') return;    //����Ǹ��ڵ㣬ֱ�ӷ���

    tempNode=(*curNode)->next;  
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }   //����curNode�����к�һ��ݹ�ɾ����������нڵ�

    tempNode=(*curNode);
    IGetAbsolutePath(node,path2);   //�õ�Ҫɾ���ڵ��λ��
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);    //�õ�����Ľڵ��λ��
        if(IisChild(path1,path2))   //���������ͻ
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                    (*curNode)=tempNode;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        tempNode=lastNode;
    }   //���curNode��������node�ڵ㣬���ýڵ�������г�ȥ

    if(node->file.type[1]!='\\')
        (*curNode)->child=IFindParent(node);    //����curNode�ڵ�

    IDetree(node);  //����IDetree����

    node->file.type[0]='0'; //�ر��ļ���
}

/*
    �������ܣ��ڼ���IEntree�����󣬻��������ڴ�
    ���������X���������ļ��ڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IAfterEntree(IFileNode *cur,IFileNode *X)
{
#ifdef LM   //���ڴ�����ʱʹ��
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
    IFileNodePointer *nodeX=(IFileNodePointer*)X;    //�����ļ��ڵ�
    IFileNodePointer *tempNode=(*curNode)->pre,*lastNode=tempNode->pre;    //ѭ��ʹ��
    char path1[PATH_LEN],path2[PATH_LEN],path[PATH_LEN];   //�ݴ��ַ���

    IGetAbsolutePath((*curNode)->child,path1);  //��õ�ǰλ��
    if(nodeX&&nodeX->child)     //���nodeX��Ϊ��           
        IGetAbsolutePath(nodeX->child,path2);   //�õ�nodeXָ���·��
    else          
        strcpy(path2,"");   //���Ϊ�վͽ�·����Ϊ��

    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path);     //�õ�����������ڵ�
        if(strcmp(path,ROOT_NAME)&&strcmp(path,path1)&&strcmp(path,path2)\
        &&!IisChild(path1,path)&&!IisChild(path2,path))
        {           //���������ͻ
            IDetree(tempNode->child);   //�ͷŽڵ�
            if(tempNode->pre)
            {
                tempNode=tempNode->pre;
                tempNode->next=tempNode->next->next;
                free(tempNode->next->pre);
                tempNode->next->pre=tempNode;
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
            }   //��������ɾ���ڵ�
        }
        tempNode=lastNode;  //�������
    }   //end of while(tempNode)
#endif
}
