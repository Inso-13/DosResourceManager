/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵����Diry��DirBaseΪ�������ṩ�˻������Ա�ǰ��ֱ��ʹ�õ��ļ���������
 **************************************************
 */

#include"IDiry.h"

/*
    �������ܣ��������ļ�
    ���������pathNode����·���ڵ�, fileName�������ļ���
    �����������
    ����ֵ�����Ƴɹ�����1��ʧ���򷵻�0
*/
int Inew(IFileNode *pathNode,char *fileName)
{
    char temp[PATH_LEN],tempStr1[PATH_LEN];  //�����ַ���
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","r+");
    long len=0;
    int i;

    for(i=0;i<strlen(fileName);i++)
    {
        if(fileName[i]>='a'&&fileName[i]<='z')
            fileName[i]+='A'-'a';
    }
    IGetAbsolutePath(pathNode,temp);
    Icd(temp);  //���뵱ǰĿ¼
    strcat(temp,"\\");
    strcat(temp,fileName);
    
    if(creatnew(fileName,0)==-1)
        return 0;
    //����ʧ�ܣ�����0

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
    //�����ɹ�����ӵ��ļ����У�����1 
}

/*
    �������ܣ��������ļ�/�ļ���
    ���������oldName�������ļ��ڵ�, newName�������ļ���
    �����������
    ����ֵ����
*/
void Irename(IFileNode *oldName,char *newName)
{
    char temp[PATH_LEN];  //�����ַ���
    struct find_t ft;  //�����ļ��ṹ��
    int i;  //ѭ������

    IGetAbsolutePath(IFindParent(oldName),temp);
    Icd(temp);
    rename(oldName->file.name,newName);  
    //�������ļ�/�ļ���

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
        if(i==0) //���û�к�׺��
        {
            _dos_findfirst(newName,0xf7,&ft);
            if(!(ft.attrib&FA_DIREC))   //��������ļ���
                strcpy(oldName->file.type,"NOT");
        }
    }
    //�����ļ�������
}

/*
    �������ܣ���rootĿ¼�µ��ļ����ļ����ϼ���
    ���������root������Ҫ������Ŀ¼
    �����������
    ����ֵ����
*/
void IDetree(IFileNode *root)
{
    if(!root) return;
    //��root==NULL��ֱ�ӷ���
    
    if(!IisFolder(root)) return;
    //��root�����ļ��У�ֱ�ӷ���
    
    if(!root->child) return;
    //��rootδ���򿪣�ֱ�ӷ���

    root->file.type[0]='0';
    //�ر��ļ���

    if(root->file.type[1]=='\\') return;
    //��Ŀ¼Ϊ��Ŀ¼����0����
    
    if(root->child)
    {
        IDelFilelist(root->child);
        root->child=NULL;
    }
    //��rootĿ¼�µ��ļ����ļ����ϼ���
}

/*
    �������ܣ���rootĿ¼�µ��ļ��ӵ��ļ�����
    ���������root������Ҫ��֦��Ŀ¼,flag��������λ
    �����������
    ����ֵ����
*/
void IEntree(IFileNode *root,char flag)
{
    IFileNode *childRoot=NULL;
    char temp[PATH_LEN];

    if(!root) return;
    //��root==NULL��ֱ�ӷ���
    if(!IisFolder(root)) return;
    //��root�����ļ��У�ֱ�ӷ���
    if(!strcmp(root->file.type,"0ds")) return;
    //��root�Ǳ������Ĵ��̣�ֱ�ӷ���
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
    //��root�ѱ��򿪣����´�
    root->file.type[0]='1';
    //���ļ���
    if(root->file.type[1]=='\\') return;
    //��Ŀ¼Ϊ��Ŀ¼����1����
    IGetAbsolutePath(root,temp);
    childRoot=IGetFileNodeList(temp);
    if(childRoot)
        IAddChild(root,childRoot);
    //��rootĿ¼�µ��ļ��ӵ��ļ�����
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
    //�����ӽڵ�
}

/*
    �������ܣ�����oldParentĿ¼�����б�ѡ�е��ļ�
    ���������oldParent������Ҫ���Ƶ�Ŀ¼, newParent����Ŀ��Ŀ¼
    �����������
    ����ֵ����
*/
void Icplr(IFileNode *oldParent,IFileNode *newParent,char flag)
{
    IFileNode *tempNode=oldParent->child,*newF=NULL;
    char temp[PATH_LEN];    //�����ļ�·��

    while(tempNode)
    {
        if(tempNode->flags&NODE_IS_SELECTED)
        {
            Icpr(tempNode,newParent,flag);
            if(IisFolder(tempNode)) //������ļ���
            {
                newF=IFindNodeByName(tempNode->file.name,newParent);
                IGetAbsolutePath(newF,temp);
                if(IPeek(newF,temp))
                    newF->flags|=NODE_HAS_FOLDER;
            }
        } 
        //������ļ��ڵ㱻ѡ�У�����֮
        tempNode=tempNode->next;
    }
}

/*
    �������ܣ�ɾ��oldParentĿ¼�����б�ѡ�е��ļ�
    ���������oldParent������Ҫɾ����Ŀ¼
    �����������
    ����ֵ����
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
        //������ļ��ڵ㱻ѡ�У���ɾ��֮
        tempNode=tempNode->next;
    }
}

/*
    �������ܣ����ļ����ڵ�ǰ�ļ��в����ļ�
    ���������path������Ҫ���ҵ�Ŀ¼, patternͨ���
    ���������fp�����ݴ��ļ�
    ����ֵ����
*/
void ISearch(char *path,char *pattern,FILE *fp)
{
    int ret,i;
    struct find_t ft;
    char temp[PATH_LEN];  //�����ַ���

    Icd(path);  //���뵱ǰ·��
    ret=_dos_findfirst("*.*", 0xf7,&ft);  //����ȫ���ļ�
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
        //�ų������ļ�·���򱻱������ļ�·��

        if(IMatch(ft.name,pattern))
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            strcat(temp,"\n");
            fputs(temp,fp);
        }
        //���ƥ�䣬��¼��fp�ļ�

        if(ft.attrib&FA_DIREC)
        {
            strcpy(temp,path);
            strcat(temp,"\\");
            strcat(temp,ft.name);
            ISearch(temp,pattern,fp);
        }
        //������ļ��У��ݹ����

        Icd(path);  //�ص���ǰ·��
        ret=_dos_findnext(&ft); //������һ��
    }
}
