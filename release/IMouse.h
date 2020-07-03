#if !defined(__IMOUSE_H)
#define __IMOUSE_H

#define WAITING 0xff00
#define LEFTPRESS 0xff01
#define LEFTCLICK 0xff10
#define LEFTDRAG 0xff19
#define RIGHTPRESS 0xff02
#define RIGHTCLICK 0xff20
#define RIGHTDRAG 0xff2a
#define MIDDLEPRESS 0xff04
#define MIDDLECLICK 0xff40
#define MIDDLEDRAG 0xff4c
#define MOUSEMOVE 0xff08

void MouseMath(int (*up)[16],int (*down)[16],int (*mouse_draw)[16]);
void MouseOn(int x,int y,int (*mouse_draw)[16],int (*pixel_save)[16]);
void MouseOff(int*,int*,int (*mouse_draw)[16],int (*pixel_save)[16]);
void MouseLoad(int*,int*);
void MouseReset(void);
void MouseSetX(int lx,int rx);
void MouseSetY(int uy,int dy);
void MouseSetXY(int x,int y);
void MouseGetXY(int*,int*);
void MouseSpeed(int vx,int vy);
int LeftPress(void);
int RightPress(void);
int MouseStatus(int*,int*,int (*mouse_draw)[16],int (*pixel_save)[16]);

#endif