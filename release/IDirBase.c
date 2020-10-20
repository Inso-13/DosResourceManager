/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：DiryBase作为Diry库的底层支撑，封装了许多常用的文件操作函数
 **************************************************
 */

#include"IDirBase.h"

/*
    函数功能：复制单个文件，将inFile文件复制到outParent文件夹内，并更新节点
    输入参数：inFile——等待复制的文件, outParent——粘贴到的目标文件夹，flag——是否强制覆盖
    输出参数：无
    返回值：复制成功返回1，失败则返回0
*/
int Icopy(IFileNode *inFile,IFileNode *outParent,char flag)
{
    char inPath[PATH_LEN];  //输入文件的路径
    char outPath[PATH_LEN]; //输出文件夹的路径
    char temp[PATH_LEN]; //辅助字符串
    char i[2],name[18],ext[5]; //文件名，后缀名
    char tempStr[30+2*PATH_LEN];  //命令行辅助字符串
    int j;  //循环辅助变量，记录后缀名的分界点

    IGetAbsolutePath(inFile,inPath);    //得到输入文件的路径
    IGetAbsolutePath(outParent,outPath);    //得到输出文件夹的路径
    strcat(outPath,"\\");
    strcat(outPath,inFile->file.name);      //得到输出文件的路径
    strcpy(name,inFile->file.name);     //获取文件名
    
    if(!flag)   //如果不需要强制覆盖
    {
        if(ISearchPath(outPath)||!strcmp(inPath,outPath)) //原位置拷贝，文件自动重命名
        {
            strcpy(i,"1");
            for(j=0;j<strlen(inFile->file.name);j++)
                if(inFile->file.name[j]=='.')
                    break;
            strcpy(ext,inFile->file.name+j);
            if(strlen(name)>11||(j==strlen(name)&&j>7)) //如果文件名过长
            {
                strcpy(name+4,"~"); //添加省略符
                strcpy(name+5,ext); //复制后缀名
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
            }while(ISearchPath(temp));  //不断改变后缀，直到文件名合法
            strcpy(outPath,temp);
        } // end of if(ISearchPath(outPath)||!strcmp(inPath,outPath))
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        strcat(tempStr+strlen(tempStr),outPath);

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);
    }
    else    //如果需要强制覆盖
    {
        Irmf(IFindNodeByPath(outPath,outParent));   //删除原有文件
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        IGetAbsolutePath(outParent,tempStr+strlen(tempStr));

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);    //复制新文件
    }   // end of if(!flag)

    IAddFileNode(outParent,name);   //添加新文件节点
    return 1;
}

/*
    函数功能：彻底删除文件
    输入参数：fileNode——等待删除的文件
    输出参数：无
    返回值：删除成功返回1，失败则返回0
*/
int Irmf(IFileNode *fileNode)
{
    char tempStr[PATH_LEN];   //辅助字符串
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");    //打开删除辅助文件

    IGetAbsolutePath(fileNode,tempStr);
    strcat(tempStr,"\n");
    fputs(tempStr,fp);

    strcpy(tempStr,"del ");
    IGetAbsolutePath(fileNode,tempStr+4);
    strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
    system(tempStr);    //删除文件

    fclose(fp);    //关闭删除辅助文件
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name); //删除文件节点
}

/*
    函数功能：创建文件夹，并更新节点
    输入参数：pathNode——父节点, folderName——新文件夹名
    输出参数：无
    返回值：创建文件夹成功返回1，失败则返回0
*/
int Imkdir(IFileNode *pathNode,char *folderName)    
{
    char temp[PATH_LEN];     //辅助字符串
    
    IGetAbsolutePath(pathNode,temp);
    strcat(temp,"\\");
    strcat(temp,folderName);    //得到新文件夹的绝对路径

    if(mkdir(temp)==-1) //如果创建文件夹失败
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
int Irmdir(IFileNode *node)
{
    int i=0;    //循环辅助变量
    char temp[PATH_LEN];      //辅助字符串
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");    //打开删除辅助文件

    IGetAbsolutePath(node,temp);    
    strcat(temp,"\n");
    fputs(temp,fp);     //将要删除的文件夹记录到辅助文件里

    IGetAbsolutePath(node,temp);
    IDelFileNode(IFindParent(node),node->file.name);    //删除文件节点

    for(i=0;i<100;i++)
        if(ISearchPath(temp))
            rmdir(temp);    //不断尝试删除文件夹
        else 
            break;
            
    fclose(fp);  //关闭删除辅助文件
    return 1;
}

/*
    函数功能：复制整个文件链表
    输入参数：oldChildChild——要复制的文件夹中的第一个节点, newChild——要粘贴到的文件夹内部
    输出参数：无
    返回值：无
*/
void ICopyAll(IFileNode *oldChildChild,IFileNode *newChild)
{
    while(oldChildChild)
    {
        if(IisFolder(oldChildChild))    //如果是文件夹，递归复制
        {
            if(!oldChildChild->child)   //如果文件未被打开
                IEntree(oldChildChild,UNFORCED);
            Imkdir(newChild,oldChildChild->file.name); //创建文件夹
            if(oldChildChild->child)    //如果有子节点
            {
                ICopyAll(oldChildChild->child,\
                IFindNodeByName(oldChildChild->file.name,newChild));  //复制整个链表
                IDetree(oldChildChild); //删除原链表
            }
        }
        else    //如果文件
        {
            Icopy(oldChildChild,newChild,UNFORCED);   //复制文件
        }
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
void Icpr(IFileNode *oldChild,IFileNode *newParent,char flag)
{
    char temp[PATH_LEN];      //辅助字符串
    IFileNode *tempNode=NULL;   //辅助节点

    if(IisFolder(oldChild)) //如果是文件
    {
        IGetAbsolutePath(newParent,temp);
        strcat(temp,"\\");
        strcat(temp,oldChild->file.name);

        if(ISearchPath(temp))
        {
            if(flag)    //如果是强制覆盖
                Irmr(IFindNodeByPath(temp,newParent));
            else
                return;
        }
        Imkdir(newParent,oldChild->file.name);  //创建文件夹
        IEntree(oldChild,UNFORCED);  
        tempNode=IFindNodeByPath(temp,newParent);
        tempNode->flags|=NODE_TO_REENTREE;
        ICopyAll(oldChild->child,tempNode);
        IDetree(oldChild);    //释放原节点的内存
    }
    else
        Icopy(oldChild,newParent,flag); //如果是文件
}  

/*
    函数功能：删除链表
    输入参数：oldChildChild——要删除的文件夹中的第一个节点
    输出参数：无
    返回值：无
*/
void IDelAll(IFileNode *oldChildChild)
{
    IFileNode *nextNode=NULL;   //辅助文件节点

    while(oldChildChild)
    {
        nextNode=oldChildChild->next;
        if(IisFolder(oldChildChild))    //如果是文件夹
        {
            if(!oldChildChild->child)
                IEntree(oldChildChild,UNFORCED);
            IDelAll(oldChildChild->child);
            Irmdir(oldChildChild);
        }
        else    //如果是文件
        {
            Irmf(oldChildChild);   //删除文件 
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
void Irmr(IFileNode *oldChild)
{
    if(IisFolder(oldChild)) //如果是文件夹
    {
        IEntree(oldChild,UNFORCED);
        if(oldChild->child)
            IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    //删除文件夹中所有的文件
}

/*
    函数功能：判断是否有name文件
    输入参数：name——文件绝对/相对路径
    输出参数：无
    返回值：若存在改文件返回1; 否则返回0
*/
int ISearchPath(char *name)
{
    struct find_t ft;   //查找结构体

    return !_dos_findfirst(name,0xf7,&ft); 
    //查找是否有名叫name的文件
}