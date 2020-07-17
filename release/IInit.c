#include"IInit.h"

void IInitGraph()
{
    int GraphDrive=VGA,GraphMode=VGAHI;
    initgraph(&GraphDrive,&GraphMode,"C:\\BORLANDC\\BGI");
}