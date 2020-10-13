/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：将Diry函数的接口统一化，供前端调用栈使用
 **************************************************
 */

#include"IDirActive.h"

/*
    函数功能：激活IEntree函数，更改当前节点
    输入参数：node——需要IEntree的节点
    输出参数：cur——当前节点
    返回值：无
*/
void IEntreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //当前节点
	IFileNodePointer *newCurNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));     //新节点
    IFileNodePointer *tempNode=NULL,*nextNode=NULL;    //循环辅助节点

    tempNode=(*curNode)->next;  //tempNode指向循环的下一项
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }//假如curNode链表有后一项，递归删除后面的所有节点

    newCurNode->child=node;
    newCurNode->next=NULL;
    newCurNode->wait=WAIT_COUNT;
    newCurNode->pre=*curNode;
    (*curNode)->next=newCurNode;
    *curNode=newCurNode;
    //新节点初始化

    IEntree(node,node->flags&NODE_TO_REENTREE);   //激活IEntree函数

    tempNode=(*curNode)->pre;
    while(tempNode)
    {
        tempNode->wait--;   //减少前面节点的等待次数
        if(tempNode->wait<WAIT_OFF)    //如果节点的等待次数不足0
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        else
            tempNode=tempNode->pre;
    }   //end of while(tempNode)
    //删除curNode链表中的超时节点，以节约内存
}

/*
    函数功能：激活IDetree函数，更改当前节点
    输入参数：node——需要IDetree的节点
    输出参数：cur——当前节点
    返回值：无
*/
void IDetreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //当前节点
    IFileNodePointer *tempNode=NULL,*nextNode=NULL,*lastNode=NULL;    //循环辅助节点
    char path1[PATH_LEN],path2[PATH_LEN];  //辅助字符串

    if(node->file.type[1]=='\\') return;    //如果是根节点，直接返回

    tempNode=(*curNode)->next;  
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }   //假如curNode链表有后一项，递归删除后面的所有节点

    tempNode=(*curNode);
    IGetAbsolutePath(node,path2);   //得到要删除节点的位置
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);    //得到需检查的节点的位置
        if(IisChild(path1,path2))   //如果发生冲突
        {
            if(tempNode->pre)
            {
                if(tempNode->next)
                {
                    tempNode=tempNode->pre;
                    tempNode->next=tempNode->next->next;
                    free(tempNode->next->pre);
                    tempNode->next->pre=tempNode;
                }
                else
                {
                    tempNode=tempNode->pre;
                    free(tempNode->next);
                    tempNode->next=NULL;
                    (*curNode)=tempNode;
                }
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
                break;
            }
        }
        tempNode=lastNode;
    }   //如果curNode链表中有node节点，将该节点从链表中除去

    if(node->file.type[1]!='\\')
        (*curNode)->child=IFindParent(node);    //更改curNode节点

    IDetree(node);  //激活IDetree函数

    node->file.type[0]='0'; //关闭文件夹
}

/*
    函数功能：在激活IEntree函数后，回收垃圾内存
    输入参数：X——辅助文件节点
    输出参数：cur——当前节点
    返回值：无
*/
void IAfterEntree(IFileNode *cur,IFileNode *X)
{
#ifdef LM   //在内存有限时使用
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //当前节点
    IFileNodePointer *nodeX=(IFileNodePointer*)X;    //辅助文件节点
    IFileNodePointer *tempNode=(*curNode)->pre,*lastNode=tempNode->pre;    //循环使用
    char path1[PATH_LEN],path2[PATH_LEN],path[PATH_LEN];   //暂存字符串

    IGetAbsolutePath((*curNode)->child,path1);  //获得当前位置
    if(nodeX&&nodeX->child)     //如果nodeX不为空           
        IGetAbsolutePath(nodeX->child,path2);   //得到nodeX指向的路径
    else          
        strcpy(path2,"");   //如果为空就将路径置为空

    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path);     //得到待检查的链表节点
        if(strcmp(path,ROOT_NAME)&&strcmp(path,path1)&&strcmp(path,path2)&&!IisChild(path1,path)&&!IisChild(path2,path))
        {           //如果发生冲突
            IDetree(tempNode->child);   //释放节点
            if(tempNode->pre)
            {
                tempNode=tempNode->pre;
                tempNode->next=tempNode->next->next;
                free(tempNode->next->pre);
                tempNode->next->pre=tempNode;
            }
            else
            {
                tempNode->next->pre=NULL;
                free(tempNode);
            }   //从链表中删除节点
        }
        tempNode=lastNode;  //继续检查
    }   //end of while(tempNode)
#endif
}
