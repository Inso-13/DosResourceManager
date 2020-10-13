/*
 **************************************************
 *   版本号：1.0
 *   作者：黄子昊
 *   生成日期：2020-9-4
 *   说明：视图函数1等
 **************************************************
 */

#ifndef __IVIEW1_H
#define __IVIEW1_H

//库文件
#include<GRAPHICS.H>
#include<CONIO.H>
#include<STDIO.H>
#include<STRING.H>
#include<STDLIB.H>

//辅助模块
#include"IHanZi.h"
#include"IType.h"
#include"ISound.h"
#include"IEvent.h"

//调用模块
#include"IActive.h"
#include"IMenu.h"
#include"IDirActive.h"

//图形库
#include"IIcon.h"
#include"IIconL.h"
#include"IDraw.h"


//函数原型
int IView1(IFileNodePointer** curNode,IFileNodePointer *nodeX,IEventStackNode *top,char *page,char *menuFlag,FILE *fpHZ);
void IView10DrawIcon(IFileNode *tempNode,int y);
void IView1PageControl(IFileNodePointer** curNode,char *page,int numOfItem);
void IView10(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,FILE *fpHZ,IEventStackNode *top,char *menuFlag);
void IView11(IFileNodePointer **curNode,IFileNodePointer *nodeX,IFileNode *tempNode,FILE *fpHZ,IEventStackNode *top,char *menuFlag);
void IView11DrawIcon(IFileNode *tempNode,int x,int y);
void IView1DelOrCover(int numOfSelected,IFileNodePointer **curNode,IFileNodePointer *nodeX,IEventStackNode *top,char *menuFlag,FILE *fpHZ);

#endif