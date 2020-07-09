#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IUtility.h"

void IInitGraph()
{
    int GraphDrive=VGA,GraphMode=VGAHI;
    initgraph(&GraphDrive,&GraphMode,"c:\\BORLANDC\\BGI");
}
void IQuit()
{
    closegraph();
    fcloseall();
    exit(0);
}