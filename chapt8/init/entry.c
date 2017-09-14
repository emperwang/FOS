#include"console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
int kern_entry()
{
   	init_debug();
	
	init_gdt();
	init_idt();

 	
	concole_clear();

	console_write_color("hello,OS kernel!",rc_black,rc_green);
	
	init_timer(200);
	
	asm voatile("sti");
	
	return 0;
}
