#include "IDate.h"

typedef struct IFile
{
    char name[36];
    IDate date;
    char type[6];
    long size;
    char path[80];
}IFile;


