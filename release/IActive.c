/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ���һ��
 *   �������ڣ�2020-9-4
 *   ˵����Active�ຯ�������м�㣬���ڽ���ˣ���Diry�ȣ������Ľӿ�ͳһ������ǰ�˵���ջʹ��
 **************************************************
 */

#include"IActive.h"

/*
    �������ܣ��ڼ���IEntree�����󣬻��������ڴ�
    ���������X���������ļ��ڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IAfterEntree(IFileNode* cur,IFileNode* X)
{
#ifdef LM
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=(*curNode)->pre,*lastNode=tempNode->pre;
    char path1[150],path2[150],path[150];

    IGetAbsolutePath((*curNode)->child,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);
    else
        strcpy(path2,"");

    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path);
        if(strcmp(path,"DOS")&&strcmp(path,path1)&&strcmp(path,path2)&&!IisChild(path1,path)&&!IisChild(path2,path))
        {
            IDetree(tempNode->child);
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
            }
        }
        tempNode=lastNode;
    }
#endif
}

/*
    �������ܣ�����IEntree���������ĵ�ǰ�ڵ�
    ���������node������ҪIEntree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IEntreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
	IFileNodePointer * newCurNode=(IFileNodePointer *)malloc(sizeof(IFileNodePointer));     //�½ڵ�
    IFileNodePointer * tempNode=NULL,*nextNode=NULL;

    tempNode=(*curNode)->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    //����curNode�����к�һ��ݹ�ɾ����������нڵ�

    newCurNode->child=node;
    newCurNode->next=NULL;
    newCurNode->wait=10;
    newCurNode->pre=*curNode;
    (*curNode)->next=newCurNode;
    *curNode=newCurNode;
    //�½ڵ��ʼ��

    IEntree(node,node->flags&16);
    //����IEntree����

    tempNode=(*curNode)->pre;
    while(tempNode)
    {
        tempNode->wait--;
        if(tempNode->wait<0)
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
    }
    //ɾ��curNode�����еĳ�ʱ�ڵ㣬�Խ�Լ�ڴ�
}

/*
    �������ܣ����������nodeX��ΪNULL
    ���������node������ҪIDetree�Ľڵ�
    ���������X���������ļ��ڵ�
    ����ֵ����
*/
void ISetXNull(IFileNode* node,IFileNode* X)
{
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    char path1[150],path2[150];

    if(node->file.type[1]=='\\')
        return;

    IGetAbsolutePath(node,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);   
    if(!strcmp(path1,path2)||IisChild(path2,path1))
        nodeX->child=NULL;
}

/*
    �������ܣ�����IDetree���������ĵ�ǰ�ڵ�
    ���������node������ҪIDetree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IDetreeActive(IFileNode* node,IFileNode* cur)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
    IFileNodePointer * tempNode,*nextNode,*lastNode;
    char path1[150],path2[150];

    if(node->file.type[1]=='\\') return;

    tempNode=(*curNode)->next;
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }
    //����curNode�����к�һ��ݹ�ɾ����������нڵ�

    tempNode=(*curNode);
    IGetAbsolutePath(node,path2);
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);
        if(IisChild(path1,path2))
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
    }
    //���curNode��������node�ڵ㣬���ýڵ�������г�ȥ

    if(node->file.type[1]!='\\')
        (*curNode)->child=IFindParent(node);
    //����curNode�ڵ�

    IDetree(node);
    //����IDetree����

    node->file.type[0]='0';
    //�ر��ļ���
}

/*
    �������ܣ���View1�У���һ�أ�ѡ���ļ��ڵ㣬��ʾ����
    ���������node������ѡ�еĽڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISelect(IFileNode* node,IFileNode* null)
{
    IFileNode* tempNode=IFindParent(node)->child;

    while(tempNode)
    {
        tempNode->flags&=29;
        tempNode=tempNode->next;
    }
    //�����ǰ·�����Ѿ��б�ѡ�еĽڵ㣬���ýڵ���Ϊδ��ѡ��

    node->flags|=2;
    //ѡ�иýڵ�
}

/*
    �������ܣ���View1�У����ϵأ�ѡ���ļ��ڵ㣬��ʾ����
    ���������node������ѡ�еĽڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ICtrlSelect(IFileNode* node,IFileNode* null)
{
    if(!(node->flags&2))
        node->flags|=2;
    else
        node->flags&=5;
    //����ýڵ��ѱ�ѡ�У����ѡ�У�����ѡ�иýڵ�
}

/*
    �������ܣ��ղ�����������ռλ/�ض�/ˢ�µ�
    ���������null1��������ռλ, null2��������ռλ
    �����������
    ����ֵ����
*/
void INOP(IFileNode* null1,IFileNode* null2){}

/*
    �������ܣ�������һĿ¼
    ���������null��������ռλ
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGoLeftActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;
    //������һĿ¼
}

/*
    �������ܣ�������һĿ¼
    ���������null��������ռλ
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGoRightActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;
    //������һĿ¼
}

/*
    �������ܣ�������Һ���
    ���������cur������ǰ�ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISearchActive(IFileNode* cur,IFileNode* null)
{
    IFileNodePointer * curNode=(IFileNodePointer *)cur;
    FILE* fp=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+"); //���ǵķ�ʽ�����ڼ�¼���ļ�
    char temp[20],path[150];     //�����ַ���

    IGetAbsolutePath(curNode->child,path);  //�����Ҫ���ҵ�·��
    strcpy(temp,"\0");
    IGetString(851+DF,51+DF,166,temp,1);  
    //�õ����ҵ�pattern

    setfillstyle(SOLID_FILL,255);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(144);
    outtextxy(900+DF,753+DF,"Searching...");

    if(temp[0])
        ISearch(path,temp,fp);
    //������Һ���
    fclose(fp);

    setfillstyle(SOLID_FILL,255);
    bar(900+DF,745+DF,1020+DF,765+DF);
}

/*
    �������ܣ���exe���ļ�
    ���������exe������ִ�е��ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void IexeActive(IFileNode* exe,IFileNode* null)
{
    char temp[180];

    IGetAbsolutePath(exe,temp);

    setfillstyle(SOLID_FILL,0);
    bar(0,0,1280,1024);
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");
    system(temp);
    //ϵͳ���ã����ñ༭�����ı��ļ�
    delay(2000);
    IQuit();
}

/*
    �������ܣ���txt���ļ�
    ���������txt�����ɱ༭���ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ItxtActive(IFileNode* txt,IFileNode* null)
{
    char temp[150];

    strcpy(temp,"C:\\BORLANDC\\BIN\\BC.EXE ");
    IGetAbsolutePath(txt,temp+23);
    
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");
    system(temp);
    //ϵͳ���ã�����BC�༭�����ı��ļ�
    IQuit();
}

/*
    �������ܣ�View0��һҳ
    ���������pag����View0��ҳ��, null��������ռλ
    �����������
    ����ֵ����
*/
void ILastPage(IFileNode *pag,IFileNode* null)
{
    char* page=(char*)pag;

    *page-=1;
    //������һҳ
}

/*
    �������ܣ�View0��һҳ
    ���������pag����View0��ҳ��, null��������ռλ
    �����������
    ����ֵ����
*/
void INextPage(IFileNode *pag,IFileNode* null)
{
    char* page=(char*)pag;

    *page+=1;
    //������һҳ
}

/*
    �������ܣ�����View0Ϊ��ϸ��Ϣ
    ���������flag����View0�Ŀ���λ, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetView10(IFileNode * flag,IFileNode* null)
{
    char *menuFlag=(char*)flag;

    (*menuFlag)&=63;
}

/*
    �������ܣ�����View0Ϊ��ͼ��
    ���������flag����View0�Ŀ���λ, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetView11(IFileNode * flag,IFileNode* null)
{
    char *menuFlag=(char*)flag;

    (*menuFlag)|=64;
}