#include"console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "task.h"
#include "sched.h"


void kern_init();

multiboot_t *glb_mboot_ptr;

char kern_stack[STACK_SIZE] __attribute__((aligned(16)));

uint32_t kern_stack_top;

__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_high = (pgd_t *)0x3000;

__attribute__((section (".init.text"))) void kern_entry()
{
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT|PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high | PAGE_PRESENT|PAGE_WRITE;
	int i;
	for(i=0; i <1024;i++)
	{
		pte_low[i] = (i<<12)|PAGE_PRESENT|PAGE_WRITE;
	}
	
	for(i = 0; i < 1024;i++)
	{
		pte_high[i] = (i<<12)|PAGE_PRESENT|PAGE_WRITE;		
	}
	
	asm volatile("mov %0,%%cr3": :"r"(pgd_tmp));
	
	uint32_t cr0;
	asm volatile ("mov %%cr0,%0":"=r"(cr0));
	
	cr0 |= 0x80000000;
	asm volatile("mov %0,%%cr0": :"r"(cr0));
	
	kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE)&0xfffffff0;
	asm volatile("mov %0,%%esp\n\t"
			"xor %%ebp,%%ebp": :"r"(kern_stack_top));
	glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

	kern_init();
	
}

int flag = 0;
int thread(void *arg)
{
	while(1)
	{
		if(flag == 1)
		{
			printk_color(rc_black,rc_green,"B");
			flag = 0
		}
	}
	return 0;
}

int kern_init()
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
//	show_memory_map();	
	init_memory_map();
	
	init_pmm();
	init_vmm();
	init_heap();

	init_sched();
	kernel_thread(thread,NULL);
	
	while(1)
	{	
		if(flag == 0)
		{
			printk_color(rc_black,rc_red,"A");
			flag = 1;
		}
	}	

	return 0;
}
