#include "IDate.h"

typedef struct IFile
{
    char* name;
    IDate date;
    char* type;
    long size;
    char disk;
    char* path;
}IFile;


