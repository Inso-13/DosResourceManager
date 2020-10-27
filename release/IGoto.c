/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-4
 *   说明：根据路径进入指定位置的函数
 **************************************************
 */

#include"IGoto.h"

/*
    函数功能：直接进入目录
    输入参数：path——路径
    输出参数：cur——当前节点
    返回值：无
*/
void IGotoFrom(IFileNode *j,IFileNode *cur)
{
    int num=(int)j;                                             //选择的节点的位置
    FILE *searched=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","r");    //查找到的文件
    IFileNodePointer **curNode=(IFileNodePointer**)cur;         //当前节点链表
    IFileNode* tempNode=(*curNode)->child;                      //循环辅助节点
    char tempStr[PATH_LEN],tempName[PATH_LEN];                  //辅助字符串
    int i;                                                      //循环辅助整型变量

    while(num--)
        fgets(tempStr,PATH_LEN,searched);                       //得到文件的绝对路径
    fclose(searched);

    IGetAbsolutePath(tempNode,tempName);
    strcpy(tempStr,tempStr+strlen(tempName));
    while(1)
    {
        for(i=1;i<strlen(tempStr);i++)
        {
            if(tempStr[i]=='\\')
                break;
        }
        if(i<strlen(tempStr))
        {
            strcpy(tempName,tempStr+1);
            tempName[i-1]='\0';
            IEntreeActive(tempNode,cur);
            tempNode=IFindNodeByName(tempName,tempNode->child);
            strcpy(tempStr,tempStr+i);
        }   //分割文件的绝对路径，层层进入目录
        else
        {
            IEntreeActive(tempNode,cur);
            strcpy(tempStr,tempStr+1);
            if(tempStr[strlen(tempStr)-1]=='\n')
                tempStr[strlen(tempStr)-1]='\0';
            tempNode=tempNode->child;
            while(tempNode->next)
            {
                tempNode->flags&=NODE_DEL_SELECT;
                tempNode=tempNode->next;
            }   //取消目标目录下其他的选中
            tempNode->flags&=NODE_DEL_SELECT;
            tempNode=IFindParent(tempNode);
            tempNode=IFindNodeByName(tempStr,tempNode->child);
            tempNode->flags|=NODE_ADD_SELECT;
            break;
        }   //选中目标文件
    }
}

/*
    函数功能：直接进入目录
    输入参数：path——路径
    输出参数：cur——当前节点
    返回值：无
*/
char IGoto(char *path,IFileNodePointer **curNode)
{
    IFileNode *initNode=(*curNode)->child;       //curNode的初始值，失败时重新赋给curNode
    IFileNode *tempNode=initNode;                //循环辅助节点
    char tempStr1[PATH_LEN],tempStr2[PATH_LEN];  //辅助字符串
    char flag=0;                                 //标志位，用于区分文件与文件夹
    int i,n;                                     //循环辅助变量

    if(path[strlen(path)-1]=='\\')
        flag=1;
    while(tempNode->pre)
    {
        tempNode=tempNode->pre;
    }   //tempNode==DRM
    
    strcpy(tempStr1,path);
    while(1)
    {
        n=strlen(tempStr1);
        if(!n)
            break;
        for(i=0;i<n;i++)
        {
            if(tempStr1[i]>='a'&&tempStr1[i]<='z')
                tempStr1[i]+='A'-'a';
            else if(tempStr1[i]=='\\')
                break;
        }   //将路径转换为大写
        strcpy(tempStr2,tempStr1);
        tempStr2[i]='\0';

        if(i==n)
            strcpy(tempStr1,tempStr1+n);
        else
            strcpy(tempStr1,tempStr1+i+1);
        
        IEntreeActive(tempNode,(IFileNode*)curNode);
        tempNode=IFindNodeByName(tempStr2,tempNode->child);
        if(flag)
            IEntreeActive(tempNode,(IFileNode*)curNode);
            
        if(!tempNode)
        {
            IEntreeActive(initNode,(IFileNode*)curNode);
            return 0;
        }   //如果失败，回到原来的路径
    }
    return 1;
}