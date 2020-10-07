/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵������Ҫ������һЩ���õĺ���
 **************************************************
 */

#include"IUtility.h"

/*
    �������ܣ���ʼ���ļ��ڵ�
    ���������node�����ļ��ڵ�
    �����������
    ����ֵ����
*/
void IFileNodeSetNull(IFileNode * node)
{
    node->flags=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
/*
    �������ܣ�����·���ҵ��ڵ�
    ���������path����·��, root������ʼ���ڵ�
    �����������
    ����ֵ�����ҵ������ظýڵ㣻���򷵻�NULL
*/
IFileNode * IFindNodeByPath(char * path,IFileNode * root)
{
    IFileNode * tempNode;
    char temp[150];

    if(!root)
        return 0;

    IGetAbsolutePath(root,temp);
    if(!strcmp(temp,path))   //�Ƚ�·����һ���򷵻�
        return root;
    
    tempNode=IFindNodeByPath(path,root->child); //�����������
    if(tempNode)
        return tempNode;

    tempNode=IFindNodeByPath(path,root->next);
    if(tempNode)
        return tempNode;
    
    return 0;   //δ�ҵ����򷵻�NULL
}

/*
    �������ܣ������ļ����ҵ��ڵ�
    ���������name�����ļ���, root������ʼ���ڵ�
    �����������
    ����ֵ�����ҵ������ظýڵ㣻���򷵻�NULL
*/
IFileNode * IFindNodeByName(char * name,IFileNode * root)
{
    IFileNode * temp;

    if(!root)
        return 0;

    if(!strcmp(root->file.name,name))   //�Ƚ��ļ�����һ���򷵻�
        return root;
    
    temp=IFindNodeByName(name,root->next);     //�����������
    if(temp)
        return temp;

    temp=IFindNodeByName(name,root->child);
    if(temp)
        return temp;
    
    return 0;   //δ�ҵ����򷵻�NULL
}

/*
    �������ܣ��жϽڵ��Ƿ�ΪĿ¼
    ���������node�������жϵĽڵ�
    �����������
    ����ֵ����Ŀ¼�򷵻�1������Ŀ¼�򷵻�0
*/
int IisFolder(IFileNode * node)
{
    return (node->file.type[0]=='0')||(node->file.type[0]=='1');
}

/*
    �������ܣ����ݽڵ�õ�����·��
    ���������node�����ļ��ڵ�
    ���������temp�����ļ��ľ���·��
    ����ֵ����
*/
void IGetAbsolutePath(IFileNode * node,char* temp)
{
    if(node->file.name[1]==':'||!strcmp(node->file.name,"DOS"))
        strcpy(temp,node->file.name);
    else
    {
        IGetAbsolutePath(IFindParent(node),temp);
        strcat(temp,"\\");
        strcat(temp,node->file.name);
    }
}

/*
    �������ܣ������ļ��ڵ�ĸ��ڵ�
    ���������child�����ӽڵ�
    �����������
    ����ֵ�����ڵ�
*/
IFileNode * IFindParent(IFileNode * child)
{
    IFileNode * temp=child;
    
    if(temp->file.type[1]=='\\')
        return NULL;
    //���child��DOS���ڵ�, �򷵻�NULL

    while(!(temp->flags&4))    //�ҵ�����ͷ
    {
        temp=temp->pre;
    }
    return temp->pre;
}

/*
    �������ܣ������ļ�·���õ��ļ���
    ���������path�����ļ�·��
    ���������name�����ļ���
    ����ֵ����
*/
void IGetNameByPath(char* path,char* name)
{
    int i;
    int n=strlen(path);

    for(i=n-1;i>=0;i--)
    {
        if(path[i]=='\\')
            break;
    }
    strcpy(name,path+i+1);
}

/*
    �������ܣ��ж�path2�Ƿ�Ϊpath1����·��
    ���������path1������·��, path2������·��
    �����������
    ����ֵ����path2�Ƿ�Ϊpath1����·��, ����1; ���򷵻�0
*/
int IisChild(char* path1,char* path2)
{
    int n=strlen(path2),i;

    for(i=0;i<n;i++)
    {
        if(path1[i]!=path2[i])
            return 0;
    }
    if(n==strlen(path1))
        return 0;
    return 1;
}
