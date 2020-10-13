/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：与文件节点操作相关的部分函数，比较底层
 **************************************************
 */

#include"INode.h"

/*
    函数功能：添加子节点
    输入参数：parent——父节点, child——子节点
    输出参数：无
    返回值：成功则返回1, 失败则返回0
*/
int IAddChild(IFileNode *parent,IFileNode *child)
{
    IFileNode *temp=NULL;

    if(!parent) return 0;
    //父节点为空，返回0
    
    if(!strcmp(child->file.name,""))
    {
        free(child);
        child=NULL;
        return 0;
    }
    //子节点为僵尸节点，清除并返回0
    
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
    //如果父节点已有子节点
    else
    {
        parent->child=child;
        child->pre=parent;
        child->flags|=NODE_ADD_HEAD;
    }
    //如果父节点未有子节点
    return 1;   
    //成功添加，返回1
}

/*
    函数功能：得到路径下的所有文件，以链表的形式返回
    输入参数：path——绝对路径
    输出参数：无
    返回值：路径下的文件链表
*/
IFileNode *IGetFileNodeList(char *path)
{
    IFileNode *childRoot=(IFileNode*)malloc(sizeof(IFileNode)),*tempNode=childRoot,*lastNode=childRoot;
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
    //"*.*"， 0xf7所有文件节点   ft存储查找结果
    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,"..")||!strcmp(ft.name,"WINDOWS")||IStartWith(ft.name,"DOCUME")||IStartWith(ft.name,"$")||IStartWith(ft.name,"PROGRA")||IStartWith(ft.name,"360")||IStartWith(ft.name,"NTLDR")||IStartWith(ft.name,"SYSTE")||IEndWith(ft.name,"SYS")||IEndWith(ft.name,"INI")||IEndWith(ft.name,"COM")||IEndWith(ft.name,"BIN"))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }   //跳过无用节点
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
            for(i=0;i<strlen(tempNode->file.name);i++)
            {
                if(tempNode->file.name[i]=='.')
                {
                    strcpy(tempNode->file.type,tempNode->file.name+i+1);
                    break;
                }
                if(i==strlen(tempNode->file.name)-1)
                    strcpy(tempNode->file.type,"NOT");
            }
        }
        tempNode->file.date=ft.wr_date;
        tempNode->file.time=ft.wr_time;
        //初始化新节点

        ret=_dos_findnext(&ft);
        //查找下一个节点

        if(ret) break;
        if(j>MAXNODES) break;
        //如果该路径下节点数大于120, 则不再继续查找

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
    函数功能：在parent文件夹中添加name文件节点
    输入参数：parent——父节点, name——子节点文件名
    输出参数：无
    返回值：成功则返回1, 失败则返回0
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
    //查找name文件

    if(ret) return 0;   
    //查找不到，返回0
        
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
    //初始化该节点

    return IAddChild(parent,child);
}

/*
    函数功能：在parent文件夹中删除name文件节点
    输入参数：parent——父节点, name——子节点文件名
    输出参数：无
    返回值：成功则返回1, 失败则返回0
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
    //如果是链表头
    else
    {
        child->pre->next=child->next;
        if(child->next) child->next->pre=child->pre;
    }
    //如果不是链表头

    free(child);
    return 1;
}

/*
    函数功能：递归删除整个链表
    输入参数：root要删除的文件书根节点
    输出参数：无
    返回值：无
*/
void IDelFilelist(IFileNode *root)
{
    if(root->child)
    {
        IDelFilelist(root->child);
    }
    //深度优先
    if(root->next)
    {
        IDelFilelist(root->next);
    }
    free(root);
    root=NULL;
}

/*
    函数功能：递归添加整个树
    输入参数：root要增枝的文件书根节点
    输出参数：无
    返回值：无
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
    //深度优先

    if(root->next)
        IAddFilelist(root->next);
}

/*
    函数功能：查看文件夹内是否有子文件夹
    输入参数：node——目标节点, path——绝对路径
    输出参数：无
    返回值：若有子文件夹，返回1; 否则返回0
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
    函数功能：更换磁盘并进入目录
    输入参数：path——绝对路
    输出参数：无
    返回值：无
*/
void Icd(char *path)
{
    char temp[PATH_LEN]="";

    if(path[1]==':'&&getdisk()!=(path[0]-'A'))  //当前磁盘与目标不一致
    {
        setdisk(path[0]-'A');   //更改磁盘
    } 
    if(strlen(path)<=3)     //路径标准化
    {
        strcpy(temp,path);
        strcpy(temp+1,"");
        strcat(temp,":\\.");
        chdir(temp);
    }   
    chdir(path);    //更改目录
}