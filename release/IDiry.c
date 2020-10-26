/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：Diry以DirBase为基础，提供了基本可以被前端直接使用的文件操作函数
 **************************************************
 */

#include"IDiry.h"

/*
    函数功能：建立新文件
    输入参数：pathNode——路径节点, fileName——新文件名
    输出参数：无
    返回值：复制成功返回1，失败则返回0
*/
int Inew(IFileNode *pathNode,char *fileName)
{
    char temp[PATH_LEN],tempStr1[PATH_LEN];  //辅助字符串
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","r+");
    long len=0;
    int i;

    for(i=0;i<strlen(fileName);i++)
    {
        if(fileName[i]>='a'&&fileName[i]<='z')
            fileName[i]+='A'-'a';
    }
    IGetAbsolutePath(pathNode,temp);
    Icd(temp);  //进入当前目录
    strcat(temp,"\\");
    strcat(temp,fileName);
    
    if(creatnew(fileName,0)==-1)
        return 0;
    //创建失败，返回0

    while(fgets(tempStr1,PATH_LEN,fp))
    {
        if(tempStr1[strlen(tempStr1)-1]=='\n')
            tempStr1[strlen(tempStr1)-1]='\0';
        if(!strcmp(tempStr1,temp))
        {
            fseek(fp,len+1,SEEK_SET);
            fputc('|',fp);
            break;
        }
        len+=strlen(tempStr1)+2;
    }
    fclose(fp);
    
    return IAddFileNode(pathNode,fileName);
    //创建成功，添加到文件树中，返回1 
}

/*
    函数功能：重命名文件/文件夹
    输入参数：oldName——旧文件节点, newName——新文件名
    输出参数：无
    返回值：无
*/
void Irename(IFileNode *oldName,char *newName)
{
    char temp[PATH_LEN];  //辅助字符串
    struct find_t ft;  //查找文件结构体
    int i;  //循环变量

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  
    //重命名文件/文件夹

    strcpy(oldName->file.name,newName);
    for(i=strlen(oldName->file.name)-1;i>=0;i--)
    {
        if(oldName->file.name[i]=='.')
        {
            oldName->file.type[0]=oldName->file.name[i+1];
            oldName->file.type[1]=oldName->file.name[i+2];
            oldName->file.type[2]=oldName->file.name[i+3];
            oldName->file.type[3]='\0';
            break;
        }
        if(i==-1) //如果没有后缀名
        {
            _dos_findfirst(newName,0xf7,&ft);
            if(!(ft.attrib&FA_DIREC))   //如果不是文件夹
                strcpy(oldName->file.type,"NOT");
        }
    }
    //调整文件的类型
}

/*
    函数功能：将root目录下的文件从文件树上减除
    输入参数：root——需要减除的目录
    输出参数：无
    返回值：无
*/
void IDetree(IFileNode *root)
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
    
    if(root->child)
    {
        IDelFilelist(root->child);
        root->child=NULL;
    }
    //将root目录下的文件从文件树上减除
}

/*
    函数功能：将root目录下的文件加到文件树上
    输入参数：root——需要增枝的目录,flag——控制位
    输出参数：无
    返回值：无
*/
void IEntree(IFileNode *root,char flag)
{
    IFileNode *childRoot=NULL;
    char temp[PATH_LEN];

    if(!root) return;
    //若root==NULL，直接返回
    if(!IisFolder(root)) return;
    //若root不是文件夹，直接返回
    if(!strcmp(root->file.type,"0ds")) return;
    //若root是被保护的磁盘，直接返回
    if(root->file.type[0]=='1'||root->child)
    {
        if(flag)
        {
            IDetree(root);
            root->flags&=NODE_DEL_TO_REENTREE;
        }
        else 
            return;
    }
    //若root已被打开，重新打开
    root->file.type[0]='1';
    //打开文件夹
    if(root->file.type[1]=='\\') return;
    //若目录为根目录，置1返回
    IGetAbsolutePath(root,temp);
    childRoot=IGetFileNodeList(temp);
    if(childRoot)
        IAddChild(root,childRoot);
    //将root目录下的文件加到文件树上
    while(childRoot)
    {
        if(IisFolder(childRoot))
        {
            IGetAbsolutePath(childRoot,temp);
            if(IPeek(childRoot,temp))
                childRoot->flags|=NODE_HAS_FOLDER;
        }
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
void Icplr(IFileNode *oldParent,IFileNode *newParent,char flag)
{
    IFileNode *tempNode=oldParent->child,*newF=NULL;
    char temp[PATH_LEN];    //储存文件路径

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            Icpr(tempNode,newParent,flag);
            if(IisFolder(tempNode)) //如果是文件夹
            {
                newF=IFindNodeByName(tempNode->file.name,newParent);
                IGetAbsolutePath(newF,temp);
                if(IPeek(newF,temp))
                    newF->flags|=NODE_HAS_FOLDER;
            }
        } 
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
void Irmlr(IFileNode *oldParent)
{
    IFileNode *tempNode=oldParent->child;

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            Irmr(tempNode);
            if(IisFolder(tempNode))
                Irmdir(tempNode);
        }
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
void ISearch(char *path,char *pattern,FILE *fp)
{
    int ret,i;
    struct find_t ft;
    char temp[PATH_LEN];  //辅助字符串

    Icd(path);  //进入当前路径
    ret=_dos_findfirst("*.*", 0xf7,&ft);  //搜索全部文件
    while(1)
    {
        while(!strcmp(ft.name,".")||!strcmp(ft.name,"..")||!strcmp(ft.name,"WINDOWS")\
        ||IStartWith(ft.name,"DOCUME")||IStartWith(ft.name,"$")||\
        IStartWith(ft.name,"PROGRA")||IStartWith(ft.name,"360")||\
        IStartWith(ft.name,"NTLDR")||IStartWith(ft.name,"SYSTE")||\
        IEndWith(ft.name,"SYS")||IEndWith(ft.name,"INI")||\
        IEndWith(ft.name,"COM")||IEndWith(ft.name,"BIN"))
        {
            ret=_dos_findnext(&ft);
            if(ret) break;
        }
        if(ret) break;
        //排除无用文件路径或被保护的文件路径

        if(IMatch(ft.name,pattern))
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            strcat(temp,"\n");
            fputs(temp,fp);
        }
        //如果匹配，记录进fp文件

        if(ft.attrib&FA_DIREC)
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            ISearch(temp,pattern,fp);
        }
        //如果是文件夹，递归查找

        Icd(path);  //回到当前路径
        ret=_dos_findnext(&ft); //查找下一项
    }
}
