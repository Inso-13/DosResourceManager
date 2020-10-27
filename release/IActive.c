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
void ISelect(IFileNode *node,IFileNode *flag)
{
    char *menuFlag=(char*)flag;
    char *temp="1";
    int i=0,j=0;
    IFileNode *tempNode=IFindParent(node)->child;   //ѡ��ڵ�ĸ��ڵ�

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            tempNode->flags&=NODE_DEL_SELECT;
            if((*menuFlag)&FLAG_IS_VIEW11)
                IBar(276+DF+i%30%6*102,116+DF+i%30/6*112,276+DF+99+i%30%6*102,\
                116+DF+109+i%30/6*112,DRM_CHOSENBLUE,DRM_WHITE);
            else
                IBar(248+DF,116+i%30*20+DF,936+DF,135+i%30*20+DF,DRM_CHOSENBLUE,\
                DRM_WHITE);
        }
        if(tempNode==node)
        {
            j=i;
        }
        tempNode=tempNode->next;
        i++;
    }   //�����ǰ·�����Ѿ��б�ѡ�еĽڵ㣬������Ϊδ��ѡ��

    node->flags|=NODE_ADD_SELECT; //ѡ�иýڵ�
    if((*menuFlag)&FLAG_IS_VIEW11)
        IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
        116+DF+109+j%30/6*112,DRM_WHITE,DRM_CHOSENBLUE);      
    else
        IBar(248+DF,116+j%30*20+DF,936+DF,135+j%30*20+DF,DRM_WHITE,DRM_CHOSENBLUE);
    
    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(160+DF+16*2,752+3+DF,160+DF+16*2+8*3,767+DF);
    setcolor(DRM_BLUE);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(160+DF+16*2+12,752+3+DF,temp);
    settextjustify(LEFT_TEXT,TOP_TEXT);
}

/*
    �������ܣ���View1�У����ϵأ�ѡ���ļ��ڵ㣬��ʾ����
    ���������node������ѡ�еĽڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ICtrlSelect(IFileNode *node,IFileNode *flag)
{
    char temp[4];
    char *menuFlag=(char*)flag;
    IFileNode *tempNode=IFindParent(node)->child;   //ѡ��ڵ�ĸ��ڵ�
    int i=0,j=0,numOfSelected=0;

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
            numOfSelected++;
        if(tempNode==node)
            j=i;
        tempNode=tempNode->next;
        i++;
    }

    if(!(node->flags&NODE_IS_SELECTED))
    {
        node->flags|=NODE_ADD_SELECT;
        numOfSelected++;
        if((*menuFlag)&FLAG_IS_VIEW11)
            IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
            116+DF+109+j%30/6*112,DRM_WHITE,DRM_CHOSENBLUE);      
        else
            IBar(248+DF,116+j%30*20+DF,936+DF,135+j%30*20+DF,DRM_WHITE,DRM_CHOSENBLUE);
    }
    else
    {
        node->flags&=NODE_DEL_SELECT;
        numOfSelected--;
        if((*menuFlag)&FLAG_IS_VIEW11)
            IBar(276+DF+j%30%6*102,116+DF+j%30/6*112,276+DF+99+j%30%6*102,\
            116+DF+109+j%30/6*112,DRM_CHOSENBLUE,DRM_WHITE);
        else
            IBar(248+DF,116+j%30*20+DF,936+DF,135+j%30*20+DF,DRM_CHOSENBLUE,DRM_WHITE);
    }
    //����ýڵ��ѱ�ѡ�У����ѡ�У�����ѡ�иýڵ�

    setfillstyle(SOLID_FILL,DRM_WHITE);
    bar(160+DF+16*2,752+3+DF,160+DF+16*2+8*3,767+DF);
    setcolor(DRM_BLUE);
    sprintf(temp,"%d",numOfSelected);
    settextjustify(CENTER_TEXT,TOP_TEXT);
    outtextxy(160+DF+16*2+12,752+3+DF,temp);
    settextjustify(LEFT_TEXT,TOP_TEXT);
}

/*
    �������ܣ��ղ�����������ռλ/�ض�/ˢ�µ�
    ���������null1��������ռλ, null2��������ռλ
    �����������
    ����ֵ����
*/
void INOP(IFileNode *null1,IFileNode *null2)
{
    ICheckNull(null1);
    ICheckNull(null2);
}

/*
    �������ܣ�������һĿ¼
    ���������null��������ռλ
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IGoLeftActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer **)cur;

    ICheckNull(null);
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

    ICheckNull(null);
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

    ICheckNull(null);
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

    ICheckNull(null);
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

    ICheckNull(null);
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
    
    ICheckNull(null);
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

    ICheckNull(null);
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

    ICheckNull(null);
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
    
    ICheckNull(null);
    (*menuFlag)|=FLAG_ADD_VIEW11;    //����Ϊ��ʾview1��1����ͼ
}

/*
    �������ܣ�����·��
    ���������cur������ǰ�ڵ�, X���������ļ��ڵ�
    �����������
    ����ֵ����
*/
void IGotoActive(IFileNode *cur,IFileNode *null)
{
    IFileNodePointer **curNode=(IFileNodePointer**)cur;
    char tempStr[PATH_LEN];
    char flag;

    ICheckNull(null);
    IGetAbsolutePath((*curNode)->child,tempStr);
    IGetString(152+DF,51+DF,649,tempStr,GOTO_STR);

    flag=IGoto(tempStr,curNode);

    if(!flag)
    {
        setcolor(DRM_RED);
        outtextxy(400+DF,752+DF,"Failed");
        IWarningBeep();
        delay(1500);
    }
}