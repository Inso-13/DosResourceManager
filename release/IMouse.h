#ifndef __IMOUSE_H
#define __IMOUSE_H

void IMouseMath(int (*mouseDraw)[16]);
void IMouseOn(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);
void IMouseOff(int x,int y,int (*mouseDraw)[16],int (*pixelSave)[16]);
void IMouseSetX(int lx,int rx);
void IMouseSetY(int uy,int dy);
void IMouseSetXY(int x,int y);
void IMouseSetLimit(int xMax,int yMax);
void IMouseGetXY(int*,int*);
int IMouseLeftRelease(void);
int ILeftPress(void);
int IRightPress(void);
int IMouseStatus(int*,int*,int (*mouseDraw)[16],int (*pixelSave)[16]);

#endif