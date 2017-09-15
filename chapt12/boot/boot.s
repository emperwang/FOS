
;multiboot魔数，由规范决定
MBOOT_HEADER_MAGIC  equ     0x1BADB002

;0号位表示所有的引导模块将按页(4KB)边界对齐
MBOOT_PAGE_ALIGN    equ     1<<0

;1号位通过multiboot信息结构的mem_*域包括可用内存的信息
;把内存空间的信息包含在信息结构中GRUBMultiboot
MBOOT_MEM_INFO      equ     1<<1

;定义我们使用的Multiboot的标记
MBOOT_HEADER_FLAGS  equ     MBOOT_PAGE_ALIGN|MBOOT_MEM_INFO

;域是一个位的无符号值，当与其他的域checksun32magic也就是(和magicflags)
;相加时,要求其结果必须时位的无符号值32 0即(magic+flags+checksun=0)
MBOOT_CHECKSUN      equ -(MBOOT_HEADER_MAGIC+MBOOT_HEADER_FLAGS)

;符合规范的multiboot OS映像需要这样一个magic multiboot头
;multiboot头的分布必须如下所示:
;-------------------------------------------------
;偏移量类型域名备注
;0      u32     magic 必需
;4      u32     flags 必需
;8      u32     checksum 必需
;-------------------------------------------------

[BITS 32]  ;所有代码使用32bit方式编译
section .init.text    ;指定存放在临时代码段
;在代码段的额起始位置设置符合multiboot规范的标记

dd MBOOT_HEADER_MAGIC  ;GRUB会通过这个魔数判断该映像是否支持 
dd MBOOT_HEADER_FLAGS  ;GRUB的一些加载时选项，其详细注释在定义处
dd MBOOT_CHECKSUN      ;检测数值

[GLOBAL start]         ;向外部声明内核代码入口，提供给链接器 
[GLOBAL mboot_ptr_tmp] ;向外部声明struct multiboot* 变量
[EXTERN kern_entry]    ;声明内核C代码的入口函数
start:
    cli

    mov [mboot_ptr_tmp],ebx 
    
    mov esp,STACK_TOP
    and esp,0FFFFFFF0H
    mov ebp,0
    call    kern_entry

section .init.data
stack:    times 1024 db 0
STACK_TOP  equ  $-stack-1
mboot_ptr_tmp:   dd 0



