/*
 **************************************************
 *   �汾�ţ�1.0
 *   ���ߣ������
 *   �������ڣ�2020-9-4
 *   ˵����DiryBase��ΪDiry��ĵײ�֧�ţ���װ����ೣ�õ��ļ���������
 **************************************************
 */

#include"IDirBase.h"

/*
    �������ܣ����Ƶ����ļ�����inFile�ļ����Ƶ�outParent�ļ����ڣ������½ڵ�
    ���������inFile�����ȴ����Ƶ��ļ�, outParent����ճ������Ŀ���ļ��У�flag�����Ƿ�ǿ�Ƹ���
    �����������
    ����ֵ�����Ƴɹ�����1��ʧ���򷵻�0
*/
int Icopy(IFileNode *inFile,IFileNode *outParent,char flag)
{
    char inPath[PATH_LEN];  //�����ļ���·��
    char outPath[PATH_LEN]; //����ļ��е�·��
    char temp[PATH_LEN]; //�����ַ���
    char i[2],name[18],ext[5]; //�ļ�������׺��
    char tempStr[30+2*PATH_LEN];  //�����и����ַ���
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","r+");
    int j;
    long len=0;  //ѭ��������������¼��׺���ķֽ��

    IGetAbsolutePath(inFile,inPath);    //�õ������ļ���·��
    IGetAbsolutePath(outParent,outPath);    //�õ�����ļ��е�·��
    strcat(outPath,"\\");
    strcat(outPath,inFile->file.name);      //�õ�����ļ���·��
    strcpy(name,inFile->file.name);     //��ȡ�ļ���
    
    while(fgets(temp,PATH_LEN,fp))
    {
        if(temp[strlen(temp)-1]=='\n')
            temp[strlen(temp)-1]='\0';
        if(!strcmp(temp,outPath))
        {
            fseek(fp,len+1,SEEK_SET);
            fputc('|',fp);
            break;
        }
        len+=strlen(temp)+2;
    }
    fclose(fp);

    if(!flag)   //�������Ҫǿ�Ƹ���
    {
        if(ISearchPath(outPath)||!strcmp(inPath,outPath)) //ԭλ�ÿ������ļ��Զ�������
        {
            strcpy(i,"1");
            for(j=0;j<strlen(inFile->file.name);j++)
                if(inFile->file.name[j]=='.')
                    break;
            strcpy(ext,inFile->file.name+j);
            if(strlen(name)>11||(j==strlen(name)&&j>7)) //����ļ�������
            {
                strcpy(name+4,"~"); //���ʡ�Է�
                strcpy(name+5,ext); //���ƺ�׺��
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
            }while(ISearchPath(temp));  //���ϸı��׺��ֱ���ļ����Ϸ�
            strcpy(outPath,temp);
        } // end of if(ISearchPath(outPath)||!strcmp(inPath,outPath))
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        strcat(tempStr+strlen(tempStr),outPath);

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);
    }
    else    //�����Ҫǿ�Ƹ���
    {
        Irmf(IFindNodeByPath(outPath,outParent));   //ɾ��ԭ���ļ�
        strcpy(tempStr,"copy ");
        IGetAbsolutePath(inFile,tempStr+5);
        strcat(tempStr," ");
        IGetAbsolutePath(outParent,tempStr+strlen(tempStr));

        strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
        system(tempStr);    //�������ļ�
    }   // end of if(!flag)

    IAddFileNode(outParent,name);   //������ļ��ڵ�
    return 1;
}

/*
    �������ܣ�����ɾ���ļ�
    ���������fileNode�����ȴ�ɾ�����ļ�
    �����������
    ����ֵ��ɾ���ɹ�����1��ʧ���򷵻�0
*/
int Irmf(IFileNode *fileNode)
{
    char tempStr[PATH_LEN];   //�����ַ���
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");    //��ɾ�������ļ�

    IGetAbsolutePath(fileNode,tempStr);
    strcat(tempStr,"\n");
    fputs(tempStr,fp);

    strcpy(tempStr,"del ");
    IGetAbsolutePath(fileNode,tempStr+4);
    strcat(tempStr,">>C:\\DOSRES\\ETC\\log.txt");
    system(tempStr);    //ɾ���ļ�

    fclose(fp);    //�ر�ɾ�������ļ�
    return IDelFileNode(IFindParent(fileNode),fileNode->file.name); //ɾ���ļ��ڵ�
}

/*
    �������ܣ������ļ��У������½ڵ�
    ���������pathNode�������ڵ�, folderName�������ļ�����
    �����������
    ����ֵ�������ļ��гɹ�����1��ʧ���򷵻�0
*/
int Imkdir(IFileNode *pathNode,char *folderName)    
{
    char temp[PATH_LEN],tempStr1[PATH_LEN];     //�����ַ���
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","r+");
    long len=0;
    
    IGetAbsolutePath(pathNode,temp);
    strcat(temp,"\\");
    strcat(temp,folderName);    //�õ����ļ��еľ���·��

    if(mkdir(temp)==-1) //��������ļ���ʧ��
        return 0;
    else
    {
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
        return IAddFileNode(pathNode,folderName);
    }
    //�����ļ��ڵ�
}

/*
    �������ܣ�ɾ�����п��ļ��У������½ڵ�
    ���������node�������ڵ�, flag���������Ƿ�ɾ���ֵ��ļ���
    �����������
    ����ֵ��ɾ���ļ��гɹ�����1��ʧ���򷵻�0
*/
int Irmdir(IFileNode *node)
{
    int i=0;    //ѭ����������
    char temp[PATH_LEN];      //�����ַ���
    FILE *fp=fopen("C:\\DOSRES\\ETC\\DEL.TXT","a+");    //��ɾ�������ļ�

    IGetAbsolutePath(node,temp);    
    strcat(temp,"\n");
    fputs(temp,fp);     //��Ҫɾ�����ļ��м�¼�������ļ���

    IGetAbsolutePath(node,temp);
    IDelFileNode(IFindParent(node),node->file.name);    //ɾ���ļ��ڵ�

    for(i=0;i<100;i++)
        if(ISearchPath(temp))
            rmdir(temp);    //���ϳ���ɾ���ļ���
        else 
            break;
            
    fclose(fp);  //�ر�ɾ�������ļ�
    return 1;
}

/*
    �������ܣ����������ļ�����
    ���������oldChildChild����Ҫ���Ƶ��ļ����еĵ�һ���ڵ�, newChild����Ҫճ�������ļ����ڲ�
    �����������
    ����ֵ����
*/
void ICopyAll(IFileNode *oldChildChild,IFileNode *newChild)
{
    while(oldChildChild)
    {
        if(IisFolder(oldChildChild))    //������ļ��У��ݹ鸴��
        {
            if(!oldChildChild->child)   //����ļ�δ����
                IEntree(oldChildChild,UNFORCED);
            Imkdir(newChild,oldChildChild->file.name); //�����ļ���
            if(oldChildChild->child)    //������ӽڵ�
            {
                ICopyAll(oldChildChild->child,\
                IFindNodeByName(oldChildChild->file.name,newChild->child));  //������������
                IDetree(oldChildChild); //ɾ��ԭ����
            }
        }
        else    //����ļ�
        {
            Icopy(oldChildChild,newChild,UNFORCED);   //�����ļ�
        }
        oldChildChild=oldChildChild->next;  
    }
    //�ݹ鸴���ֵܽڵ�
}

/*
    �������ܣ��ݹ鸴�������ļ����ļ���
    ���������oldChild����Ҫ���Ƶ��ļ����ļ���, newCParent����Ҫճ�������ļ���
    �����������
    ����ֵ����
*/
void Icpr(IFileNode *oldChild,IFileNode *newParent,char flag)
{
    char temp[PATH_LEN];      //�����ַ���
    IFileNode *tempNode=NULL;   //�����ڵ�

    if(IisFolder(oldChild)) //������ļ�
    {
        IGetAbsolutePath(newParent,temp);
        strcat(temp,"\\");
        strcat(temp,oldChild->file.name);

        if(ISearchPath(temp))
        {
            if(flag)    //�����ǿ�Ƹ���
                Irmr(IFindNodeByPath(temp,newParent));
            else
                return;
        }
        Imkdir(newParent,oldChild->file.name);  //�����ļ���
        IEntree(oldChild,UNFORCED);  
        tempNode=IFindNodeByPath(temp,newParent);
        tempNode->flags|=NODE_TO_REENTREE;
        ICopyAll(oldChild->child,tempNode);
        IDetree(oldChild);    //�ͷ�ԭ�ڵ���ڴ�
    }
    else
        Icopy(oldChild,newParent,flag); //������ļ�
}  

/*
    �������ܣ�ɾ������
    ���������oldChildChild����Ҫɾ�����ļ����еĵ�һ���ڵ�
    �����������
    ����ֵ����
*/
void IDelAll(IFileNode *oldChildChild)
{
    IFileNode *nextNode=NULL;   //�����ļ��ڵ�

    while(oldChildChild)
    {
        nextNode=oldChildChild->next;
        if(IisFolder(oldChildChild))    //������ļ���
        {
            if(!oldChildChild->child)
                IEntree(oldChildChild,UNFORCED);
            IDelAll(oldChildChild->child);
            Irmdir(oldChildChild);
        }
        else    //������ļ�
        {
            Irmf(oldChildChild);   //ɾ���ļ� 
        }
        oldChildChild=nextNode;
    }
}

/*
    �������ܣ��ݹ�ɾ�������ļ����ļ���
    ���������oldChild����Ҫɾ�����ļ���
    �����������
    ����ֵ����
*/
void Irmr(IFileNode *oldChild)
{
    if(IisFolder(oldChild)) //������ļ���
    {
        IEntree(oldChild,UNFORCED);
        if(oldChild->child)
            IDelAll(oldChild->child);
    }
    else
        Irmf(oldChild);
    //ɾ���ļ��������е��ļ�
}

/*
    �������ܣ��ж��Ƿ���name�ļ�
    ���������name�����ļ�����/���·��
    �����������
    ����ֵ�������ڸ��ļ�����1; ���򷵻�0
*/
int ISearchPath(char *name)
{
    struct find_t ft;   //���ҽṹ��

    return !_dos_findfirst(name,0xf7,&ft); 
    //�����Ƿ�������name���ļ�
}