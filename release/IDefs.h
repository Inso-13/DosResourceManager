#ifndef __IDEF_H
#define __IDEF_H

#define LM
#define DB
#define DF 0
#define BUFFSIZE 1024
//�����ļ�ʱ�Ļ�������С
#define MAXNODES 120

#define PATH_LEN 150
#define ROOT_NAME "DOS"

#define WAIT_COUNT 10
#define WAIT_OFF 0

#define NODE_IS_CUT 1
#define NODE_IS_SELECTED 2
#define NODE_IS_HEAD 4
#define NODE_HAS_FOLDER 8
#define NODE_TO_REENTREE 16

#define NODE_DEL_TO_REENTREE 15
#define NODE_DEL_SELECT 29
#define NODE_ADD_SELECT 2
#define NODE_DEL_CUT 30
#define NODE_DEL_HEAD 27
#define NODE_ADD_HEAD 4

#define MENU_SET_VIEW10 63
#define MENU_SET_VIEW11 64

#define FORCED 1
#define UNFORCED 0

enum DRM_COLORS
{
    DRM_VIOLET      =   84,
    DRM_PURPLE      =   50,
    DRM_LIGHTGRAY   =   247,
    DRM_DARKGRAY    =   248,
    DRM_LIGHTGREEN  =   140,
    DRM_DARKBLUE    =   10,
    DRM_BLUE        =   11,
    DRM_WHITE       =   255,
    DRM_ORANGE      =   202,
    DRM_YELLOW      =   206,
    DRM_CHOSENBLUE  =   139,
    DRM_BLACK       =   0,
    DRM_RED         =   180,
    DRM_TURQUOISE   =   6,
    DRM_LIDHTBLUE   =   23,
    DRM_BRIGHTBLUE  =   31,
    DRM_LIGHTYELLOW =   207
};
//menuFlag�����˵��ı�־(bit0 �Ƿ�Ϊ����˵�,bit1 �Ƿ���ɾ��ȷ�ϴ���,bit2 �Ƿ���Ctrl, bit3 �Ƿ������һҳ, bit4��5 �Ƿ��и���ȷ�ϴ���,bit6 ����View1��ͼ 0Ϊ��ϸ��Ϣ/1Ϊ��ͼ��)
#define FLAG_IS_SEC_MENU 1
#define FLAG_TO_DEL 2
#define FLAG_IS_CTRLED 4
#define FLAG_IS_LAST_PAGE 8
#define FLAG_TO_COVER 16
#define FLAG_TO_UNCOVER 32
#define FLAG_IS_VIEW11 64

#define FLAG_DEL_CTRLED 123
#define FLAG_ADD_CTRLED 4
#define FLAG_DEL_TO_DEL 125
#define FLAG_ADD_COVER 16
#define FLAG_ADD_LAST_PAGE 8
#define FLAG_DEL_LAST_PAGE 119
#define FLAG_DEL_UNCOVER 95
#define FLAG_CLEAR_COVER 79
#define FLAG_ADD_UNCOVER 32
#define FLAG_DEL_COVER 111
#define FLAG_DEL_SEC_MENU 126
#define FLAG_ADD_DEL_COMFIRM 2

enum REACT_VIEW
{
    REACT_MORE  =-1,
    REACT_NULL  =0,
    REACT_LOGIN =1,
    REACT_VIEW0 =2,
    REACT_VIEW1 =4,
    REACT_VIEW01=6,
    REACT_VIEW2 =8
};

enum MOUSE_STATUS
{
    MOUSE_NULL  = -1,
    MOUSE_MOVE  =1,
    MOUSE_LEFT_PRESS=2,
    MOUSE_RIGHT_PRESS=4,
    MOUSE_DOUBLE_LEFT_PRESS=8,
    MOUSE_LEFT_RELEASE=16
};

#endif