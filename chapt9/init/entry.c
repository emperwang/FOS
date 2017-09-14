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
	init_memory_map();

	printk_color(rc_black,rc_red,"\nThe count of physical memory page is:%u\n\n",phy_page_count);
	uint32_t alloc_addr = NULL;
	
	printk_color(rc_black,rc_light_brown,"Test physical memory alloc:\n")
	
	alloc_addr = pmm_alloc_page();
	printk_color(rc_black,rc_light_brown,"Alloc physical addr:0x%08X\n",alloc_addr);

	alloc_addr = pmm_alloc_page();
	printk_color(rc_black,rc_light_brown,"Alloc physical addr:0x%08X\n",alloc_addr);
	alloc_addr = pmm_alloc_page();
	printk_color(rc_black,rc_light_brown,"Alloc physical addr:0x%08X\n",alloc_addr);
	alloc_addr = pmm_alloc_page();
	printk_color(rc_black,rc_light_brown,"Alloc physical addr:0x%08X\n",alloc_addr);
	return 0;
}
