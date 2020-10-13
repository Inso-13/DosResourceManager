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