#include"console.h"

int kern_entry()
{
    uint8_t *input = (uint8_t*)0xB8000;
    uint8_t color = (0<<4) | (15&0x0f);

 /*   *input++ ='H';*inpuit++=color;
    *input++ ='e';*inpuit++=color;
    *input++ ='l';*inpuit++=color;
    *input++ ='l';*inpuit++=color;
    *input++ ='o';*inpuit++=color;
    *input++ =',';*inpuit++=color;
    *input++ ='o';*inpuit++=color;
    *input++ ='s';*inpuit++=color;
    *input++ =' ';*inpuit++=color;
    *input++ ='k';*inpuit++=color;
    *input++ ='e';*inpuit++=color;
    *input++ ='r';*inpuit++=color;
    *input++ ='n';*inpuit++=color;
    *input++ ='e';*inpuit++=color;
    *input++ ='l';*inpuit++=color;
    *input++ ='!';*inpuit++=color;*/
    
    concole_clear();

    console_write_color("hello,OS kernel!",rc_black,rc_green);

    return 0;
}
