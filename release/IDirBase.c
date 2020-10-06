/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：DiryBase作为Diry库的底层支撑，封装了许多常用的文件操作函数
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
//复制文件时的缓存区大小

/*
    函数功能：复制单个文件，将inFile文件复制到outParent文件夹内，并更新节点
    输入参数：inFile——等待复制的文件, outParent——粘贴到的目标文件夹，flag——是否强制覆盖
    输出参数：无
    返回值：复制成功返回1，失败则返回0
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
        if(ISearchPath(outPath)||!strcmp(inPath,outPath)) //原位置拷贝，文件自动重命名
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
    //添加新文件节点
    return 1;
}

/*
    函数功能：彻底删除文件
    输入参数：fileNode——等待删除的文件
    输出参数：无
    返回值：删除成功返回1，失败则返回0
*/
int Irmf(IFileNode * fileNode)
{
    char tempStr[150];   //辅助字符串
    FILE* fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");

    IGetAbsolutePath(fileNode,tempStr);
    strcat(tempStr,"\n");
    fputs(tempStr,fp);

    strcpy(tempStr,"del ");
    IGetAbsolutePath(fileNode,tempStr+4);
    strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");

    system(tempStr);
    //删除文件
    delay(1);

    fclose(fp);
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name);     
    //删除文件节点
}

/*
    函数功能：创建文件夹，并更新节点
    输入参数：pathNode——父节点, folderName——新文件夹名
    输出参数：无
    返回值：创建文件夹成功返回1，失败则返回0
*/
int Imkdir(IFileNode * pathNode,char* folderName)    
{
    char temp[150];     //辅助字符串
    
    IGetAbsolutePath(pathNode,temp);
    strcat(temp,"\\");
    strcat(temp,folderName);
    //得到新文件夹的绝对路径

    if(mkdir(temp)==-1)
        return 0;
    else
        return IAddFileNode(pathNode,folderName);
    //更新文件节点
}

/*
    函数功能：删除所有空文件夹，并更新节点
    输入参数：node——父节点, flag——控制是否删除兄弟文件夹
    输出参数：无
    返回值：删除文件夹成功返回1，失败则返回0
*/
int Irmdir(IFileNode * node)
{
    char temp[180];      //辅助字符串
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
    函数功能：复制整个文件链表
    输入参数：oldChildChild——要复制的文件夹中的第一个节点, newChild——要粘贴到的文件夹内部
    输出参数：无
    返回值：无
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
        //如果是文件夹，递归复制
        else
        {
            Icopy(oldChildChild,newChild,0);  
        }
        //如果是文件，则简单复制
        oldChildChild=oldChildChild->next;  
    }
    //递归复制兄弟节点
}

/*
    函数功能：递归复制所有文件和文件夹
    输入参数：oldChild——要复制的文件或文件夹, newCParent——要粘贴到的文件夹
    输出参数：无
    返回值：无
*/
void Icpr(IFileNode * oldChild,IFileNode * newParent,char flag)
{
    char temp[150];      //辅助字符串
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
    //如果是文件夹
    else
        Icopy(oldChild,newParent,flag);
    //如果是文件
}  

/*
    函数功能：删除链表
    输入参数：oldChildChild——要删除的文件夹中的第一个节点
    输出参数：无
    返回值：无
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
    函数功能：递归删除所有文件和文件夹
    输入参数：oldChild——要删除的文件夹
    输出参数：无
    返回值：无
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
    //删除文件夹中所有的文件
}
