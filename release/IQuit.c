/*
 **************************************************
 *   版本号：1.0
 *   作者：郭一菲
 *   生成日期：2020-9-4
 *   说明：主要定义了异常退出函数
 **************************************************
 */

#include "IQuit.h"

/*
    函数功能：退出程序
    输入参数：无
    输出参数：无
    返回值：无
*/
void IQuit()
{
    closegraph();   //关闭图形界面
    fcloseall();    //关闭所有文件
    exit(0);    //退出
}

/*
    函数功能：析构curNode链表
    输入参数：pointer——curNode节点
    输出参数：无
    返回值：无
*/
void IDelPointer(IFileNodePointer* pointer)
{
    IFileNodePointer* tempNode=pointer;
    while(tempNode->next)
    {
        tempNode=tempNode->next;
    }
    //找到链表尾

    while(tempNode->pre)
    {
        tempNode=tempNode->pre;
        free(tempNode->next);
        tempNode->next=NULL;
    }
    free(tempNode);
}
