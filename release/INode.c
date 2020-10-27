/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵�������ļ��ڵ������صĲ��ֺ������Ƚϵײ�
 **************************************************
 */

#include"INode.h"

/*
    �������ܣ�����ӽڵ�
    ���������parent�������ڵ�, child�����ӽڵ�
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IAddChild(IFileNode *parent,IFileNode *child)
{
    IFileNode *temp=NULL;

    if(!parent) return 0;
    //���ڵ�Ϊ�գ�����0
    
    if(!strcmp(child->file.name,""))
    {
        free(child);
        child=NULL;
        return 0;
    }
    //�ӽڵ�Ϊ��ʬ�ڵ㣬���������0
    
    if(parent->child)
    {
        temp=parent->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=child;
        child->pre=temp;
        child->flags&=NODE_DEL_HEAD;
    }
    //������ڵ������ӽڵ�
    else
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=NODE_ADD_HEAD;
    }
    //������ڵ�δ���ӽڵ�
    return 1;   
    //�ɹ���ӣ�����1
}

/*
    �������ܣ��õ�·���µ������ļ������������ʽ����
    ���������path��������·��
    �����������
    ����ֵ��·���µ��ļ�����
*/
IFileNode *IGetFileNodeList(char *path)
{
    IFileNode *childRoot=(IFileNode*)malloc(sizeof(IFileNode)),\
    *tempNode=childRoot,*lastNode=childRoot;
    int ret,checkAgain=0,i,j=0;
    struct find_t ft;
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","r+");
    char tempStr1[PATH_LEN],tempStr2[PATH_LEN];

    if(childRoot==NULL)
    {
        IQuit();
    }
    Icd(path);
    IFileNodeSetNull(childRoot);
    ret=_dos_findfirst("*.*", 0xf7,&ft);  
    //"*.*"�� 0xf7�����ļ��ڵ�   ft�洢���ҽ��
    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,"..")||!strcmp(ft.name,"WINDOWS")||\
        IStartWith(ft.name,"DOCUME")||IStartWith(ft.name,"$")||\
        IStartWith(ft.name,"PROGRA")||IStartWith(ft.name,"360")||\
        IStartWith(ft.name,"NTLDR")||IStartWith(ft.name,"SYSTE")||\
        IEndWith(ft.name,"SYS")||IEndWith(ft.name,"INI")||\
        IEndWith(ft.name,"COM")||IEndWith(ft.name,"BIN"))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }   //�������ýڵ�
        while(fgets(tempStr1,PATH_LEN,fp))
        {
            if(tempStr1[strlen(tempStr1)-1]=='\n')
                tempStr1[strlen(tempStr1)-1]='\0';
            strcpy(tempStr2,path);
            strcat(tempStr2,"\\");
            strcat(tempStr2,ft.name);
            if(!strcmp(tempStr1,tempStr2))
            {
                ret=_dos_findnext(&ft);
                if(ret) break;
                else checkAgain=1;
            }
        }
        rewind(fp);
        if(checkAgain)
        {
            checkAgain=0;
            continue;
        }
        if(ret)
        {
            if(tempNode==lastNode)
                childRoot=NULL;
            else
                lastNode->next=NULL;
            free(tempNode);
            break;
        }
        j++;

        strcpy(tempNode->file.name,ft.name);
        tempNode->file.size=(ft.size/512+1)/2;
        if(ft.attrib&FA_DIREC)
        {
            strcpy(tempNode->file.type,"0");
        }
        else
        {
            for(i=strlen(tempNode->file.name)-1;i>=0;i--)
            {
                if(tempNode->file.name[i]=='.')
                {
                    tempNode->file.type[0]=tempNode->file.name[i+1];
                    tempNode->file.type[1]=tempNode->file.name[i+2];
                    tempNode->file.type[2]=tempNode->file.name[i+3];
                    tempNode->file.type[3]='\0';
                    break;
                }
                if(i==0)
                    strcpy(tempNode->file.type,"NOT");
            }
        }
        tempNode->file.date=ft.wr_date;
        tempNode->file.time=ft.wr_time;
        //��ʼ���½ڵ�

        ret=_dos_findnext(&ft);
        //������һ���ڵ�

        if(ret) break;
        if(j>MAXNODES) break;
        //�����·���½ڵ�������120, ���ټ�������

        lastNode=tempNode;
        tempNode=(IFileNode*)malloc(sizeof(IFileNode));

        if(tempNode==NULL)
        {
            IQuit();
        }
        lastNode->next=tempNode;
        IFileNodeSetNull(tempNode);
        tempNode->pre=lastNode;
    }
    fclose(fp);
    return childRoot;
}

/*
    �������ܣ���parent�ļ��������name�ļ��ڵ�
    ���������parent�������ڵ�, name�����ӽڵ��ļ���
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IAddFileNode(IFileNode *parent,char *name)
{
    IFileNode *child=(IFileNode*)malloc(sizeof(IFileNode));
    int ret,i;
    struct find_t ft;
    char temp[PATH_LEN];

    if(child==NULL)
        IQuit();
    
    IGetAbsolutePath(parent,temp);
    Icd(temp);
    IFileNodeSetNull(child);
    ret=_dos_findfirst(name, 0xf7,&ft);  
    //����name�ļ�

    if(ret) return 0;   
    //���Ҳ���������0
        
    strcpy(child->file.name,ft.name);
    child->file.date=ft.wr_date;
    child->file.time=ft.wr_time;
    child->file.size=(ft.size/512+1)/2;
    
    if(ft.attrib&FA_DIREC)
        strcpy(child->file.type,"0");
    
    else
    {
        for(i=0;i<strlen(child->file.name);i++)
        {
            if(child->file.name[i]=='.')
            {
                strcpy(child->file.type,child->file.name+i+1);
                break;
            }
            if(i==strlen(child->file.name)-1)
                strcpy(child->file.type,"NOT");
        }
    }
    //��ʼ���ýڵ�

    return IAddChild(parent,child);
}

/*
    �������ܣ���parent�ļ�����ɾ��name�ļ��ڵ�
    ���������parent�������ڵ�, name�����ӽڵ��ļ���
    �����������
    ����ֵ���ɹ��򷵻�1, ʧ���򷵻�0
*/
int IDelFileNode(IFileNode *parent,char *name)
{
    IFileNode *child=parent->child;
    int ret,i;
    char temp[PATH_LEN];

    IGetAbsolutePath(parent,temp);
    Icd(temp);

    while(strcmp(child->file.name,name)&&child!=NULL)
       child=child->next;
    
    if(child==NULL)
        return 0;

    if(child->flags&NODE_IS_HEAD)
    {
        child->pre->child=child->next;
        if(child->next)
        {
            child->next->pre=child->pre;
            child->next->flags|=NODE_ADD_HEAD;
        }
    }
    //���������ͷ
    else
    {
        child->pre->next=child->next;
        if(child->next) child->next->pre=child->pre;
    }
    //�����������ͷ

    free(child);
    return 1;
}

/*
    �������ܣ��ݹ�ɾ����������
    ���������rootҪɾ�����ļ�����ڵ�
    �����������
    ����ֵ����
*/
void IDelFilelist(IFileNode *root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    //�������
    if(root->next)
    {
        IDelFilelist(root->next);
    }
    free(root);
    root=NULL;
}

/*
    �������ܣ��ݹ����������
    ���������rootҪ��֦���ļ�����ڵ�
    �����������
    ����ֵ����
*/
void IAddFilelist(IFileNode *root)
{
    IFileNode *childRoot;
    char temp[PATH_LEN];

    if(!root->child&&IisFolder(root))
    {
        IGetAbsolutePath(root,temp);
        childRoot=IGetFileNodeList(temp);
        IAddChild(root,childRoot);
    }
    
    if(root->child)
        IAddFilelist(root->child);
    //�������

    if(root->next)
        IAddFilelist(root->next);
}

/*
    �������ܣ��鿴�ļ������Ƿ������ļ���
    ���������node����Ŀ��ڵ�, path��������·��
    �����������
    ����ֵ���������ļ��У�����1; ���򷵻�0
*/
int IPeek(IFileNode *node,char *path)
{
    int ret;
    struct find_t ft;
    char temp[PATH_LEN];

    if(!IisFolder(node)) return 0;

    Icd(path);
    ret=_dos_findfirst("*.*", 0xf7,&ft);

    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        if(ft.attrib&FA_DIREC)
            return 1;

        ret=_dos_findnext(&ft);
        if(ret) break;
    }
    return 0;
}

/*
    �������ܣ��������̲�����Ŀ¼
    ���������path��������·
    �����������
    ����ֵ����
*/
void Icd(char *path)
{
    char temp[PATH_LEN]="";

    if(path[1]==':'&&getdisk()!=(path[0]-'A'))  //��ǰ������Ŀ�겻һ��
    {
        setdisk(path[0]-'A');   //���Ĵ���
    } 
    if(strlen(path)<=3)     //·����׼��
    {
        strcpy(temp,path);
        strcpy(temp+1,"");
        strcat(temp,":\\.");
        chdir(temp);
    }   
    chdir(path);    //����Ŀ¼
}