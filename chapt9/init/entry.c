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

	printk("kernel in memory start : 0x%08X\n",kern_start);
	printk("kernel in memory end:   0x%08X\n",kern_end);	
	printk("kernel in memory used: %d kb\N",(kern_end - kern_start + 1023)/1024);
	show_memory_map();	
	return 0;
}
