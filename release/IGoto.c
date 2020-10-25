#include"IGoto.h"

/*
    函数功能：直接进入目录
    输入参数：path——路径
    输出参数：cur——当前节点
    返回值：无
*/
void IGotoFrom(IFileNode *j,IFileNode *cur)
{
    int num=(int)j;
    FILE *searched=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","r");
    IFileNodePointer **curNode=(IFileNodePointer**)cur;
    IFileNode* tempNode=(*curNode)->child;
    char tempStr[PATH_LEN],tempName[PATH_LEN];
    int i;

    while(num--)
        fgets(tempStr,PATH_LEN,searched);
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
        }
        else
        {
            IEntreeActive(tempNode,cur);
            strcpy(tempStr,tempStr+1);
            if(tempStr[strlen(tempStr)-1]=='\n')
                tempStr[strlen(tempStr)-1]='\0';
            tempNode=IFindNodeByName(tempStr,tempNode->child);
            tempNode->flags|=NODE_ADD_SELECT;
            break;
        }
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
    IFileNode *initNode=(*curNode)->child;
    IFileNode *tempNode=initNode;
    char tempStr1[PATH_LEN],tempStr2[PATH_LEN];
    char flag=0;
    int i,n;

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
        }
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
        }
    }
    return 1;
}