
[GLOBAL idt_flush]
idt_flush:
	mov eax,[esp+4]
	lidt [eax]
	ret
.end

%macro  ISR_NOERRCODE 1
[GLOBAL isr%1]
isr%1:
	cli
	push 0
	push %1
	jmp isr_common_stub
%endmacro

%macro  ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
	cli
	push %1
	jmp isr_common_stub
%endmacro

ISR_NOERRCODE	0
ISR_NOERRCODE	1
ISR_NOERRCODE	2
ISR_NOERRCODE	3
ISR_NOERRCODE	4
ISR_NOERRCODE	5
ISR_NOERRCODE	6
ISR_NOERRCODE	7
ISR_ERRCODE	8
ISR_NOERRCODE	9
ISR_ERRCODE	10
ISR_ERRCODE	11
ISR_ERRCODE	12
ISR_ERRCODE	13
ISR_ERRCODE	14
ISR_NOERRCODE	15
ISR_NOERRCODE	16
ISR_ERRCODE	17
ISR_NOERRCODE	18
ISR_NOERRCODE	19

ISR_NOERRCODE	20
ISR_NOERRCODE	21
ISR_NOERRCODE	22
ISR_NOERRCODE	23
ISR_NOERRCODE	24
ISR_NOERRCODE	25
ISR_NOERRCODE	26
ISR_NOERRCODE	27
ISR_NOERRCODE	28
ISR_NOERRCODE	29
ISR_NOERRCODE	31

ISR_NOERRCODE	255

[GLOBAL isr_common_stub]
[EXTERN isr_handler]
isr_common_stub:
	pusha
	
	mov ax,ds
	push eax        ;到这里,所有需要入栈的都入栈了
	
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax

	push esp       ;这里的esp就是pt_regs指针,作为参数传入栈中
	call isr_handler
	add esp,4

	pop ebx        ;让原来的数据段数值出栈
	mov ds,bx
	mov es,bx
	mov fs,bx
	mov gs,bx
	mov ss,bx
	
	popa
	
	add esp,8	;清理err_code,中断号
	iret
.end	 	


