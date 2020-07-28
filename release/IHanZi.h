#ifndef __IHANZI_H
#define __IHANZI_H

void IPutsHZ16(int x,int y,char *str,FILE * fp);
// 中文输出，wid为字间距，size为放大倍数（整数），fp为fpHZ
void Iouttextxy(int x,int y,char *str,FILE * fp);
// 自动判断中英文输出，fp为fpHZ

#endif