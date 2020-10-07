/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：主要定义了一些常用的函数
 **************************************************
 */

#include"IUtility.h"

/*
    函数功能：初始化文件节点
    输入参数：node——文件节点
    输出参数：无
    返回值：无
*/
void IFileNodeSetNull(IFileNode * node)
{
    node->flags=0;
    node->child=NULL;
    node->next=NULL;
    node->pre=NULL;
}
/*
    函数功能：根据路径找到节点
    输入参数：path——路径, root——起始根节点
    输出参数：无
    返回值：若找到，返回该节点；否则返回NULL
*/
IFileNode * IFindNodeByPath(char * path,IFileNode * root)
{
    IFileNode * tempNode;
    char temp[150];

    if(!root)
        return 0;

    IGetAbsolutePath(root,temp);
    if(!strcmp(temp,path))   //比较路径，一致则返回
        return root;
    
    tempNode=IFindNodeByPath(path,root->child); //深度优先搜索
    if(tempNode)
        return tempNode;

    tempNode=IFindNodeByPath(path,root->next);
    if(tempNode)
        return tempNode;
    
    return 0;   //未找到，则返回NULL
}

/*
    函数功能：根据文件名找到节点
    输入参数：name——文件名, root——起始根节点
    输出参数：无
    返回值：若找到，返回该节点；否则返回NULL
*/
IFileNode * IFindNodeByName(char * name,IFileNode * root)
{
    IFileNode * temp;

    if(!root)
        return 0;

    if(!strcmp(root->file.name,name))   //比较文件名，一致则返回
        return root;
    
    temp=IFindNodeByName(name,root->next);     //广度优先搜索
    if(temp)
        return temp;

    temp=IFindNodeByName(name,root->child);
    if(temp)
        return temp;
    
    return 0;   //未找到，则返回NULL
}

/*
    函数功能：判断节点是否为目录
    输入参数：node——待判断的节点
    输出参数：无
    返回值：是目录则返回1，不是目录则返回0
*/
int IisFolder(IFileNode * node)
{
    return (node->file.type[0]=='0')||(node->file.type[0]=='1');
}

/*
    函数功能：根据节点得到绝对路径
    输入参数：node——文件节点
    输出参数：temp——文件的绝对路径
    返回值：无
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
    函数功能：返回文件节点的父节点
    输入参数：child——子节点
    输出参数：无
    返回值：父节点
*/
IFileNode * IFindParent(IFileNode * child)
{
    IFileNode * temp=child;
    
    if(temp->file.type[1]=='\\')
        return NULL;
    //如果child是DOS根节点, 则返回NULL

    while(!(temp->flags&4))    //找到链表头
    {
        temp=temp->pre;
    }
    return temp->pre;
}

/*
    函数功能：根据文件路径得到文件名
    输入参数：path——文件路径
    输出参数：name——文件名
    返回值：无
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
    函数功能：判断path2是否为path1的子路径
    输入参数：path1——父路径, path2——子路径
    输出参数：无
    返回值：若path2是否为path1的子路径, 返回1; 否则返回0
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
