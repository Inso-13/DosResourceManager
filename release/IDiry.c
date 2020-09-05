/*
    版本号：1.0
    作者：黄子昊
    生成日期：2020-9-4
    说明：Diry以DirBase为基础，提供了基本可以被前端直接使用的文件操作函数
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
    函数功能：建立新文件
    输入参数：pathNode——路径节点, fileName——新文件名
    输出参数：无
    返回值：复制成功返回1，失败则返回0
*/
IBool Inew(IFileNode * pathNode,char* fileName)
{
    char temp[50];  //辅助字符串

    IGetAbsolutePath(pathNode,temp);
    Icd(temp);
    if(creatnew(fileName,0)==-1)
        return 0;
    //创建失败，返回0

    return IAddFileNode(pathNode,fileName);
    //创建成功，添加到文件树中，返回1 
}

/*
    函数功能：重命名文件/文件夹
    输入参数：oldName——旧文件节点, newName——新文件名
    输出参数：无
    返回值：无
*/
void Irename(IFileNode * oldName,char* newName)
{
    char temp[50];
    int i;

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  
    //重命名文件/文件夹

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
    //调整文件的类型
}

/*
    函数功能：将root目录下的文件从文件树上减除
    输入参数：root——需要减除的目录
    输出参数：无
    返回值：无
*/
void IDetree(IFileNode * root)
{
    if(!root) return;
    //若root==NULL，直接返回
    
    if(!IisFolder(root)) return;
    //若root不是文件夹，直接返回
    
    if(!root->child) return;
    //若root未被打开，直接返回

    root->file.type[0]='0';
    //关闭文件夹

    if(root->file.type[1]=='\\') return;
    //若目录为根目录，置0返回
    
    IDelFilelist(root->child);
    root->child=NULL;
    //将root目录下的文件从文件树上减除
}

/*
    函数功能：将root目录下的文件加到文件树上
    输入参数：root——需要增枝的目录
    输出参数：无
    返回值：无
*/
void IEntree(IFileNode * root)
{
    IFileNode * childRoot;
    char temp[50];

    if(!root) return;
    //若root==NULL，直接返回

    if(!IisFolder(root)) return;
    //若root不是文件夹，直接返回

    if(!strcmp(root->file.type,"0ds")) return;
    //若root是被保护的磁盘，直接返回

    if(root->file.type[0]=='1'||root->child) return;
    //若root已被打开，直接返回
    
    root->file.type[0]='1';
    //打开文件夹
    
    if(root->file.type[1]=='\\') return;
    //若目录为根目录，置1返回

    IGetAbsolutePath(root,temp);
    childRoot=IGetFileNodeList(temp);
    if(childRoot)
        IAddChild(root,childRoot);
    //将root目录下的文件加到文件树上

    while(childRoot&&IisFolder(childRoot))
    {
        IGetAbsolutePath(childRoot,temp);
        IPeek(childRoot,temp);
        childRoot=childRoot->next;
    }
    //更新子节点
}

/*
    函数功能：复制oldParent目录下所有被选中的文件
    输入参数：oldParent——需要复制的目录, newParent——目的目录
    输出参数：无
    返回值：无
*/
void Icplr(IFileNode * oldParent,IFileNode * newParent)
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Icpr(tempNode,newParent);
        //如果子文件节点被选中，则复制之

        tempNode=tempNode->next;
    }
}

/*
    函数功能：删除oldParent目录下所有被选中的文件
    输入参数：oldParent——需要删除的目录
    输出参数：无
    返回值：无
*/
void Irmlr(IFileNode * oldParent)
{
    IFileNode * tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&2)
            Irmr(tempNode);
        //如果子文件节点被选中，则删除之

        tempNode=tempNode->next;
    }
}

/*
    函数功能：按文件名在当前文件夹查找文件
    输入参数：path——需要查找的目录, pattern通配符
    输出参数：fp——暂存文件
    返回值：无
*/
void ISearch(char* path,char* pattern,FILE* fp)
{
    int ret,i;
    struct find_t ft;
    char temp[60];  //辅助字符串

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
        //排除.与..两个无用文件路径

        if(IMatch(ft.name,pattern))
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            strcat(temp,"\n");
            fputs(temp,fp);
        }
        //如果匹配，记录进fp文件

        if(ft.attrib&0x10)
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            ISearch(temp,pattern,fp);
        }
        //如果是文件夹，递归查找

        Icd(path);
        ret=_dos_findnext(&ft);
        //查找下一项
    }
}
