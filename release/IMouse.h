#ifndef __IMOUSE_H
#define __IMOUSE_H

void IMouseMath(int (*mouseDraw)[16]);  //鼠标形状初始化
void IMouseOn(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);   //鼠标新位置显示
void IMouseOff(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);  //鼠标旧位置消失
void IMouseSetXY(int x,int y);  //设置鼠标的位置
void IMouseSetLimit(int xMax,int yMax); //设置鼠标移动的最大范围，推荐640*480
void IMouseGetXY(int*,int*);    //得到鼠标的当前位置
int IMouseLeftRelease(void);    //鼠标左键是否释放
int ILeftPress(void);           //鼠标左键是否按下
int IRightPress(void);          //鼠标右键是否按下
int IMouseStatus(int*,int*,int (*mouseDraw)[16],int (*pixelSave)[16]);
//返回鼠标的状态

#endif