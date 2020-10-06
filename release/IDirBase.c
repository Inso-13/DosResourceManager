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
#include<GRAPHICS.H>
#include"IUtility.h"
#include"ISound.h"
#include"INode.h"
#include"IDirBase.h"

#define BUFFSIZE 256
//�����ļ�ʱ�Ļ�������С

/*
    �������ܣ����Ƶ����ļ�����inFile�ļ����Ƶ�outParent�ļ����ڣ������½ڵ�
    ���������inFile�����ȴ����Ƶ��ļ�, outParent����ճ������Ŀ���ļ��У�flag�����Ƿ�ǿ�Ƹ���
    �����������
    ����ֵ�����Ƴɹ�����1��ʧ���򷵻�0
*/
int Icopy(IFileNode * inFile,IFileNode * outParent,char flag)
{
    char inPath[150],outPath[150],temp[150],i[2],name[18],ext[5];
    int j;
    char tempStr[300];

    IGetAbsolutePath(inFile,inPath);
    IGetAbsolutePath(outParent,outPath);
    strcat(outPath,"\\");
    strcat(outPath,inFile->file.name);
    strcpy(name,inFile->file.name);
    if(!flag)
    {
        if(ISearchPath(outPath)||!strcmp(inPath,outPath)) //ԭλ�ÿ������ļ��Զ�������
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
            }while(ISearchPath(temp));
            strcpy(outPath,temp);
        }
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        strcat(tempStr+strlen(tempStr),outPath);

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);
    }
    else
    {
        Irmf(IFindNodeByPath(outPath,outParent));
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        IGetAbsolutePath(outParent,tempStr+strlen(tempStr));

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);
    }

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
int Irmf(IFileNode * fileNode)
{
    char tempStr[150];   //�����ַ���
    FILE* fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");

    IGetAbsolutePath(fileNode,tempStr);
    strcat(tempStr,"\n");
    fputs(tempStr,fp);

    strcpy(tempStr,"del ");
    IGetAbsolutePath(fileNode,tempStr+4);
    strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");

    system(tempStr);
    //ɾ���ļ�
    delay(1);

    fclose(fp);
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
    char temp[180];      //�����ַ���
    int i=0;    
    FILE* fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");

    IGetAbsolutePath(node,temp);
    strcat(temp,"\n");
    fputs(temp,fp);

    IGetAbsolutePath(node,temp);
    IDelFileNode(IFindParent(node),node->file.name);

    for(i=0;i<100;i++)
        if(ISearchPath(temp))
            rmdir(temp);
        else 
            break;
            
    fclose(fp);
    return 1;
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
                IEntree(oldChildChild,0);
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
            Icopy(oldChildChild,newChild,0);  
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
void Icpr(IFileNode * oldChild,IFileNode * newParent,char flag)
{
    char temp[150];      //�����ַ���
    IFileNode *tempNode=NULL;

    if(IisFolder(oldChild))
    {
        IGetAbsolutePath(newParent,temp);
        strcat(temp,"\\");
        strcat(temp,oldChild->file.name);

        if(ISearchPath(temp))
        {
            if(flag)
                Irmr(IFindNodeByPath(temp,newParent));
            else
                return; 
        }
        Imkdir(newParent,oldChild->file.name);
        IEntree(oldChild,0);
        tempNode=IFindNodeByPath(temp,newParent);
        tempNode->flags|=16;
        ICopyAll(oldChild->child,tempNode);
        IDetree(oldChild);
    }
    //������ļ���
    else
        Icopy(oldChild,newParent,flag);
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
                IEntree(oldChildChild,0);
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
        IEntree(oldChild,0);
        if(oldChild->child)
            IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    //ɾ���ļ��������е��ļ�
}
