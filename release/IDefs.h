/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-10-10
 *   说明：主要的一些宏定义
 **************************************************
 */

#ifndef __IDEFS_H
#define __IDEFS_H

#define LM              //有限的内存
// #define DB              //调试模式
#define DF 0            //屏幕偏移量
#define BUFFSIZE 1024   //复制文件时的缓存区大小
#define MAXNODES 120    //每个文件夹中显示的最大文件数
#define PATH_LEN 150    //绝对路径长度
#define ROOT_NAME "DRM" //根目录名
#define FORCED 1        //强制覆盖
#define UNFORCED 0      //非强制覆盖
#define VIEW0_PAGE 1    //view0显示页码
#define VIEW0_UNPAGE 0  //view0不显示页码

enum WAIT_CONTROL
{
    WAIT_OFF    = 0,
    WAIT_COUNT  = 10
};

enum NODE_FLAGS
{
    NODE_IS_CUT        = 1,
    NODE_IS_SELECTED   = 2,
    NODE_IS_HEAD       = 4,
    NODE_HAS_FOLDER    = 8,
    NODE_TO_REENTREE   = 16
};

enum NODE_CHANGE
{
    NODE_ADD_SELECT      = 2,
    NODE_ADD_HEAD        = 4,
    NODE_DEL_TO_REENTREE = 15,
    NODE_DEL_HEAD        = 27,
    NODE_DEL_SELECT      = 29,
    NODE_DEL_CUT         = 30
};

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

enum FLAG_FLAGS
{
    FLAG_IS_SEC_MENU   = 1,
    FLAG_TO_DEL        = 2,
    FLAG_IS_CTRLED     = 4,
    FLAG_IS_LAST_PAGE  = 8,
    FLAG_TO_COVER      = 16,
    FLAG_TO_UNCOVER    = 32,
    FLAG_IS_VIEW11     = 64
};

enum FLAG_CHANGE
{
    FLAG_ADD_DEL_COMFIRM = 2,
    FLAG_ADD_CTRLED      = 4,
    FLAG_ADD_LAST_PAGE   = 8,
    FLAG_ADD_COVER       = 16,
    FLAG_ADD_UNCOVER     = 32,
    FLAG_ADD_VIEW10      = 63,
    FLAG_ADD_VIEW11      = 64,
    FLAG_CLEAR_COVER     = 79,
    FLAG_DEL_UNCOVER     = 95,
    FLAG_DEL_COVER       = 111,
    FLAG_DEL_LAST_PAGE   = 119,
    FLAG_DEL_CTRLED      = 123,
    FLAG_DEL_TO_DEL      = 125,
    FLAG_DEL_SEC_MENU    = 126
};

enum REACT_VIEW
{
    REACT_MORE   =  -1,
    REACT_NULL   =  0,
    REACT_LOGIN  =  1,
    REACT_VIEW0  =  2,
    REACT_VIEW1  =  4,
    REACT_VIEW01 =  6,
    REACT_VIEW2  =  8
};

enum MOUSE_STATUS
{
    MOUSE_NULL              =  -1,
    MOUSE_MOVE              =  1,
    MOUSE_LEFT_PRESS        =  2,
    MOUSE_RIGHT_PRESS       =  4,
    MOUSE_DOUBLE_LEFT_PRESS =  8,
    MOUSE_LEFT_RELEASE      =  16
};

#endif