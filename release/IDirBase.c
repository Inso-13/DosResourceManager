/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵����DiryBase��ΪDiry��ĵײ�֧�ţ���װ����ೣ�õ��ļ���������
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<DOS.H>
#include<DIR.H>
#include<IO.H>
#include<ALLOC.H>
#include"IUtility.h"
#include"INode.h"
#include"IDirBase.h"

#define BUFFSIZE 256
//�����ļ�ʱ�Ļ�������С

/*
    �������ܣ����Ƶ����ļ�����inFile�ļ����Ƶ�outParent�ļ����ڣ������½ڵ�
    ���������inFile�����ȴ����Ƶ��ļ�, outParent����ճ������Ŀ���ļ���
    �����������
    ����ֵ�����Ƴɹ�����1��ʧ���򷵻�0
*/
int Icopy(IFileNode * inFile,IFileNode * outParent)
{
    FILE * fin,*fout;
    char * buff,inPath[150],outPath[150],temp[150],i[2],name[18],ext[5];
    int ret,j;

    IGetAbsolutePath(inFile,inPath);
    fin=fopen(inPath,"r");
    if(fin==NULL)
    {
#ifdef DB
        printf("failed to open %s\n",inFile->file.name);
#endif
        return 0;
    }
    //��Դ�ļ�

    IGetAbsolutePath(outParent,outPath);
    strcat(outPath,"\\");
    strcat(outPath,inFile->file.name);
    strcpy(name,inFile->file.name);
    if(searchpath(outPath)||!strcmp(inPath,outPath)) //ԭλ�ÿ������ļ��Զ�������
    {
        strcpy(i,"1");
        for(j=0;j<strlen(inFile->file.name);j++)
            if(inFile->file.name[j]=='.')
                break;
        strcpy(ext,inFile->file.name+j);
        if(strlen(name)>11||(j==strlen(name)&&j>7))
        {
            strcpy(name+4,"~");
            strcpy(name+5,ext);
            j=5;
        }
        IGetAbsolutePath(outParent,outPath);
        strcat(outPath,"\\");
        do
        {
            strcpy(name+j,"");
            strcat(name,i);
            strcat(name,ext);
            strcpy(temp,outPath);
            strcat(temp,name);
            i[0]++;
        }while(searchpath(temp));
        strcpy(outPath,temp);
    }

    fout=fopen(outPath,"w");
    if(fout==NULL)
    {
#ifdef DB
        printf("failed to open %s\n",inFile->file.name);
#endif
        return 0;
    }
    //��Ŀ���ļ�

    buff=malloc(BUFFSIZE);
    if(buff==NULL)
    {
#ifdef DB
        puts("not enough memory");
#endif
        return 0;
    }

    while(1)
    {
        ret=fread(buff,1,BUFFSIZE,fin);
        fwrite(buff,ret>BUFFSIZE?BUFFSIZE:ret,1,fout);
        if(feof(fin))
            break;
    }
    //����ѭ����ֱ���ļ��������

    fclose(fin);
    fclose(fout);
    free(buff);
    //�ر��ļ����ͷŻ�����

    // IAddFileNode(outParent,name);  
    //������ļ��ڵ�
    return 1;
}

/*
    �������ܣ�����ɾ���ļ�
    ���������fileNode�����ȴ�ɾ�����ļ�
    �����������
    ����ֵ��ɾ���ɹ�����1��ʧ���򷵻�0
*/
int Irmf(IFileNode * fileNode)
{
    char tempStr[150];   //�����ַ���

    IGetAbsolutePath(fileNode,tempStr);
    remove(tempStr);    
    //ɾ���ļ�
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name);     
    //ɾ���ļ��ڵ�
}

/*
    �������ܣ������ļ��У������½ڵ�
    ���������pathNode�������ڵ�, folderName�������ļ�����
    �����������
    ����ֵ�������ļ��гɹ�����1��ʧ���򷵻�0
*/
int Imkdir(IFileNode * pathNode,char* folderName)    
{
    char temp[150];     //�����ַ���
    
    IGetAbsolutePath(pathNode,temp);
    strcat(temp,"\\");
    strcat(temp,folderName);
    //�õ����ļ��еľ���·��

    if(mkdir(temp)==-1)
        return 0;
    else
        return IAddFileNode(pathNode,folderName);
    //�����ļ��ڵ�
}

/*
    �������ܣ�ɾ�����п��ļ��У������½ڵ�
    ���������node�������ڵ�, flag���������Ƿ�ɾ���ֵ��ļ���
    �����������
    ����ֵ��ɾ���ļ��гɹ�����1��ʧ���򷵻�0
*/
int Irmdir(IFileNode * node)
{
    char temp[150];      //�����ַ���

    IGetAbsolutePath(node,temp);
    IDelFileNode(IFindParent(node),node->file.name);
    //���½ڵ�

    return !rmdir(temp);
}

/*
    �������ܣ����������ļ�����
    ���������oldChildChild����Ҫ���Ƶ��ļ����еĵ�һ���ڵ�, newChild����Ҫճ�������ļ����ڲ�
    �����������
    ����ֵ����
*/
void ICopyAll(IFileNode * oldChildChild,IFileNode * newChild)
{
    while(oldChildChild)
    {
        if(IisFolder(oldChildChild))
        {
            if(!oldChildChild->child)
                IEntree(oldChildChild);
            Imkdir(newChild,oldChildChild->file.name);
            if(oldChildChild->child)
            {
                ICopyAll(oldChildChild->child,IFindNodeByName(oldChildChild->file.name,newChild));
                IDetree(oldChildChild);
            }
        }
        //������ļ��У��ݹ鸴��
        else
        {
            Icopy(oldChildChild,newChild);  
        }
        //������ļ�����򵥸���
        oldChildChild=oldChildChild->next;  
    }
    //�ݹ鸴���ֵܽڵ�
}

/*
    �������ܣ��ݹ鸴�������ļ����ļ���
    ���������oldChild����Ҫ���Ƶ��ļ����ļ���, newCParent����Ҫճ�������ļ���
    �����������
    ����ֵ����
*/
void Icpr(IFileNode * oldChild,IFileNode * newParent)
{
    char temp[150];      //�����ַ���

    IGetAbsolutePath(newParent,temp);
    strcat(temp,"\\");

    if(IisFolder(oldChild))
    {
        Imkdir(newParent,oldChild->file.name);
        IEntree(oldChild);
        strcat(temp,oldChild->file.name);
        ICopyAll(oldChild->child,IFindNodeByPath(temp,newParent));
        IDetree(oldChild);
    }
    //������ļ���
    else
        Icopy(oldChild,newParent);
    //������ļ�
}  

/*
    �������ܣ�ɾ������
    ���������oldChildChild����Ҫɾ�����ļ����еĵ�һ���ڵ�
    �����������
    ����ֵ����
*/
void IDelAll(IFileNode * oldChildChild)
{
    IFileNode *nextNode=NULL;

    while(oldChildChild)
    {
        nextNode=oldChildChild->next;
        if(IisFolder(oldChildChild))
        {
            if(!oldChildChild->child)
                IEntree(oldChildChild);
            IDelAll(oldChildChild->child);
            Irmdir(oldChildChild);
        }
        else
        {
            Irmf(oldChildChild);
        }
        oldChildChild=nextNode;
    }
}

/*
    �������ܣ��ݹ�ɾ�������ļ����ļ���
    ���������oldChild����Ҫɾ�����ļ���
    �����������
    ����ֵ����
*/
void Irmr(IFileNode * oldChild)
{
    if(IisFolder(oldChild))
    {
        IEntree(oldChild);
        if(oldChild->child)
            IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    //ɾ���ļ��������е��ļ�
}
