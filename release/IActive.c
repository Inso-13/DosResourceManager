/*
    �汾�ţ�1.0
    ���ߣ������
    �������ڣ�2020-9-4
    ˵����Active�ຯ�������м�㣬���ڽ���ˣ���Diry�ȣ������Ľӿ�ͳһ������ǰ�˵���ջʹ��
*/


#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>
#include<BIOS.H>
#include<DOS.H>
#include<GRAPHICS.H>
#include<CONIO.H>
#include"IEvent.h"
#include"IUtility.h"
#include"IDiry.h"
#include"ISort.h"
#include"IInit.h"
#include"IHanZi.h"
#include"IActive.h"
#include"IDebug.h"


/*
    �������ܣ��ڼ���IEntree�����󣬻��������ڴ�
    ���������X���������ļ��ڵ�
    ���������cur������ǰ�ڵ�
    ����ֵ����
*/
void IAfterEntree(IFileNode* cur,IFileNode* X)
{
    IFileNodePointer ** curNode=(IFileNodePointer **)cur;
    IFileNodePointer * nodeX=(IFileNodePointer *)X;
    IFileNodePointer * tempNode=(*curNode)->pre,*lastNode=tempNode->pre;
    char path1[50],path2[50],path[50];

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

    IEntree(node);
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
    char path1[50],path2[50];

    if(node->file.type[1]=='d'||node->file.type[1]=='\\')
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
    char path1[50],path2[50];

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
        if(!strcmp(path1,path2)||IisChild(path1,path2))
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
    �������ܣ������Եػ�ȡ�ַ���
    ���������x���������λ�õĺ�����, y���������λ�õ�������, length���������ĳ���. flag��������������
    ���������string������ȡ���ַ���
    ����ֵ����ȡ���ַ������׵�ַ
    ע��flag=0 ������;flag=1 ���ؿ�; flag=2 �����û���;flag=3 ��������;flag=4 ���ļ�/���ļ���
*/
char* IGetString(int x,int y,int length,char* string,int flag)
{
    char* org=string;       //��¼��string�ĳ�ʼλ��
    char tempChar='\0';     //���ڽ���������ַ�
    char temp[20];          //�����ַ���
    int n,i,t=0,j;

    fflush(stdin);
    //ˢ�¼��̻�����

    setcolor(0);
    if(flag>=1&&flag<=3)
    {
        rectangle(x-1,y,x+length+1,y+27);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+1,x+length,y+26);
    }
    else
    {
        if(flag==4)
            strcpy(string,"");
        rectangle(x-1,y+6,x+length+1,y+25);
        setfillstyle(SOLID_FILL,255);
        bar(x,y+7,x+length,y+24);   
    }
    //��ʼ�������
    n=strlen(string);
    i=n;

    setcolor(144);
    if(flag!=3)
        outtextxy(x+2,y+9,string);
    else
        for(j=0;j<n;j++)
        {
            outtextxy(x+2+8*j,y+9,"*");
        }
    //���flag==3, ������ʾ��������

    while(1)
    {
        while(!kbhit())
        {
            if(t>0)
                setcolor(144);
            else
                setcolor(255);
            line(x+2+8*i,y+9,x+2+8*i,y+18);
            t++;
        }
        //����t���ڼ�ʱ��ʵ����˸����Ч��

        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);
        //���ֲ�ͬ�������

        tempChar=getch();

        if(tempChar=='\r')  //�س���
            break;
        else if(tempChar=='\b')  //�˸��
        {
            if(n&&i)
            {
                strcpy(string+i-1,string+i);
                n--;
                i--;
            }
        }
        else if(tempChar==0x1B)  //ESC��
        {
            strcpy(string,"");
            break;
        }
        else if(tempChar=='\0')
        {
            tempChar=getch();
            if(tempChar=='K'&&i)  //�����
                i--;
            else if(tempChar=='M'&&n>i)    //�ҷ����
                i++;
            else
            {
                getch();
                tempChar=getch();
                continue;
            }
        }
        else if(n<12&&((tempChar>='0'&&tempChar<='9')||(tempChar>='a'&&tempChar<='z')||(tempChar>='A'&&tempChar<='Z')||tempChar=='.'||tempChar=='_'||(flag==1&&(tempChar=='?'||tempChar=='*'))))
        {
            strcpy(temp,string+i);
            string[i++]=tempChar;
            strcpy(string+i,temp);
            n++;
        }
        //�Ϸ��ַ�����

        setcolor(144);
        if(flag>=1&&flag<=3)
            bar(x,y+1,x+length,y+26);
        else
            bar(x,y+7,x+length,y+24);   
        //���������

        if(flag!=3)
            outtextxy(x+2,y+9,string);
        else
            for(j=0;j<n;j++)
                outtextxy(x+2+8*j,y+9,"*");
        //�Ƿ������ʾ
    }
    return org;
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
    char temp[20],path[60];     //�����ַ���

    IGetAbsolutePath(curNode->child,path);  //�����Ҫ���ҵ�·��
    strcpy(temp,"\0");
    IGetString(851,51,166,temp,1);  
    //�õ����ҵ�pattern

    if(temp[0])
        ISearch(path,temp,fp);
    //������Һ���

    fclose(fp);
}

/*
    �������ܣ���exe���ļ�
    ���������exe������ִ�е��ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void IexeActive(IFileNode* exe,IFileNode* null)
{
    // char temp[50];

    // setfillstyle(SOLID_FILL,0);
    // bar(0,0,1024,768);
    // //Ӫ��dos�ն˻���

    // IGetAbsolutePath(exe,temp);
    // //�õ���ִ���ļ��ľ���·��

    // system(temp);
    //ϵͳ���ã�����exe�ļ�
}

/*
    �������ܣ���txt���ļ�
    ���������txt�����ɱ༭���ļ��ڵ�, null��������ռλ
    �����������
    ����ֵ����
*/
void ItxtActive(IFileNode* txt,IFileNode* null)
{
    // char temp[50];

    // strcpy(temp,"BC ");
    // IGetAbsolutePath(txt,temp+3);
    // closegraph();
    // //�ر�svgaģʽ

    // system(temp);
    //ϵͳ���ã�����BC�༭�����ı��ļ�
}

/*
    �������ܣ�������˵�
    ���������flag��������˵��򿪱�־, null��������ռλ
    �����������
    ����ֵ����
*/
void ISortMenuActive(IFileNode* flag,IFileNode* null)
{
    char *n=(char*) flag;
    *n|=1;
    //���򿪱�־��Ϊ1
}

/*
    �������ܣ�����������
    ���������cur������ǰ�ڵ�, pfun��������ȷ��˳��ĺ���ָ�룬������lambda
    �����������
    ����ֵ����
*/
void ISortActive(IFileNode* cur,IFileNode* pfun)
{
    IFileNodePointer* curNode=(IFileNodePointer*)cur;
    int (*fun)(IFileNode*,IFileNode*)=(int(*)(IFileNode*,IFileNode*))pfun;
    
    if(curNode->child->child)
        ISort(curNode->child,fun);
    //����������
}

/*
    �������ܣ���ȡ�û���
    ���������nam�������ڴ洢�û���, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetName(IFileNode* nam,IFileNode* null)
{
    char* name =(char*)nam;

    IGetString(440,440,220,name,2);
    //��ȡ�û���
}

/*
    �������ܣ���ȡ�û���
    ���������pass�������ڴ洢����, null��������ռλ
    �����������
    ����ֵ����
*/
void IGetPassword(IFileNode* pass,IFileNode* null)
{
    char* password=(char*)pass;

    IGetString(440,490,220,password,3);
    //��ȡ����
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
