#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "IBase.h"

void IQuit()
{
    closegraph();
    fcloseall();
    exit(0);
}

