#include "types.h"

int kern_entry()
{
    uint8_t *input = (uint8_t*)0xB8000;
    uint8_t color = (1<<4) | (15&0x0f);

    *input++ ='H';*input++=color;
    *input++ ='e';*input++=color;
    *input++ ='l';*input++=color;
    *input++ ='l';*input++=color;
    *input++ ='o';*input++=color;
    *input++ =',';*input++=color;
    *input++ ='o';*input++=color;
    *input++ ='s';*input++=color;
    *input++ =' ';*input++=color;
    *input++ ='k';*input++=color;
    *input++ ='e';*input++=color;
    *input++ ='r';*input++=color;
    *input++ ='n';*input++=color;
    *input++ ='e';*input++=color;
    *input++ ='l';*input++=color;
    *input++ ='!';*input++=color;
    return 0;
}
