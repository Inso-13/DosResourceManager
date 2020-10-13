/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-7
 *   说明：磁盘初始化函数
 **************************************************
 */

#include"IDisk.h"

/*
    函数功能：初始化文件根节点
    输入参数：id——用户身份
    输出参数：无
    返回值：根文件节点
*/
IFileNode *IDiskInit(char id)
{
    IFileNode *root=(IFileNode*)malloc(sizeof(IFileNode)); //根节点
    IFileNode *rootC=(IFileNode*)malloc(sizeof(IFileNode)); //C盘节点
    IFileNode *tempNode=rootC,*lastNode=rootC;  //辅助文件节点 
    int i,disk; //循环变量
    char temp[3];  //辅助字符串

    IFileNodeSetNull(root); 
    IFileNodeSetNull(rootC);
    root->child=rootC;
    strcpy(root->file.type,"1\\");
    strcpy(root->file.name,ROOT_NAME);
    root->flags=NODE_IS_HEAD+NODE_HAS_FOLDER;
    rootC->pre=root;
    rootC->flags|=NODE_IS_HEAD;
    strcpy(temp,"C:");  //节点初始化
    
    for(i=0;i<26;i++)   //遍历26个英文字母，查找所有磁盘
    {
        setdisk(i);
        disk=getdisk();
        if(disk==i)     //如果磁盘存在，初始化磁盘节点
        {
            if(disk<2||disk>24)
                continue;
            tempNode->file.date=33;
            tempNode->file.time=0;
            tempNode->file.size=-1;
            tempNode->flags|=8;
            if(disk==2&&id==0)  //如果是游客，保护C盘
                strcpy(tempNode->file.type,"0ds");
            else    //如果是管理员，不需要保护C盘
                strcpy(tempNode->file.type,"0d");
            temp[0]=disk+'A';
            strcpy(tempNode->file.name,temp);
            tempNode=(IFileNode*)malloc(sizeof(IFileNode));    //申请新内存
            IFileNodeSetNull(tempNode); //节点初始化
            lastNode->next=tempNode;
            tempNode->pre=lastNode;
            lastNode=lastNode->next;
        }
    }
    lastNode->pre->next=NULL;
    free(lastNode); //释放lastNode节点
    setdisk(2);     //回到C盘
    return root;    //返回磁盘节点的根节点
}