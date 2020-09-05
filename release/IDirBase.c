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
IBool Icopy(IFileNode * inFile,IFileNode * outParent)
{
    FILE * fin,*fout;
    char * buff,inPath[50],outPath[50],temp[50],i[2],name[18],ext[5];
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

    IAddFileNode(outParent,name);  
    //������ļ��ڵ�
    return 1;
}

/*
    �������ܣ�����ɾ���ļ�
    ���������fileNode�����ȴ�ɾ�����ļ�
    �����������
    ����ֵ��ɾ���ɹ�����1��ʧ���򷵻�0
*/
IBool Irmf(IFileNode * fileNode)
{
    char tempStr[50];   //�����ַ���

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
IBool Imkdir(IFileNode * pathNode,char* folderName)    
{
    char temp[80];     //�����ַ���
    
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
IBool Irmdir(IFileNode * node,int flag)
{
    char temp[50];      //�����ַ���
    
    if(node->child) 
        return Irmdir(node->child,0);
    //�ݹ�ɾ�����ļ���

    if(!flag)
    {
        if(node->next)
            return Irmdir(node->next,0);
    }
    //flag==0, ɾ���ֵ��ļ���

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
    char temp[50];      //�����ַ���

    if(IisFolder(oldChildChild))
    {
        if(!oldChildChild->child)
            IAddFilelist(oldChildChild);
        Imkdir(newChild,oldChildChild->file.name);
        if(oldChildChild->child)
            ICopyAll(oldChildChild->child,newChild->child);
    }
    //������ļ��У��ݹ鸴��
    else
    {
        Icopy(oldChildChild,newChild);
    }
    //������ļ�����򵥸���

    if(oldChildChild->next)
    {
        ICopyAll(oldChildChild->next,newChild);
    }
    //�ݹ鸴���ֵܽڵ�

    IGetAbsolutePath(newChild,temp);
    IPeek(newChild,temp);
    //�����ļ��ڵ������
}

/*
    �������ܣ��ݹ鸴�������ļ����ļ���
    ���������oldChild����Ҫ���Ƶ��ļ����ļ���, newCParent����Ҫճ�������ļ���
    �����������
    ����ֵ����
*/
void Icpr(IFileNode * oldChild,IFileNode * newParent)
{
    char temp[50];      //�����ַ���

    IGetAbsolutePath(newParent,temp);
    strcat(temp,"\\");

    if(IisFolder(oldChild))
    {
        Imkdir(newParent,oldChild->file.name);
        IEntree(oldChild);
        strcat(temp,oldChild->file.name);
        ICopyAll(oldChild->child,IFindNodeByPath(temp,newParent));
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
    IFileNode *tempNode=oldChildChild,*nextNode=oldChildChild->next;

    if(IisFolder(oldChildChild))
    {
        IEntree(oldChildChild);
        if(oldChildChild->child)
            IDelAll(oldChildChild->child);
    }
    else
    {
        Irmf(oldChildChild);
    }

    if(nextNode)
    {
        tempNode=nextNode;
        nextNode=nextNode->next;
        IDelAll(tempNode);
    }
    //�ݹ�ɾ���ֵܽڵ�
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

    while(Irmdir(oldChild,1));
    //ɾ��ʣ�µ����п��ļ���
}
