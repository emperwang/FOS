#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"

void timer_callback(pt_regs *regs)
{
	static uint32_t tick =0;
	printk_color(rc_black,rc_red,"tick:%d\n",tick++);
}

void init_timer(uint32_t frequency)
{
	register_interrupt_handler(IRQ0,timer_callback);
	
//8253PIT 芯片IO端口范围是40-43H，输入频率位1193180,frequency是每秒中断次数
	uint32_t divisor = 1192180 / frequency;
	
	outb(0x43,0x36);
	
	//拆分低字节和高字节
	uint8_t low  = (uint8_t)(divisor & 0xff);
	uint8_t high = (uint8_t)((divisorr>>8)&0xff);
	
	//写入高字节和低字节
	outb(0x40,low);
	outb(0x40,high);
}
