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
void IAfterEntree(IFileNode *cur,IFileNode *X)
{
#ifdef LM   //���ڴ�����ʱʹ��
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
    IFileNodePointer *nodeX=(IFileNodePointer*)X;    //�����ļ��ڵ�
    IFileNodePointer *tempNode=(*curNode)->pre,*lastNode=tempNode->pre;    //ѭ��ʹ��
    char path1[PATH_LEN],path2[PATH_LEN],path[PATH_LEN];   //�ݴ��ַ���

    IGetAbsolutePath((*curNode)->child,path1);  //��õ�ǰλ��
    if(nodeX&&nodeX->child)     //���nodeX��Ϊ��           
        IGetAbsolutePath(nodeX->child,path2);   //�õ�nodeXָ���·��
    else          
        strcpy(path2,"");   //���Ϊ�վͽ�·����Ϊ��

    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path);     //�õ�����������ڵ�
        if(strcmp(path,ROOT_NAME)&&strcmp(path,path1)&&strcmp(path,path2)&&!IisChild(path1,path)&&!IisChild(path2,path))
        {           //���������ͻ
            IDetree(tempNode->child);   //�ͷŽڵ�
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
            }   //��������ɾ���ڵ�
        }
        tempNode=lastNode;  //�������
    }   //end of while(tempNode)
#endif
}

/*
    �������ܣ�����IEntree���������ĵ�ǰ�ڵ�
    ���������node������ҪIEntree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IEntreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
	IFileNodePointer *newCurNode=(IFileNodePointer*)malloc(sizeof(IFileNodePointer));     //�½ڵ�
    IFileNodePointer *tempNode=NULL,*nextNode=NULL;    //ѭ�������ڵ�

    tempNode=(*curNode)->next;  //tempNodeָ��ѭ������һ��
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }//����curNode�����к�һ��ݹ�ɾ����������нڵ�

    newCurNode->child=node;
    newCurNode->next=NULL;
    newCurNode->wait=WAIT_COUNT;
    newCurNode->pre=*curNode;
    (*curNode)->next=newCurNode;
    *curNode=newCurNode;
    //�½ڵ��ʼ��

    IEntree(node,node->flags&NODE_TO_REENTREE);   //����IEntree����

    tempNode=(*curNode)->pre;
    while(tempNode)
    {
        tempNode->wait--;   //����ǰ��ڵ�ĵȴ�����
        if(tempNode->wait<WAIT_OFF)    //����ڵ�ĵȴ���������0
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
    //ɾ��curNode�����еĳ�ʱ�ڵ㣬�Խ�Լ�ڴ�
}

/*
    �������ܣ����������nodeX��ΪNULL
    ���������node������ҪIDetree�Ľڵ�
    ���������X���������ļ��ڵ�
    ����ֵ����
*/
void ISetXNull(IFileNode *node,IFileNode *X)
{
    IFileNodePointer *nodeX=(IFileNodePointer*)X;    //�ļ������ڵ�
    char path1[PATH_LEN],path2[PATH_LEN];     //�����ַ���

    if(node->file.type[1]=='\\')
        return;     //����Ǹ�Ŀ¼�������в���

    IGetAbsolutePath(node,path1);
    if(nodeX&&nodeX->child)
        IGetAbsolutePath(nodeX->child,path2);      //�õ����ߵ�·��
    if(!strcmp(path1,path2)||IisChild(path2,path1))
        nodeX->child=NULL;  //������ͻ��ɾ�������ڵ㣬ȡ��ճ���ȴ�
}

/*
    �������ܣ�����IDetree���������ĵ�ǰ�ڵ�
    ���������node������ҪIDetree�Ľڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IDetreeActive(IFileNode *node,IFileNode *cur)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;   //��ǰ�ڵ�
    IFileNodePointer *tempNode=NULL,*nextNode=NULL,*lastNode=NULL;    //ѭ�������ڵ�
    char path1[PATH_LEN],path2[PATH_LEN];  //�����ַ���

    if(node->file.type[1]=='\\') return;    //����Ǹ��ڵ㣬ֱ�ӷ���

    tempNode=(*curNode)->next;  
    while(tempNode)
    {
        nextNode=tempNode->next;
        tempNode->pre->next=NULL;
        free(tempNode);
        tempNode=nextNode;
    }   //����curNode�����к�һ��ݹ�ɾ����������нڵ�

    tempNode=(*curNode);
    IGetAbsolutePath(node,path2);   //�õ�Ҫɾ���ڵ��λ��
    while(tempNode)
    {
        lastNode=tempNode->pre;
        IGetAbsolutePath(tempNode->child,path1);    //�õ�����Ľڵ��λ��
        if(IisChild(path1,path2))   //���������ͻ
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
    }   //���curNode��������node�ڵ㣬���ýڵ�������г�ȥ

    if(node->file.type[1]!='\\')
        (*curNode)->child=IFindParent(node);    //����curNode�ڵ�

    IDetree(node);  //����IDetree����

    node->file.type[0]='0'; //�ر��ļ���
}

/*
    �������ܣ���View1�У���һ�أ�ѡ���ļ��ڵ㣬��ʾ����
    ���������node������ѡ�еĽڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISelect(IFileNode *node,IFileNode *null)
{
    IFileNode *tempNode=IFindParent(node)->child;   //ѡ��ڵ�ĸ��ڵ�

    while(tempNode)
    {
        tempNode->flags&=NODE_DEL_SELECT;    
        tempNode=tempNode->next;
    }   //�����ǰ·�����Ѿ��б�ѡ�еĽڵ㣬������Ϊδ��ѡ��

    node->flags|=NODE_ADD_SELECT; //ѡ�иýڵ�
}

/*
    �������ܣ���View1�У����ϵأ�ѡ���ļ��ڵ㣬��ʾ����
    ���������node������ѡ�еĽڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ICtrlSelect(IFileNode *node,IFileNode *null)
{
    if(!(node->flags&NODE_IS_SELECTED))
        node->flags|=NODE_ADD_SELECT;
    else
        node->flags&=NODE_DEL_SELECT;
    //����ýڵ��ѱ�ѡ�У����ѡ�У�����ѡ�иýڵ�
}

/*
    �������ܣ��ղ�����������ռλ/�ض�/ˢ�µ�
    ���������null1��������ռλ, null2��������ռλ
    �����������
    ����ֵ����
*/
void INOP(IFileNode *null1,IFileNode *null2){}

/*
    �������ܣ�������һĿ¼
    ���������null��������ռλ
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGoLeftActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->pre;   //������һĿ¼
}

/*
    �������ܣ�������һĿ¼
    ���������null��������ռλ
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGoRightActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;

    *curNode=(*curNode)->next;  //������һĿ¼
}

/*
    �������ܣ�������Һ���
    ���������cur������ǰ�ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ISearchActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer *curNode=(IFileNodePointer*)cur;  //��ǰ�ڵ�
    FILE *fp=fopen("C:\\DOSRES\\ETC\\SEARCH.TXT","w+"); //���ǵķ�ʽ�����ڼ�¼���ļ�
    char temp[20],path[PATH_LEN];     //�����ַ���

    IGetAbsolutePath(curNode->child,path);  //�����Ҫ���ҵ�·��
    strcpy(temp,"\0");  //����ַ���
    IGetString(851+DF,51+DF,166,temp,SEARCH_STR);   //�õ����ҵ�pattern������ʹ�ã�*

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);
    setcolor(DRM_RED);
    outtextxy(900+DF,753+DF,"Searching...");    //��ʾ��������

    if(temp[0])
        ISearch(path,temp,fp);  //������Һ���
    fclose(fp);    //�ر�������¼���ļ�

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(900+DF,745+DF,1020+DF,765+DF);  //ֹͣ��ʾSearching...
}

/*
    �������ܣ���exe���ļ�
    ���������exe������ִ�е��ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void IexeActive(IFileNode *exe,IFileNode *null)
{
    char temp[PATH_LEN+24];     //�����ַ���

    IGetAbsolutePath(exe,temp);

    setfillstyle(SOLID_FILL,DRM_BLACK);
    bar(0,0,1280,1024);
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");  //����־��Ϣ�����log.txt
    system(temp);   //ϵͳ���ã����ñ༭�����ı��ļ�
    delay(2000);  //����ͣ��
    IQuit();    //����ͣ�����˳�
}

/*
    �������ܣ���txt���ļ�
    ���������txt�����ɱ༭���ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ItxtActive(IFileNode *txt,IFileNode *null)
{
    char temp[PATH_LEN+48];   //�����ַ���

    strcpy(temp,"C:\\BORLANDC\\BIN\\BC.EXE ");  //����BC�༭��
    IGetAbsolutePath(txt,temp+23);  
    
    strcat(temp,">>C:\\DOSRES\\ETC\\log.txt");  //����ض�����log.txt
    system(temp);   //ϵͳ���ã�����BC�༭�����ı��ļ�
    IQuit();    //����ʱ�˳�
}

/*
    �������ܣ�View0��һҳ
    ���������pag����View0��ҳ��, null��������ռλ
    �����������
    ����ֵ����
*/
void ILastPage(IFileNode *pag,IFileNode *null)
{
    char *page=(char*)pag;  //ҳ�����

    *page-=1;   //������һҳ
}

/*
    �������ܣ�View0��һҳ
    ���������pag����View0��ҳ��, null��������ռλ
    �����������
    ����ֵ����
*/
void INextPage(IFileNode *pag,IFileNode *null)
{
    char *page=(char*)pag;  //ҳ�����

    *page+=1;   //������һҳ
}

/*
    �������ܣ�����View0Ϊ��ϸ��Ϣ
    ���������flag����View0�Ŀ���λ, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetView10(IFileNode *flag,IFileNode *null)
{
    char *menuFlag=(char*)flag;    //�˵�/��ͼ����

    (*menuFlag)&=FLAG_ADD_VIEW10;    //����Ϊ��ʾview1��0����ͼ
}

/*
    �������ܣ�����View0Ϊ��ͼ��
    ���������flag����View0�Ŀ���λ, null��������ռλ
    �����������
    ����ֵ����
*/
void ISetView11(IFileNode *flag,IFileNode *null)
{
    char *menuFlag=(char*)flag; //�˵�/��ͼ����

    (*menuFlag)|=FLAG_ADD_VIEW11;    //����Ϊ��ʾview1��1����ͼ
}