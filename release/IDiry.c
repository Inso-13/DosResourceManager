/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵����Diry��DirBaseΪ�������ṩ�˻������Ա�ǰ��ֱ��ʹ�õ��ļ���������
*/


#include<STRING.H>
#include<STDLIB.H>
#include<CONIO.H>
#include<ALLOC.H>
#include<DOS.H>
#include<IO.H>
#include<STDIO.H>
#include"IUtility.h"
#include"INode.h"
#include"IDirBase.h"
#include"IDiry.h"

/*
    �������ܣ��������ļ�
    ���������pathNode����·���ڵ�, fileName�������ļ���
    �����������
    ����ֵ�����Ƴɹ�����1��ʧ���򷵻�0
*/
IBool Inew(IFileNode * pathNode,char* fileName)
{
    char temp[50];  //�����ַ���

    IGetAbsolutePath(pathNode,temp);
    Icd(temp);
    if(creatnew(fileName,0)==-1)
        return 0;
    //����ʧ�ܣ�����0

    return IAddFileNode(pathNode,fileName);
    //�����ɹ�����ӵ��ļ����У�����1 
}

/*
    �������ܣ��������ļ�/�ļ���
    ���������oldName�������ļ��ڵ�, newName�������ļ���
    �����������
    ����ֵ����
*/
void Irename(IFileNode * oldName,char* newName)
{
    char temp[50];
    int i;

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  
    //�������ļ�/�ļ���

    strcpy(oldName->file.name,newName);
    for(i=0;i<strlen(oldName->file.name);i++)
    {
        if(oldName->file.name[i]=='.')
        {
            strcpy(oldName->file.type,oldName->file.name+i+1);
            break;
        }
        if(i==strlen(oldName->file.name)-1)
            strcpy(oldName->file.type,"NOT");
    }
    //�����ļ�������
}

/*
    �������ܣ���rootĿ¼�µ��ļ����ļ����ϼ���
    ���������root������Ҫ������Ŀ¼
    �����������
    ����ֵ����
*/
void IDetree(IFileNode * root)
{
    if(!root) return;
    //��root==NULL��ֱ�ӷ���
    
    if(!IisFolder(root)) return;
    //��root�����ļ��У�ֱ�ӷ���
    
    if(!root->child) return;
    //��rootδ���򿪣�ֱ�ӷ���

    root->file.type[0]='0';
    //�ر��ļ���

    if(root->file.type[1]=='\\') return;
    //��Ŀ¼Ϊ��Ŀ¼����0����
    
    IDelFilelist(root->child);
    root->child=NULL;
    //��rootĿ¼�µ��ļ����ļ����ϼ���
}

/*
    �������ܣ���rootĿ¼�µ��ļ��ӵ��ļ�����
    ���������root������Ҫ��֦��Ŀ¼
    �����������
    ����ֵ����
*/
void IEntree(IFileNode * root)
{
    IFileNode * childRoot;
    char temp[50];

    if(!root) return;
    //��root==NULL��ֱ�ӷ���

    if(!IisFolder(root)) return;
    //��root�����ļ��У�ֱ�ӷ���

    if(!strcmp(root->file.type,"0ds")) return;
    //��root�Ǳ������Ĵ��̣�ֱ�ӷ���

    if(root->file.type[0]=='1'||root->child) return;
    //��root�ѱ��򿪣�ֱ�ӷ���
    
    root->file.type[0]='1';
    //���ļ���
    
    if(root->file.type[1]=='\\') return;
    //��Ŀ¼Ϊ��Ŀ¼����1����

    IGetAbsolutePath(root,temp);
    childRoot=IGetFileNodeList(temp);
    if(childRoot)
        IAddChild(root,childRoot);
    //��rootĿ¼�µ��ļ��ӵ��ļ�����

    while(childRoot&&IisFolder(childRoot))
    {
        IGetAbsolutePath(childRoot,temp);
        IPeek(childRoot,temp);
        childRoot=childRoot->next;
    }
    //�����ӽڵ�
}

/*
    �������ܣ�����oldParentĿ¼�����б�ѡ�е��ļ�
    ���������oldParent������Ҫ���Ƶ�Ŀ¼, newParent����Ŀ��Ŀ¼
    �����������
    ����ֵ����
*/
void Icplr(IFileNode * oldParent,IFileNode * newParent)
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Icpr(tempNode,newParent);
        //������ļ��ڵ㱻ѡ�У�����֮

        tempNode=tempNode->next;
    }
}

/*
    �������ܣ�ɾ��oldParentĿ¼�����б�ѡ�е��ļ�
    ���������oldParent������Ҫɾ����Ŀ¼
    �����������
    ����ֵ����
*/
void Irmlr(IFileNode * oldParent)
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Irmr(tempNode);
        //������ļ��ڵ㱻ѡ�У���ɾ��֮

        tempNode=tempNode->next;
    }
}

/*
    �������ܣ����ļ����ڵ�ǰ�ļ��в����ļ�
    ���������path������Ҫ���ҵ�Ŀ¼, patternͨ���
    ���������fp�����ݴ��ļ�
    ����ֵ����
*/
void ISearch(char* path,char* pattern,FILE* fp)
{
    int ret,i;
    struct find_t ft;
    char temp[60];  //�����ַ���

    Icd(path);
    ret=_dos_findfirst("*.*",0xf7,&ft);
    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,".."))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        //�ų�.��..���������ļ�·��

        if(IMatch(ft.name,pattern))
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            strcat(temp,"\n");
            fputs(temp,fp);
        }
        //���ƥ�䣬��¼��fp�ļ�

        if(ft.attrib&0x10)
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            ISearch(temp,pattern,fp);
        }
        //������ļ��У��ݹ����

        Icd(path);
        ret=_dos_findnext(&ft);
        //������һ��
    }
}
