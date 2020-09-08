#include<DOS.H>
#include"ISound.h"

void IWarningBeep()
{
    sound(700);
    delay(200);
    sound(300);
    delay(200);
    nosound();
}